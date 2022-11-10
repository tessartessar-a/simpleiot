# simpleiot


One simple example of using IoT at home or we can call home automation. I use MQTT as data transmit from server to client, in this case 
Raspberry pi is the server and Microcontroller or ESP8266 is the client. 

Presequite: 
Microcontroller( in my case I use ESP8266). 
1. Install Arduino IDE (I use 1.8x version). 
2. install some libraries: 
  - ESP8266WiFi ( https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
  - WiFiManager ( https://github.com/tzapu/WiFiManager)
  - PubSubClient( https://github.com/knolleary/pubsubclient)
3. Upload to your board!

Server(Any PC but I prefered use raspberry pi 3)

1. Update your system (sudo apt update on terminal)
2. Install mosquitto broker
3. Install Flask
4. Install Paho-MQTT



