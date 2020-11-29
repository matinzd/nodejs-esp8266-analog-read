const WebSocket = require("ws");

const PORT = 3000;

const server = new WebSocket.Server({
  host: "0.0.0.0",
  port: PORT,
  path: "/",
});

server.addListener("listening", () => {
  console.log("Websocket server listening on port %s", PORT);
});

server.on("connection", (connection) => {
  console.log("%s Connected", connection.remoteAddress);
  connection.on("message", (data) => {
    console.log("message from arduino ", data);
  });

  connection.on("close", (code, desc) => {
    console.log("connection closed", code, desc);
  });
});
