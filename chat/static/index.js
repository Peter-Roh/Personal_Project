import { initSockets } from "./sockets.js";

const socket = io("/");

initSockets(socket);
