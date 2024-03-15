#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9 // Connect RST pin to pin 9
#define SS_PIN 10 // Connect SS pin to pin 10
#define GREEN_LED_PIN 7 // Connect green LED to pin 7
#define RED_LED_PIN 8   // Connect red LED to pin 8
#define BLUE_LED_PIN 2  // Connect blue LED to pin 2
#define WHITE_LED_PIN 3 // Connect white LED to pin 3
#define CIRCLE_LED_PIN 4 // Connect circle LED to pin 4
#define RECTANGLE_LED_PIN 5 // Connect rectangle LED to pin 5

MFRC522 mfrc522(SS_PIN, RST_PIN);
byte targetColor[4]; // Array to store the target color UID
byte targetShape[4]; // Array to store the target shape UID

void setup() {
  //Initialization
  Serial.begin(9600); 
  while (!Serial); // Do nothing if no serial port is opened
  SPI.begin(); 
  mfrc522.PCD_Init(); 
  delay(4); //Board needs time after initializing to be ready.

 //Set LED pins as output
  pinMode(GREEN_LED_PIN, OUTPUT); 
  pinMode(RED_LED_PIN, OUTPUT);   
  pinMode(BLUE_LED_PIN, OUTPUT);  
  pinMode(WHITE_LED_PIN, OUTPUT); 
  pinMode(CIRCLE_LED_PIN, OUTPUT); 
  pinMode(RECTANGLE_LED_PIN, OUTPUT); 

  //Initially turn off LEDs
  digitalWrite(GREEN_LED_PIN, LOW); 
  digitalWrite(RED_LED_PIN, LOW);   
  digitalWrite(BLUE_LED_PIN, LOW);  
  digitalWrite(WHITE_LED_PIN, LOW); 
  digitalWrite(CIRCLE_LED_PIN, LOW); 
  digitalWrite(RECTANGLE_LED_PIN, LOW); 

  randomSeed(analogRead(0)); // Seed the random number generator with a random value
  randomizeGame(); // Set the target color and shape randomly
}

void loop() {
  // Wait for a new card
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    bool colorCorrect = false;
    bool shapeCorrect = false;

    // Check if the UID matches the target color
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, targetColor)) {
      Serial.println("Correct color!");
      digitalWrite(BLUE_LED_PIN, LOW); // Turn off blue LED
      digitalWrite(WHITE_LED_PIN, LOW); // Turn off white LED
      colorCorrect = true;
    }

    // Check if the UID matches the target shape
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, targetShape)) {
      Serial.println("Correct shape!");
     
     digitalWrite(CIRCLE_LED_PIN, LOW); // Turn off circle LED
     digitalWrite(RECTANGLE_LED_PIN, LOW); // Turn off rectangle LED
      shapeCorrect = true;
    }

    // Check if both color and shape are correct
    if (colorCorrect && shapeCorrect) {
      Serial.println("Correct!");
      digitalWrite(GREEN_LED_PIN, HIGH); // Turn on green LED
      delay(1000);
      digitalWrite(GREEN_LED_PIN, LOW);
      randomizeGame(); // Set a new target color and shape randomly
    } else if (!colorCorrect && !shapeCorrect) {
      // Neither color nor shape is correct
      Serial.println("Incorrect! Try again.");
      digitalWrite(RED_LED_PIN, HIGH); // Turn on red LED
      delay(1000);
      digitalWrite(RED_LED_PIN, LOW);
    }

    if (!digitalRead(BLUE_LED_PIN) && !digitalRead(WHITE_LED_PIN) && !digitalRead(CIRCLE_LED_PIN) && !digitalRead(RECTANGLE_LED_PIN)) {
      Serial.println("Correct!");
      digitalWrite(GREEN_LED_PIN, HIGH); // Turn on green LED
      delay(1000);
      digitalWrite(GREEN_LED_PIN, LOW);
      randomizeGame(); // Set a new target color and shape randomly
    }
    // Halt the card and proceed to the next iteration
    mfrc522.PICC_HaltA();
    delay(1000); // delay to avoid rapid reads
  }
}

// check RFID tag against the target
bool checkTag(byte* tagData, byte tagSize, byte* targetData) {
  return (memcmp(tagData, targetData, tagSize) == 0);
}

// Function to randomly set the target color and shape
void randomizeGame() {
 // Turn off LED's
  digitalWrite(BLUE_LED_PIN, LOW); 
  digitalWrite(WHITE_LED_PIN, LOW); 
  digitalWrite(CIRCLE_LED_PIN, LOW); 
  digitalWrite(RECTANGLE_LED_PIN, LOW); 

  byte blueTag[] = {0x74, 0x1E, 0x98, 0x85}; // Blue tag UID (circle)
  byte whiteTag[] = {0xFD, 0xC1, 0xFF, 0x52}; // White tag UID (rectangle)

  int randomOption = random(4); // Generate a random number from 0 to 3

  switch (randomOption) {
    case 0:
      memcpy(targetColor, blueTag, sizeof(blueTag));
      digitalWrite(BLUE_LED_PIN, HIGH); // Turn on blue LED
      memcpy(targetShape, blueTag, sizeof(blueTag));
      digitalWrite(CIRCLE_LED_PIN, HIGH); // Turn on circle LED
      Serial.println("Target color: Blue, Target shape: Circle");
      break;
    case 1:
      memcpy(targetColor, blueTag, sizeof(blueTag));
      digitalWrite(BLUE_LED_PIN, HIGH); // Turn on blue LED
      memcpy(targetShape, whiteTag, sizeof(whiteTag));
      digitalWrite(RECTANGLE_LED_PIN, HIGH); // Turn on rectangle LED
      Serial.println("Target color: Blue, Target shape: Rectangle");
      break;
    case 2:
      memcpy(targetColor, whiteTag, sizeof(whiteTag));
      digitalWrite(WHITE_LED_PIN, HIGH); // Turn on white LED
      memcpy(targetShape, blueTag, sizeof(blueTag));
      digitalWrite(CIRCLE_LED_PIN, HIGH); // Turn on circle LED
      Serial.println("Target color: White, Target shape: Circle");
      break;
    case 3:
      memcpy(targetColor, whiteTag, sizeof(whiteTag));
      digitalWrite(WHITE_LED_PIN, HIGH); // Turn on white LED
      memcpy(targetShape, whiteTag, sizeof(whiteTag));
      digitalWrite(RECTANGLE_LED_PIN, HIGH); // Turn on rectangle LED
      Serial.println("Target color: White, Target shape: Rectangle");
      break;
  }
}

