/**
 * Event listener for WebSocket server "connection" event.
 */
module.exports = function (socket) {
  socket.emit('news', { hello: 'world' });
  
  socket.on('my other event', function (data) {
    console.log(data);
  });

  socket.on('disconnect', function () {
    
  });
};
