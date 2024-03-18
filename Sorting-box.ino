#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9 // Configurable, see typical pin layout above
#define SS_PIN 10 // Configurable, see typical pin layout above
#define SS_PIN2 6 // Chip select pin for the second reader
#define GREEN_LED_PIN 7 // Connect green LED to pin 7
#define RED_LED_PIN 8   // Connect red LED to pin 8
#define BLUE_LED_PIN 2  // Connect blue LED to pin 2
#define WHITE_LED_PIN 3 // Connect white LED to pin 3
#define CIRCLE_LED_PIN 4 // Connect circle LED to pin 4
#define RECTANGLE_LED_PIN 5 // Connect rectangle LED to pin 5

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance for the first reader
MFRC522 mfrc522_2(SS_PIN2, RST_PIN); // Create MFRC522 instance for the second reader

byte WhiteRect[] = {0xFD, 0xC1, 0xFF, 0x52}; // Array to store the target color 1 UID
byte BlueCirc[] = {0x74, 0x1E, 0x98, 0x85}; // Array to store the target color 2 UID

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial); // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 for the first reader
  mfrc522_2.PCD_Init(); // Init MFRC522 for the second reader
  delay(4); // Optional delay. Some boards need more time after init to be ready, see Readme

  pinMode(GREEN_LED_PIN, OUTPUT); // Set green LED pin as output
  pinMode(RED_LED_PIN, OUTPUT);   // Set red LED pin as output
  pinMode(BLUE_LED_PIN, OUTPUT);  // Set blue LED pin as output
  pinMode(WHITE_LED_PIN, OUTPUT); // Set white LED pin as output
  pinMode(CIRCLE_LED_PIN, OUTPUT); // Set circle LED pin as output
  pinMode(RECTANGLE_LED_PIN, OUTPUT); // Set rectangle LED pin as output

  digitalWrite(GREEN_LED_PIN, LOW); // Initially turn off green LED
  digitalWrite(RED_LED_PIN, LOW);   // Initially turn off red LED
  digitalWrite(BLUE_LED_PIN, LOW);  // Initially turn off blue LED
  digitalWrite(WHITE_LED_PIN, LOW); // Initially turn off white LED
  digitalWrite(CIRCLE_LED_PIN, LOW); // Initially turn off circle LED
  digitalWrite(RECTANGLE_LED_PIN, LOW); // Initially turn off rectangle LED

  randomSeed(analogRead(0)); // Seed the random number generator with a random value
  randomizeGame(WhiteRect, WhiteRect, BlueCirc, BlueCirc); // Set the target color and shape randomly
}

void loop() {
  int shape1Correct;
  int color1Correct;
  int shape2Correct;
  int color2Correct;
  // Check if both sets of color and shape LEDs are off
  if (!digitalRead(WHITE_LED_PIN) && !digitalRead(BLUE_LED_PIN) && !digitalRead(CIRCLE_LED_PIN) && !digitalRead(RECTANGLE_LED_PIN)) {
    Serial.println("Correct!");
    digitalWrite(GREEN_LED_PIN, HIGH); // Turn on green LED
    delay(1000);
    digitalWrite(GREEN_LED_PIN, LOW); // Turn off green LED
    randomizeGame(WhiteRect, WhiteRect, BlueCirc, BlueCirc); // Set a new target color and shape randomly
  }

  // Wait for a new card on the first reader
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Check if the UID matches the target color
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, WhiteRect)) {
      Serial.println("Correct color(White)!");
      digitalWrite(WHITE_LED_PIN, LOW); // Turn off white LED
    }
    else (checkTag(mfrc522_2.uid.uidByte, mfrc522_2.uid.size, WhiteRect));{
      Serial.println("Incorrect color(blue)");
      digitalWrite(RED_LED_PIN, HIGH); // Turn on red LED
      delay(1000);
      digitalWrite(RED_LED_PIN, LOW); // Turn off red LED
    }

    // Check if the UID matches the target shape
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, WhiteRect)) {
      Serial.println("Correct shape(rectangle)!");
      digitalWrite(RECTANGLE_LED_PIN, LOW); // Turn off rectangle LED
    }
    else (checkTag(mfrc522_2.uid.uidByte, mfrc522_2.uid.size, WhiteRect));{
      Serial.println("Incorrect shape(circle)");
      digitalWrite(RED_LED_PIN, HIGH); // Turn on red LED
      delay(1000);
      digitalWrite(RED_LED_PIN, LOW); // Turn off red LED
    }

    // Halt the card and proceed to the next iteration
    mfrc522.PICC_HaltA();
    delay(1000);
  }

  // Wait for a new card on the second reader
  if (mfrc522_2.PICC_IsNewCardPresent() && mfrc522_2.PICC_ReadCardSerial()) {

    if (checkTag(mfrc522_2.uid.uidByte, mfrc522_2.uid.size, BlueCirc)) {
      Serial.println("Correct color(blue)!");
      digitalWrite(BLUE_LED_PIN, LOW); // Turn off blue LED
    }
    else (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCirc));{
      Serial.println("Incorrect color(white)");
      digitalWrite(RED_LED_PIN, HIGH); // Turn on red LED
      delay(1000);
      digitalWrite(RED_LED_PIN, LOW); // Turn off red LED
    }

    // Check if the shape is correct
    if (checkTag(mfrc522_2.uid.uidByte, mfrc522_2.uid.size, BlueCirc)) {
      Serial.println("Correct shape(circle)!");
      digitalWrite(CIRCLE_LED_PIN, LOW); // Turn off circle LED
    }
    else (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCirc)); {
      Serial.println("Incorrect shape(rectangle)");
      digitalWrite(RED_LED_PIN, HIGH); // Turn on red LED
      delay(1000);
      digitalWrite(RED_LED_PIN, LOW); // Turn off red LED
    }

    // Halt the card and proceed to the next iteration
    mfrc522_2.PICC_HaltA();
    delay(1000);
  }
}

// Function to check RFID tag against the target
bool checkTag(byte* tagData, byte tagSize, byte* targetData) {
  return (memcmp(tagData, targetData, tagSize) == 0);
}

// Function to randomly set the target color and shape
void randomizeGame(byte* targetColor1, byte* targetShape1, byte* targetColor2, byte* targetShape2) {
  digitalWrite(BLUE_LED_PIN, LOW); // Turn off blue LED
  digitalWrite(WHITE_LED_PIN, LOW); // Turn off white LED
  digitalWrite(CIRCLE_LED_PIN, LOW); // Turn off circle LED
  digitalWrite(RECTANGLE_LED_PIN, LOW); // Turn off rectangle LED

  int randomOption = random(4); // Generate a random number from 0 to 3

  switch (randomOption) {
    case 0:
      memcpy(targetColor2, BlueCirc, sizeof(BlueCirc));
      digitalWrite(BLUE_LED_PIN, HIGH); // Turn on blue LED
      memcpy(targetShape2, BlueCirc, sizeof(BlueCirc));
      digitalWrite(CIRCLE_LED_PIN, HIGH); // Turn on circle LED
      Serial.println("Target color: Blue, Target shape: Circle");
      break;
    case 1:
      memcpy(targetColor2, BlueCirc, sizeof(BlueCirc));
      digitalWrite(BLUE_LED_PIN, HIGH); // Turn on blue LED
      memcpy(targetShape1, WhiteRect, sizeof(WhiteRect));
      digitalWrite(RECTANGLE_LED_PIN, HIGH); // Turn on rectangle LED
      Serial.println("Target color: Blue, Target shape: Rectangle");
      break;
    case 2:
      memcpy(targetColor1, WhiteRect, sizeof(WhiteRect));
      digitalWrite(WHITE_LED_PIN, HIGH); // Turn on white LED
      memcpy(targetShape2, BlueCirc, sizeof(BlueCirc));
      digitalWrite(CIRCLE_LED_PIN, HIGH); // Turn on circle LED
      Serial.println("Target color: White, Target shape: Circle");
      break;
    case 3:
      memcpy(targetColor1, WhiteRect, sizeof(WhiteRect));
      digitalWrite(WHITE_LED_PIN, HIGH); // Turn on white LED
      memcpy(targetShape1, WhiteRect, sizeof(WhiteRect));
      digitalWrite(RECTANGLE_LED_PIN, HIGH); // Turn on rectangle LED
      Serial.println("Target color: White, Target shape: Rectangle");
      break;
  }
}

