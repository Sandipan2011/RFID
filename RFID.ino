#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9

#define GREEN_LED 2
#define RED_LED 3
#define BUZZER 4

// LCD with I2C backpack (address can be 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Allowed card UIDs (keep them uppercase and spaced like the reader outputs)
String allowedUIDs[] = {
  "2E F3 2D 03",   // Card 0 -> limited
  "71 8B B0 02"    // Card 1 -> INFINITE access
};

// Usage counter for each card (same order). For the infinite card the counter is unused.
int usageCount[] = {0, 0};
const int maxUsage = 20;

// Index of the infinite-access card in the allowedUIDs array
const int INFINITE_INDEX = 1;

void setup() {
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  // Convert UID to string (hex with leading zero and spaces)
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) content += "0";
    content += String(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) content += " ";
  }
  content.toUpperCase();

  Serial.print("Card UID: ");
  Serial.println(content);

  lcd.clear();
  lcd.print("Checking...");
  delay(400);
  lcd.clear();

  // Find the UID in allowed list
  bool valid = false;
  int cardIndex = -1;
  int allowedCount = sizeof(allowedUIDs) / sizeof(allowedUIDs[0]);
  for (int i = 0; i < allowedCount; i++) {
    if (content == allowedUIDs[i]) {
      valid = true;
      cardIndex = i;
      break;
    }
  }

  if (valid) {
    // If this is the infinite access card, always grant without incrementing usage
    if (cardIndex == INFINITE_INDEX) {
      lcd.setCursor(0, 0);
      lcd.print("Access Granted");
      lcd.setCursor(0, 1);
      lcd.print("Unlimited");
      Serial.println("Access granted");

      digitalWrite(GREEN_LED, HIGH);
      tone(BUZZER, 1000, 200);
      delay(800);
      digitalWrite(GREEN_LED, LOW);
    } else {
      // Limited card logic
      if (usageCount[cardIndex] < maxUsage) {
        usageCount[cardIndex]++;
        int remaining = maxUsage - usageCount[cardIndex];

        lcd.setCursor(0, 0);
        lcd.print("Access Granted");
        lcd.setCursor(0, 1);
        lcd.print("Left: ");
        lcd.print(remaining);

        Serial.print("Card usage: ");
        Serial.print(usageCount[cardIndex]);
        Serial.print("/");
        Serial.println(maxUsage);

        digitalWrite(GREEN_LED, HIGH);
        tone(BUZZER, 1000, 200);
        delay(800);
        digitalWrite(GREEN_LED, LOW);
      } else {
        lcd.setCursor(0, 0);
        lcd.print("Access Denied");
        lcd.setCursor(0, 1);
        lcd.print("Limit Reached");
        Serial.println("Access Denied - Limit Reached for this card");

        for (int i = 0; i < 5; i++) {
          digitalWrite(RED_LED, HIGH);
          tone(BUZZER, 1000, 200);
          delay(300);
          digitalWrite(RED_LED, LOW);
          delay(200);
        }
      }
    }
  } else {
    // Unknown card
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    lcd.setCursor(0, 1);
    lcd.print("Unknown Card");
    Serial.println("Access Denied - Unknown card");

    for (int i = 0; i < 5; i++) {
      digitalWrite(RED_LED, HIGH);
      tone(BUZZER, 1000, 200);
      delay(300);
      digitalWrite(RED_LED, LOW);
      delay(200);
    }
  }

  delay(1600);
  lcd.clear();
  lcd.print("Scan Your Card");
}
