#include <SPI.h>
#include <MFRC522.h>

// Configurable, see typical pin layout 
#define RST_PIN 9 
#define SS_PIN 10 
// Define LED pins 
#define CORRECT_LED_PIN 7 
#define INCORRECT_LED_PIN 8  
#define YELLOW_LED_PIN A0 
#define BLUE_LED_PIN 2  
#define WHITE_LED_PIN 3 
#define CIRCLE_LED_PIN 4 
#define RECTANGLE_LED_PIN 5 
// Define switch pins
#define RECTANGLE_SWITCH_PIN A1 
#define CIRCLE_SWITCH_PIN A2 

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance for the reader

// Array to store the target UIDs
byte WhiteRect[] = {0xFD, 0xC1, 0xFF, 0x52}; 
byte YellowRect[] = {0xA4, 0x3D, 0x8F, 0x6A}; 
byte BlueCirc[] = {0x74, 0x1E, 0x98, 0x85}; 
byte YellowCirc[] = {0x29, 0xC1, 0xBF, 0x7A}; 

unsigned long lastInputTime = 0; // Variable to store the time of the last input

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial); // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 for the first reader
  
  // Set all LED pins as outputs
  pinMode(CORRECT_LED_PIN, OUTPUT); 
  pinMode(INCORRECT_LED_PIN, OUTPUT);   
  pinMode(BLUE_LED_PIN, OUTPUT);  
  pinMode(YELLOW_LED_PIN, OUTPUT);  
  pinMode(WHITE_LED_PIN, OUTPUT);
  pinMode(CIRCLE_LED_PIN, OUTPUT);
  pinMode(RECTANGLE_LED_PIN, OUTPUT); 
  // Set button pin as input with internal pull-up resistor
  pinMode(RECTANGLE_SWITCH_PIN, INPUT_PULLUP); 
  pinMode(CIRCLE_SWITCH_PIN, INPUT_PULLUP); 
  // Initially turn off output
  digitalWrite(CORRECT_LED_PIN, LOW); 
  digitalWrite(INCORRECT_LED_PIN, LOW);  
  digitalWrite(YELLOW_LED_PIN, LOW);  
  digitalWrite(BLUE_LED_PIN, LOW);  
  digitalWrite(WHITE_LED_PIN, LOW); 
  digitalWrite(CIRCLE_LED_PIN, LOW); 
  digitalWrite(RECTANGLE_LED_PIN, LOW); 

  randomizeGame(); // Set a new target color and shape randomly
}

void loop() {

// Check if both sets of color and shape LEDs are off
  if (!digitalRead(WHITE_LED_PIN) && !digitalRead(BLUE_LED_PIN) && !digitalRead(YELLOW_LED_PIN) && !digitalRead(CIRCLE_LED_PIN) && !digitalRead(RECTANGLE_LED_PIN)) {
    Serial.println("Correct!");
    digitalWrite(CORRECT_LED_PIN, HIGH); // Correct indicator
    delay(1000);
    digitalWrite(CORRECT_LED_PIN, LOW); 
    randomizeGame(); // Set a new target color and shape randomly
  }

// If 3 minutes have passed, randomize the game
if (millis() - lastInputTime > 180000) {
      digitalWrite(INCORRECT_LED_PIN, HIGH); // Incorrect indicator
      delay(1000);
      digitalWrite(INCORRECT_LED_PIN, LOW); 
      randomizeGame(); 
      lastInputTime = millis(); // Reset the last input time
    }

  //WhiteRectangle
  while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(WHITE_LED_PIN)) {
  //Check Tag & switch conditions
   if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, WhiteRect) && !digitalRead(RECTANGLE_SWITCH_PIN)) {  
      Serial.println("Correct (White Rectangle)");
      digitalWrite(WHITE_LED_PIN, LOW); 
      digitalWrite(RECTANGLE_LED_PIN, LOW); 
      lastInputTime = millis(); // Reset the last input time
    } else {
      digitalWrite(INCORRECT_LED_PIN, HIGH); // Incorrect indicator
      delay(1000);
      digitalWrite(INCORRECT_LED_PIN, LOW); 
    } 
  }

  //YellowRectangle
  while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(YELLOW_LED_PIN) ) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowRect) && !digitalRead(RECTANGLE_SWITCH_PIN)){
      Serial.println("Correct (Yellow Rectangle)!");
      digitalWrite(YELLOW_LED_PIN, LOW); 
      digitalWrite(RECTANGLE_LED_PIN, LOW); 
      lastInputTime = millis(); 
    } else {
      digitalWrite(INCORRECT_LED_PIN, HIGH);  
      delay(1000);
      digitalWrite(INCORRECT_LED_PIN, LOW); 
    } 
  }
//BlueCircle
  while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(BLUE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCirc) && !digitalRead(CIRCLE_SWITCH_PIN)) {
      Serial.println("Correct (blue circle)!");
      digitalWrite(BLUE_LED_PIN, LOW); 
      digitalWrite(CIRCLE_LED_PIN, LOW); 
      lastInputTime = millis(); 
    } else {
      digitalWrite(INCORRECT_LED_PIN, HIGH); 
      delay(1000);
      digitalWrite(INCORRECT_LED_PIN, LOW); 
    }
  }
//YellowCircle
  while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(YELLOW_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowCirc) && !digitalRead(CIRCLE_SWITCH_PIN)) {
      Serial.println("Correct (Yellow circle)!");
      digitalWrite(YELLOW_LED_PIN, LOW); 
      digitalWrite(CIRCLE_LED_PIN, LOW); 
      lastInputTime = millis(); 
    } else {
      digitalWrite(INCORRECT_LED_PIN, HIGH); 
      delay(1000);
      digitalWrite(INCORRECT_LED_PIN, LOW); 
    }
  }


}

// Function to check RFID tag against the target
bool checkTag(byte* tagData, byte tagSize, byte* targetData) {
  return (memcmp(tagData, targetData, tagSize) == 0);
}

// Function to randomly set the target color and shape
void randomizeGame() {
   // Initially Turn off game LED's
  digitalWrite(YELLOW_LED_PIN, LOW); 
  digitalWrite(BLUE_LED_PIN, LOW); 
  digitalWrite(WHITE_LED_PIN, LOW); 
  digitalWrite(CIRCLE_LED_PIN, LOW); 
  digitalWrite(RECTANGLE_LED_PIN, LOW); 
  randomSeed(analogRead(4)); // Seed the random number generator with a random value

switch (random(4)) {
    //LED case's
    case 0:
      digitalWrite(BLUE_LED_PIN, HIGH); 
      digitalWrite(CIRCLE_LED_PIN, HIGH); 
      Serial.println("Target color: Blue, Target shape: Circle");
      break;
    case 1:
      digitalWrite(WHITE_LED_PIN, HIGH); 
      digitalWrite(RECTANGLE_LED_PIN, HIGH);
      Serial.println("Target color: White, Target shape: Rectangle");
      break;
    case 2:
      digitalWrite(YELLOW_LED_PIN, HIGH);
      digitalWrite(RECTANGLE_LED_PIN, HIGH); 
      Serial.println("Target color: Yellow, Target shape: Rectangle");
      break;
    case 3:
      digitalWrite(YELLOW_LED_PIN, HIGH); 
      digitalWrite(CIRCLE_LED_PIN, HIGH); 
      Serial.println("Target color: Yellow, Target shape: Circle");
      break;
  }
}


