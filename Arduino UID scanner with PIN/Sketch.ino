#include <Keypad.h>  // https://playground.arduino.cc/Code/Keypad/
#include <LiquidCrystal.h>
#include <MFRC522.h>  // https://github.com/miguelbalboa/rfid
#include <SPI.h>

// RFID scanner setup:
#define ssPin 53  // SS
#define rstPin 48

// UID of my authorized cards:
String card1 = "C3 23 36 40";
String card2 = "A9 22 60 C2";

MFRC522 mfrc522(ssPin, rstPin);  // Create MFRC522 instance

// Keypad setup:
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {37, 35, 33, 31};
byte colPins[COLS] = {29, 27, 25, 23};

Keypad pinKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// LCD setup:
#define RS 2
#define E 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

#define rLED 9
#define gLED 10

// Variables:
char key;  // Stores pressed key

const int length = 4;                       // Password length (needed)
const int maxLength = 24;                   // Max possible length of input (I use lcd width)
const char password[length + 1] = " 1234";  // !!! Password as an array, leave password[0] blank (first character needs to be a space)
char input[maxLength];
int inputNumber = 0;
int correct = 0;

void setup() {
    Serial.begin(9600);

    lcd.begin(24, 2);

    pinMode(rLED, OUTPUT);
    pinMode(gLED, OUTPUT);

    SPI.begin();         // Initiate SPI bus
    mfrc522.PCD_Init();  // Initiate MFRC522
}

void loop() {
    lcd.print("Scan your card");

    if (!mfrc522.PICC_IsNewCardPresent()) {  // Look for new cards
        lcd.clear();
        return;
    }
    if (!mfrc522.PICC_ReadCardSerial()) {
        lcd.clear();
        return;
    }

    // Reading card UID in HEX:
    String content;
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

    // Printing card UID:
    lcd.clear();
    lcd.print("UID: ");
    content.toUpperCase();
    lcd.print(content.substring(1));

    lcd.setCursor(0, 1);

    if (content.substring(1) == card1 || content.substring(1) == card2) {
        lcd.print("Authorized!");
        digitalWrite(gLED, HIGH);
        delay(2000);
        digitalWrite(gLED, LOW);
    } else {
        lcd.print("Denied!");
        digitalWrite(rLED, HIGH);
        delay(4000);
        digitalWrite(rLED, LOW);
        lcd.clear();
        return;
    }

    lcd.clear();
    lcd.print("Input PIN:");
    lcd.setCursor(0, 1);

    while (inputNumber < maxLength) {
        key = pinKeypad.getKey();

        if (key == '#' || key == '*')  // You can confirm password using those characters
            break;

        if (key) {
            inputNumber++;
            lcd.print(key);
            input[inputNumber] = key;  // Input pressed key into array
        }
    }

    for (int i = 1; i <= length; i++) {
        if (password[i] == input[i])
            correct++;
        else
            break;
    }

    if (correct == length && inputNumber == length) {  // Lenght of inputted passwords need to be same as well as amount of correct characters
        lcd.clear();
        lcd.print("Correct!");
        Serial.write(1);  // Sends data to ESP
        success();
        Serial.write(1);  // Additional data, just in case
        delay(10000);
        lcd.clear();
        lcd.print("Locking door...");
        Serial.write(0);  // After 10 seconds, door will close
        delay(2000);
        Serial.write(0);  // Additional data, just in case
    } else {
        lcd.clear();
        lcd.print("Incorrect! ");
        fail();
    }

    /*// Debugging for testing:
    Serial.print("Correct = ");
    Serial.println(correct);
    Serial.print("Input number = ");
    Serial.println(inputNumber);
    Serial.println();
    for (int i = 0; i <= length; i++)
    {
      Serial.print("Array number = ");
      Serial.println(i);
      Serial.print("Password = ");
      Serial.println(password[i]);
      Serial.print("Input = ");
      Serial.println(input[i]);
      Serial.println();
    }*/

    reset();
}

void success() {
    for (int i = 0; i < 15; i++) {
        digitalWrite(gLED, HIGH);
        delay(200);
        digitalWrite(gLED, LOW);
        delay(200);
    }
}

void fail() {
    for (int i = 0; i < 20; i++) {
        digitalWrite(rLED, HIGH);
        delay(200);
        digitalWrite(rLED, LOW);
        delay(200);
    }
}

void reset() {
    lcd.clear();
    inputNumber = 0;
    correct = 0;
}