# C++ WebSocket Server

Simple C++ WebSocket server that broadcasts fake positional data (latitude, longitude) to connected clients. The server uses the `websocketpp` library for WebSocket functionality and the `boost` library for additional support.

## Quick Start

1. Install packages:

   ```bash
   # Ubuntu
   sudo apt-get update
   sudo apt-get install -y g++ libwebsocketpp-dev libboost-all-dev

   # Macos
   brew update
   brew install websocketpp boost
   ```

2. Compile

   ```bash
   make
   ```

3. Run

   ```
   make run
   ```

This sets up the server, which listens to incoming Websocket connections on Port 9002.
