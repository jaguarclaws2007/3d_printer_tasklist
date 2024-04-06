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
String lastEdited[MAX_TEXTS] = {"never", "never", "never", "never", "never", "never", "never", "never", "never", "never"};

String defaultHome[MAX_TEXTS] = {"Is Filament the Right Color", "Is the temperature Pre-Set", "Does the File need supports", "Does the file need a brim", "Is the file going to run over night", "[C] = clr/home, [D] = set delay", "[#] = enter, [A] = Show IP", "Please keep powered on always", "IP address: " + WiFi.localIP().toString(), "NAP"};

int amtOfActiveProjects = 0;
String activeProjects[MAX_TEXTS] = {"No Active Projects via activeProjects"};
bool showingActiveProjects = true;

int currentTextIndex = 0;

bool activelyShowingProjects = false;

String urlEncode(const String &str) {
  String encodedString = "";
  char c;
  char code0;
  char code1;
  for (unsigned int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if ((c >= '0' && c <= '9') ||
               (c >= 'A' && c <= 'Z') ||
               (c >= 'a' && c <= 'z')) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
    }
  }
  encodedString.replace("+", "%20");
  return encodedString;
}

void getActiveProjects() {
  int currentIndex = 0;
  for (int i = 0; i < MAX_TEXTS; i++) {
    if (lastEdited[i] != "never") {
      activeProjects[currentIndex] = "Press " + String(i) + " for: " + projectName[i];
      currentIndex++;
    }
  }
  amtOfActiveProjects = currentIndex;
}

#include "credentials.h"
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

  server.on("/CHPP", HTTP_GET, handleChangeHomePresetsPage);
  server.on("/CHP", HTTP_POST, handleChangeHomePresets);

  server.begin();
  Serial.println("Server started");

  lcd.clear();
  lcd.print("Connected to WiFi");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP().toString());
  defaultHome[8] = WiFi.localIP().toString();
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
      page = 0;
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
      if ((currentTextIndex == 9 && showingActiveProjects == true) || (activelyShowingProjects == true)) {
        activelyShowingProjects = true;
        if (page >= 0 && page <= amtOfActiveProjects-1) {
          Serial.println("Showing Progress List");
          Serial.println(page);
          Serial.println(amtOfActiveProjects);
          Serial.println(activeProjects[page]);

          lcd.clear();
          lcd.print(activeProjects[page].substring(0, 16));
          lcd.setCursor(0, 1);
          lcd.print(activeProjects[page].substring(16));
          page++;
        } else {
          page = 0;
          activelyShowingProjects = false;
          currentTextIndex = (currentTextIndex + 1) % MAX_TEXTS;
        }
      } else {
        lcd.clear();
        lcd.print(defaultHome[currentTextIndex].substring(0, 16));
        lcd.setCursor(0, 1);
        lcd.print(defaultHome[currentTextIndex].substring(16));
        currentTextIndex = (currentTextIndex + 1) % MAX_TEXTS;
      }
    } else if (show >= "0" && show <= "9") {
      page++;
      int projectIndex = show.toInt();

      if (page == 1) {
        printProjectPage(projectName[projectIndex], "", "C: " + color[projectIndex]);

      } else if (page == 2) {
        printProjectPage(projectName[projectIndex], "", "T: " + filePrintTime[projectIndex]);

      } else if (page == 3) {
        printProjectPage(projectName[projectIndex], "", "FT: " + filamentType[projectIndex]);

      } else if (page == 4) {
        String info = "O: " + otherInfo[projectIndex];
        int infoLength = info.length();
        int displayLength = 16;
        for (int i = 0; i <= infoLength - displayLength; i++) {
          printProjectPage(projectName[projectIndex], "", info.substring(i, i + displayLength));
          delay(500);
        }
        if (infoLength % displayLength != 0) {
          printProjectPage(projectName[projectIndex], "", info.substring(infoLength - (infoLength % displayLength)));
        }

      } else if (page == 5) {
        lcd.clear();
        lcd.print("Scan QR code ");
        lcd.setCursor(0, 1);
        lcd.print("for more info");

      } else if (page == 6) {
        String message = "Or goto: " + WiFi.localIP().toString() + "/qrCode";

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
