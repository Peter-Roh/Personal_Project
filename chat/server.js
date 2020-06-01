import express from 'express';
import socketIO from 'socket.io';
import logger from 'morgan';
import socketController from './socketController.js';

const PORT = 5000;
const app = express();

app.engine("html", require('ejs').renderFile);
app.set('view engine', 'html');
app.use(logger("dev"));
app.use(express.static('assets'))
app.use(express.static('static'));
app.use(express.static('styles'));
app.get('/', (req, res) => res.render('index'));

const handleListening = () => console.log(`✅ Server running: http://localhost:${PORT}`);

const server = app.listen(PORT, handleListening);

const io = socketIO.listen(server);

io.on("connection", socket => socketController(socket, io));
