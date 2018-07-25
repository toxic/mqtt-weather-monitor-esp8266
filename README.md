# mqtt-weather-monitor-esp8266


## Hardware
- Lolin NodeMCU v3 (base on ESP8266)
- DHT11 sensor (temperature & humidity)
- Arduino KY-018 Photo resistor module

## Software
- To work with ESP8266 you have to install [drivers](https://github.com/nodemcu/nodemcu-devkit/tree/master/Drivers).
- Arduino IDE
  Configure Arduino IDE to work with ESP module
  - Open File -> Preferences and find "Additional Boards Manager URLs" and copy/paste this url: http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open Tools -> Boards -> Boards Manager and install "esp826" board
  - Open Tools -> Board select "NodeMCU 1.0" module
  - In Tools double check board CPU is set to "80MGz" and upload speed is "115200"
  
  You have to install external libraries:
  - Adafruit MQTT Library
  - DHT Sensor Library
