import events from './events';

const socketController = socket => {
    const broadcast = (event, data) => socket.broadcast.emit(event, data);

    socket.on(events.sendMsg, ({ message }) => {
    broadcast(events.newMsg, { message, author: "Anon" });
    });
};

export default socketController;
