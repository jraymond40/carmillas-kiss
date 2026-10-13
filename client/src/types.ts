export interface MenuItem {
  label: string;
  command: string;
}

export interface RoomData {
  title: string;
  description: string;
  exits?: string[];
  bg?: string;
  menu?: MenuItem[];
}

export interface VitalsData {
  hp: number;
  max_hp: number;
  sp?: number;
  max_sp?: number;
}

export type ServerPayload =
  | { type: 'room'; data: RoomData }
  | { type: 'vitals'; data: VitalsData }
  | { type: 'text'; text: string; channel?: string }
  | { type: 'bg'; url: string }
  | { type: 'menu'; items: MenuItem[] };