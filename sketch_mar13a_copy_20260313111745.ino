#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
const int pirPin = 3;
const int gasPin = A0;
const int flamePin = 2;   // Flame sensor (DO pin)
const int buzzer = 4;
const int ledPin = 5;

// Variables
int motionState = 0;
int gasValue = 0;
int flameState = 0;

void setup() {
  Serial.begin(9600);

  pinMode(pirPin, INPUT);
  pinMode(flamePin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);

  lcd.begin();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Smart Room");
  lcd.setCursor(0, 1);
  lcd.print("Safety System");
  delay(2000);
  lcd.clear();
}

void loop() {

  // Read sensors
  motionState = digitalRead(pirPin);
  gasValue = analogRead(gasPin);
  flameState = digitalRead(flamePin);

  // Default display
  lcd.setCursor(0, 0);
  lcd.print("System Running ");

  // Motion detection
  if (motionState == HIGH) {
    lcd.setCursor(0, 1);
    lcd.print("Motion Detected ");
    digitalWrite(ledPin, HIGH);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("No Motion       ");
    digitalWrite(ledPin, LOW);
  }

  // Gas detection
  if (gasValue > 400) {
    lcd.setCursor(0, 1);
    lcd.print("Gas Leakage!    ");
    digitalWrite(buzzer, HIGH);
  }

  // Flame detection
  if (flameState == LOW) {  // LOW = flame detected
    lcd.setCursor(0, 1);
    lcd.print("🔥 FIRE ALERT!   ");
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledPin, HIGH);
  }

  // If everything normal
  if (gasValue <= 400 && flameState == HIGH) {
    digitalWrite(buzzer, LOW);
  }

  delay(500);
}