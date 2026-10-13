import { ansiToHtml } from './ansi';
import { ServerPayload, MenuItem, VitalsData, RoomData } from './types';

class MudClient {
  private socket: WebSocket | null = null;
  private history: string[] = [];
  private historyIdx = -1;
  private url: string;

  // DOM Elements
  private terminalEl: HTMLElement;
  private inputEl: HTMLInputElement;
  private bgLayerEl: HTMLElement;
  private menuContainerEl: HTMLElement;
  private vitalsBarEl: HTMLElement;
  private statusIndicatorEl: HTMLElement;

  constructor(url: string) {
    this.url = url;
    this.terminalEl = document.getElementById('terminal-log')!;
    this.inputEl = document.getElementById('cli-input') as HTMLInputElement;
    this.bgLayerEl = document.getElementById('bg-layer')!;
    this.menuContainerEl = document.getElementById('action-menu')!;
    this.vitalsBarEl = document.getElementById('vitals-panel')!;
    this.statusIndicatorEl = document.getElementById('connection-status')!;

    this.initEventListeners();
    this.connect();
  }

  public connect() {
    this.updateStatus('connecting', 'Connecting...');
    this.socket = new WebSocket(this.url);

    this.socket.onopen = () => {
      this.updateStatus('connected', 'Connected');
      this.logSystem('Connection established with FluffOS server.');
    };

    this.socket.onclose = () => {
      this.updateStatus('disconnected', 'Disconnected');
      this.logSystem('Disconnected from server. Retrying in 5 seconds...');
      setTimeout(() => this.connect(), 5000);
    };

    this.socket.onerror = () => {
      this.updateStatus('disconnected', 'Connection Error');
    };

    this.socket.onmessage = (event: MessageEvent) => {
      this.handleServerMessage(event.data);
    };
  }

  public send(command: string) {
    if (!this.socket || this.socket.readyState !== WebSocket.OPEN) {
      this.logSystem('Cannot send: not connected to server.');
      return;
    }
    // FluffOS expects standard newline termination
    this.socket.send(`${command}\n`);
  }

  private handleServerMessage(raw: string) {
    const trimmed = raw.trim();

    // Check if message is a JSON payload from FluffOS
    if (trimmed.startsWith('{') && trimmed.endsWith('}')) {
      try {
        const payload: ServerPayload = JSON.parse(trimmed);
        this.processPayload(payload);
        return;
      } catch {
        // Fall back to plain text if JSON parsing fails
      }
    }

    // Default: plain stream / ANSI text
    this.appendLog(ansiToHtml(raw));
  }

  private processPayload(payload: ServerPayload) {
    switch (payload.type) {
      case 'room':
        this.renderRoom(payload.data);
        break;
      case 'bg':
        this.setBackground(payload.url);
        break;
      case 'menu':
        this.renderMenu(payload.items);
        break;
      case 'vitals':
        this.renderVitals(payload.data);
        break;
      case 'text':
        this.appendLog(ansiToHtml(payload.text));
        break;
    }
  }

  private renderRoom(data: RoomData) {
    if (data.bg) this.setBackground(data.bg);
    this.appendLog(`<div class="room-title">${data.title}</div>`);
    this.appendLog(`<div class="room-desc">${ansiToHtml(data.description)}</div>`);

    if (data.exits && data.exits.length > 0) {
      const exitsHtml = data.exits
        .map(e => `<button class="exit-btn" data-cmd="${e}">${e}</button>`)
        .join(' ');
      this.appendLog(`<div class="room-exits"><strong>Exits:</strong> ${exitsHtml}</div>`);
    }

    if (data.menu) {
      this.renderMenu(data.menu);
    }
  }

  private setBackground(url: string) {
    if (!url) return;
    this.bgLayerEl.style.backgroundImage = `url('${url}')`;
  }

  private renderMenu(items: MenuItem[]) {
    this.menuContainerEl.innerHTML = '';
    items.forEach(item => {
      const btn = document.createElement('button');
      btn.className = 'menu-btn';
      btn.textContent = item.label;
      btn.onclick = () => {
        this.appendLog(`<span class="echo-input">&gt; ${item.command}</span>`);
        this.send(item.command);
      };
      this.menuContainerEl.appendChild(btn);
    });
  }

  private renderVitals(vitals: VitalsData) {
    const hpPct = Math.min(100, Math.max(0, (vitals.hp / vitals.max_hp) * 100));
    this.vitalsBarEl.innerHTML = `
      <div class="vital-label">HP: ${vitals.hp} / ${vitals.max_hp}</div>
      <div class="vital-track"><div class="vital-fill hp" style="width: ${hpPct}%"></div></div>
    `;
  }

  private appendLog(html: string) {
    const entry = document.createElement('div');
    entry.className = 'log-line';
    entry.innerHTML = html;
    this.terminalEl.appendChild(entry);
    this.terminalEl.scrollTop = this.terminalEl.scrollHeight;
  }

  private logSystem(text: string) {
    this.appendLog(`<span class="sys-msg">[SYSTEM] ${text}</span>`);
  }

  private updateStatus(state: 'connected' | 'connecting' | 'disconnected', label: string) {
    this.statusIndicatorEl.textContent = label;
    this.statusIndicatorEl.className = `status-pill status-${state}`;
  }

  private initEventListeners() {
    this.inputEl.addEventListener('keydown', (e: KeyboardEvent) => {
      if (e.key === 'Enter') {
        const val = this.inputEl.value;
        if (!val.trim()) return;

        this.appendLog(`<span class="echo-input">&gt; ${val}</span>`);
        this.send(val);

        this.history.push(val);
        this.historyIdx = this.history.length;
        this.inputEl.value = '';
      } else if (e.key === 'ArrowUp') {
        if (this.historyIdx > 0) {
          this.historyIdx--;
          this.inputEl.value = this.history[this.historyIdx];
        }
        e.preventDefault();
      } else if (e.key === 'ArrowDown') {
        if (this.historyIdx < this.history.length - 1) {
          this.historyIdx++;
          this.inputEl.value = this.history[this.historyIdx];
        } else {
          this.historyIdx = this.history.length;
          this.inputEl.value = '';
        }
        e.preventDefault();
      }
    });

    // Delegate clicks for inline exits
    this.terminalEl.addEventListener('click', (e: MouseEvent) => {
      const target = e.target as HTMLElement;
      if (target.classList.contains('exit-btn')) {
        const cmd = target.getAttribute('data-cmd');
        if (cmd) {
          this.appendLog(`<span class="echo-input">&gt; ${cmd}</span>`);
          this.send(cmd);
        }
      }
    });
  }
}

// Auto-boot when loaded
window.addEventListener('DOMContentLoaded', () => {
  // Replace with your FluffOS host and websocket port
  const wsProtocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
  const wsHost = window.location.hostname || '127.0.0.1';
  const client = new MudClient(`${wsProtocol}//${wsHost}:8080`);
});
