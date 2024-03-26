#include <WiFi.h>
#include <WebServer.h>

#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

String show = "home";

byte rowPins[ROWS] = {13, 12, 14, 27};
byte colPins[COLS] = {26, 25, 33, 32};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//const char* ssid = "Corbin's WIFI";
//const char* password = "e4chn78dsfsdf7";

const char* ssid = "moto g stylus (2022)_9156";
const char* password = "Ilove3Dart";

int mainDelay = 3000;

unsigned long previousMillis = 0;
int interval = mainDelay;

int page = 0;

WebServer server(80);

const int rs = 15, en = 16, d4 = 17, d5 = 18, d6 = 19, d7 = 23;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int MAX_TEXTS = 10;

String projectName[MAX_TEXTS] = {"placeholder 1", "placeholder 2", "placeholder 3", "placeholder 4", "placeholder 5", "placeholder 6", "placeholder 7", "placeholder 8", "placeholder 9", "placeholder 10"};
String color[MAX_TEXTS] = {"placeholder 1", "placeholder 2", "placeholder 3", "placeholder 4", "placeholder 5", "placeholder 6", "placeholder 7", "placeholder 8", "placeholder 9", "placeholder 10"};
String filePrintTime[MAX_TEXTS] = {"placeholder 1", "placeholder 2", "placeholder 3", "placeholder 4", "placeholder 5", "placeholder 6", "placeholder 7", "placeholder 8", "placeholder 9", "placeholder 10"};
String filamentType[MAX_TEXTS] = {"placeholder 1", "placeholder 2", "placeholder 3", "placeholder 4", "placeholder 5", "placeholder 6", "placeholder 7", "placeholder 8", "placeholder 9", "placeholder 10"};
String otherInfo[MAX_TEXTS] = {"placeholder 1", "placeholder 2", "placeholder 3", "placeholder 4", "placeholder 5", "placeholder 6", "placeholder 7", "placeholder 8", "placeholder 9", "placeholder 10"};

String defaultHome[MAX_TEXTS] = {"Is Filament the Right Color", "Is the temperature Pre-Set", "Does the File need supports", "Does the file need a brim", "Is the file going to run over night", "[D] = set delay", "[C] = clear/home", "[#] = enter, [A] = Show IP", "Please keep powered on always", "IP address: " + WiFi.localIP().toString()};

int currentTextIndex = 0;

#include "webpages.h"

void setup() {
  Serial.begin(115200);

  lcd.begin(16, 2); // Initialize the LCD
  lcd.print("Initializing...");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  delay(1500);
  lcd.clear();
  lcd.print("Connecting to WiFi...");
  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.println("Connected to WiFi");

  // Start server
  server.on("/", HTTP_GET, handleRoot);
  server.on("/sendInfo", HTTP_POST, handleInfo);
  server.on("/qrCode", HTTP_GET, handleQrCode);
  server.on("/setInfo", HTTP_GET, handleSetInfoProject);
  server.on("/showInfo", HTTP_GET, handleShowInfo);

  server.begin();
  Serial.println("Server started");

  lcd.clear();
  lcd.print("Connected to WiFi");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP().toString());
  defaultHome[9] = WiFi.localIP().toString();
  delay(2000);
}

void loop() {
  char key = keypad.getKey();
  showInfoOnScreen();
  if (key) {
    if (key >= '0' && key <= '9') {
      show = key;
    }
    if (String(key) == "A") {
      lcd.clear();
      lcd.print(WiFi.localIP().toString());
      delay(mainDelay);
    } else if (String(key) == "D") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set Delay: {#}");
      lcd.setCursor(0, 1);
      String setDelay = "";
      while (true) {
        char key = keypad.getKey();
        if (key) {
          if (key >= '0' && key <= '9') {
            lcd.print(key);
            setDelay += key;
          }

          if (String(key) == "#") {
            break;
          }

          if (String(key) == "C") {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Set Delay: {#}");
            lcd.setCursor(0, 1);

            setDelay = "";
          }
          delay(100);
        }
      }
      mainDelay = setDelay.toInt();
      interval = mainDelay;

      Serial.print("set delay to: ");
      Serial.println(setDelay);
    } else if (String(key) == "C") {
      show = "home";
    }
  }
  server.handleClient();
}



void showInfoOnScreen() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (show == "home") {
      // Display default home text
      lcd.clear();
      lcd.print(defaultHome[currentTextIndex].substring(0, 16));
      lcd.setCursor(0, 1);
      lcd.print(defaultHome[currentTextIndex].substring(16));

      currentTextIndex = (currentTextIndex + 1) % MAX_TEXTS;
    } else if (show >= "0" && show <= "9") {
      page++;
      int projectIndex = show.toInt();

      if (page == 1) {
        printProjectPage(projectName[projectIndex], ", colr:", color[projectIndex]);

      } else if (page == 2) {
        printProjectPage(projectName[projectIndex], ", prt tme:", filePrintTime[projectIndex]);

      } else if (page == 3) {
        printProjectPage(projectName[projectIndex], ", Fil tpe:", filamentType[projectIndex]);

      } else if (page == 4) {
        String info = otherInfo[projectIndex];
        int infoLength = info.length();
        int displayLength = 16;
        for (int i = 0; i <= infoLength - displayLength; i++) {
          printProjectPage(projectName[projectIndex], ", othr:", info.substring(i, i + displayLength));
          delay(500);
        }
        if (infoLength % displayLength != 0) {
          printProjectPage(projectName[projectIndex], ", othr:", info.substring(infoLength - (infoLength % displayLength)));
        }

      } else if (page == 5) {
        lcd.clear();
        lcd.print("Scan QR code ");
        lcd.setCursor(0, 1);
        lcd.print("for more info");

      } else if (page == 6) {
        String message = "or goto: " + WiFi.localIP().toString() + "/qrCode";

        lcd.clear();
        lcd.print(message.substring(0, 16));
        lcd.setCursor(0, 1);
        lcd.print(message.substring(16));

      } else {
        page = 0;
      }
    }
  }
}



void printProjectPage(String Name, String filler, String content) {
  lcd.clear();
  lcd.print("N: ");
  lcd.print(Name);
  lcd.print(filler);
  lcd.setCursor(0, 1);
  lcd.print(content);
}
