# IoT RFID door lock
Internet of things created using **arduino IoT cloud**, consisting of:
- 2 x ESP8266
- Arduino mega 
- ESP32 cam.

Goal of the project is to create a 3D printed RFID protected (with PIN) lock, with surveillance. 

I used cloud in order to control project outside from local network, without need to forward any port. It's also great for integration with different projects, and additional control from web based dashboard.

(Raspberry Pi integration planned)

# Setup
- 1st ESP8266 (ESP12E) -> controls door lock mechanism
- Arduino mega -> controls RFID scanner, keypad and lcd display
- 2nd ESP8266 (ESP12E) -> sends arduino mega data to IoT cloud 
- ESP32 cam -> surveillance system

# Specific information
- [ESP used for door lock](/Door%20lock%20ESP/Information.md)
- [Arduino used for scanning cards and inputting PIN](/Arduino%20UID%20scanner%20with%20PIN/Information.md)
- [ESP used for sending access data from arduino to cloud](/ESP%20communicating%20with%20arduino/Information.md)