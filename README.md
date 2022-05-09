# IoT RFID door lock
Internet of things created using ***arduino IoT cloud***, consisting of esp and arduino boards. It makes a 3D printed RFID protected (with PIN) lock. There is also a surveillance system. (Raspberry Pi integration planned)

# Setup
- ESP8266 (ESP12E) -> controls door lock mechanism
- Arduino uno -> controls RFID scanner and keypad
- ESP32 cam -> controls surveillance system and sends arduino data to cloud

# Specific information
- [ESP used for door lock](/Door%20lock%20ESP/Information.md)
- [Arduino used for scanning cards and inputting PIN](/Arduino%20UID%20scanner%20with%20PIN/Information.md)