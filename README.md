# NodeJS ESP8266 WebSocket 
This is a simple Arduino project to send voltage status of A0 input pin (connected to potatiometer) to NodeJS application over WebSocket using ESP8266 on vemos d1 board.

## Requirements

- NodeJS 10 or higher 
- Yarn (Optional)
- Git
- Arduino IDE

## Installation

1- Starting WebSocket Server

```
git clone https://github.com/matinzd/nodejs-esp8266-analog-read.git
cd nodejs-esp8266-analog-read
npm i // or yarn
node ./src/app.js
```

2- Starting Arduino Project

Open file below with the Arduino IDE:
```
arduino/project/project.imo
```

3- Connect second pin of potantiometer to A0 pin and connect two other pins to 5v and gnd


