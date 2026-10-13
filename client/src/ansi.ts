const ANSI_COLORS: Record<number, string> = {
  30: '#1e1e1e', 31: '#f87171', 32: '#4ade80', 33: '#facc15',
  34: '#60a5fa', 35: '#c084fc', 36: '#38bdf8', 37: '#f3f4f6',
  90: '#6b7280', 91: '#ef4444', 92: '#22c55e', 93: '#eab308',
  94: '#3b82f6', 95: '#a855f7', 96: '#06b6d4', 97: '#ffffff'
};

export function ansiToHtml(input: string): string {
  // Basic HTML entity encoding
  const escaped = input
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;');

  let currentSpan = false;

  const parsed = escaped.replace(/\x1b\[([0-9;]+)m/g, (_, codeStr) => {
    const codes = codeStr.split(';').map(Number);
    let output = '';

    for (const code of codes) {
      if (code === 0) {
        if (currentSpan) {
          output += '</span>';
          currentSpan = false;
        }
      } else if (ANSI_COLORS[code]) {
        if (currentSpan) output += '</span>';
        output += `<span style="color: ${ANSI_COLORS[code]}">`;
        currentSpan = true;
      } else if (code === 1) {
        output += '<span style="font-weight: bold;">';
        currentSpan = true;
      }
    }
    return output;
  });

  return currentSpan ? `${parsed}</span>` : parsed;
}
