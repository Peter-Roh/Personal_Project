import { handleNewMessage } from "./chat.js";
import events from './events.js'

let socket = null;

export const getSocket = () => socket;

export const updateSocket = aSocket => (socket = aSocket);

export const initSockets = aSocket => {
    updateSocket(aSocket);
    aSocket.on(events.newMsg, handleNewMessage);
};
