import { getSocket } from "./sockets.js";
import events from './events.js';

const ul = document.getElementById("chat__messages");
const sendMessage = document.getElementById("chat__send");

const appendMsg = (text, author) => {
    const li = document.createElement("li");
    li.innerHTML = `
        <span class="author ${author ? "out" : "self"}"><span class="user">${author ? author : "You"}: </span>${text}</span>
    `;
    if(!author) {
        li.style.textAlign = 'right';
    }
    ul.appendChild(li);
    ul.scrollTop = ul.scrollHeight;
};

const handleSendMsg = (event) => {
    event.preventDefault();
    const input = sendMessage.querySelector("input");
    const {value} = input;
    getSocket().emit(events.sendMsg, { message: value });
    input.value = "";
    appendMsg(value);
};

export const handleNewMessage = ({message, author}) => appendMsg(message, author);

if(sendMessage) {
    sendMessage.addEventListener("submit", handleSendMsg);
}
