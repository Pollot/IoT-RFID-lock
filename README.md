# IoT RFID door lock
Internet of things created using ***arduino IoT cloud***, consisting of esp and arduino boards. It makes a 3D printed RFID protected (with PIN) lock. There is also a surveillance system with database stored on a locally based raspberry pi.

# Setup
- ESP8266 (ESP12E) -> controls door lock mechanism
- Arduino uno -> controls RFID scaner with numpad and sends data over to ESP32
- ESP32 cam -> controls surveillance system and sends arduino data to cloud
- Raspberry Pi

# Additional information
- [ESP used for door lock](/Door%20lock%20ESP/Information.md) 