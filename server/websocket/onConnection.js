/**
 * Event listener for WebSocket server "connection" event.
 */
module.exports = function (socket) {
  socket.on('typedKeyboad', function (data) {
    console.log(data + "[" + socket.id + "]");
    socket.broadcast.emit('typedKeyboad', data + "[" + socket.id + "]");
  });

  socket.on('disconnect', function () {
    
  });
};
