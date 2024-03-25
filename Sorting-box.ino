#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9 // Configurable, see typical pin layout above
#define SS_PIN 10 // Configurable, see typical pin layout above
#define CORRECT_LED_PIN 7 // Connect green LED to pin 7
#define INCORRECT_LED_PIN 8   // Connect red LED to pin 8
#define BLUE_LED_PIN 2  // Connect blue LED to pin 2
#define WHITE_LED_PIN 3 // Connect white LED to pin 3
#define CIRCLE_LED_PIN 4 // Connect circle LED to pin 4
#define RECTANGLE_LED_PIN 5 // Connect rectangle LED to pin 5
#define YELLOW_LED_PIN A0

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
byte targetColor[4]; // Array to store the target color UID
byte targetShape[4]; // Array to store the target shape UID

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial); // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  

  pinMode(CORRECT_LED_PIN, OUTPUT); // Set green LED pin as output
  pinMode(INCORRECT_LED_PIN, OUTPUT);   // Set red LED pin as output
  pinMode(BLUE_LED_PIN, OUTPUT);  // Set blue LED pin as output
  pinMode(WHITE_LED_PIN, OUTPUT); // Set white LED pin as output
  pinMode(CIRCLE_LED_PIN, OUTPUT); // Set circle LED pin as output
  pinMode(RECTANGLE_LED_PIN, OUTPUT); // Set rectangle LED pin as output
  pinMode(YELLOW_LED_PIN, OUTPUT); 
  
  digitalWrite(CORRECT_LED_PIN, 0); // Initially turn off green LED
  digitalWrite(INCORRECT_LED_PIN, 0);   // Initially turn off red LED
  digitalWrite(BLUE_LED_PIN, 0);  // Initially turn off blue LED
  digitalWrite(WHITE_LED_PIN, 0); // Initially turn off white LED
  digitalWrite(CIRCLE_LED_PIN, 0); // Initially turn off circle LED
  digitalWrite(RECTANGLE_LED_PIN, 0); // Initially turn off rectangle LED
  digitalWrite(YELLOW_LED_PIN, 0); 
  
  randomSeed(analogRead(0)); // Seed the random number generator with a random value
  randomizeGame(); // Set the target color and shape randomly
}

void loop() {
  // Wait for a new card
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    bool colorcorrect = 0;
    bool shapecorrect = 0;

    // Check if the UID matches the target color
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, targetColor)) {
      Serial.println("Correct color!");
      digitalWrite(BLUE_LED_PIN, 0); // Turn off blue LED
      digitalWrite(WHITE_LED_PIN, 0); // Turn off white LED
      digitalWrite(YELLOW_LED_PIN, 0); //
      colorCorrect = 1;
    }

    // Check if the UID matches the target shape
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, targetShape)) {
     Serial.println("Correct shape!");
     digitalWrite(CIRCLE_LED_PIN, 0); // Turn off circle LED
     digitalWrite(RECTANGLE_LED_PIN, 0); // Turn off rectangle LED
     shapecorrect = 1;
    }

    // Check if both color and shape are correct
    if (colorcorrect & shapecorrect) {
     Serial.println("Correct!");
     digitalWrite(CORRECT_LED_PIN, 1); // Turn on green LED
      delay(1000);
      digitalWrite(CORRECT_LED_PIN, 0);
      randomizeGame(); // Set a new target color and shape randomly
    } else if (!colorcorrect & !shapecorrect) {
      // Neither color nor shape is correct
      Serial.println("Incorrect! Try again.");
      digitalWrite(INCORRECT_LED_PIN, 1); // Turn on red LED
      delay(1000);
      digitalWrite(INCORRECT_LED_PIN, 0);
    }

    
   
  }
}

// Function to check RFID tag against the target
bool checkTag(byte* tagData, byte tagSize, byte* targetData) {
  return (memcmp(tagData, targetData, tagSize) == 0);
}

// Function to randomly set the target color and shape
void randomizeGame() {
  digitalWrite(BLUE_LED_PIN, 0); // Turn off blue LED
  digitalWrite(WHITE_LED_PIN, 0); // Turn off white LED
  digitalWrite(CIRCLE_LED_PIN, 0); // Turn off circle LED
  digitalWrite(RECTANGLE_LED_PIN, 0); // Turn off rectangle LED
  digitalWrite(YELLOW_LED_PIN,0);
  //*Circle UID
  byte bluecircle[] = {0x74, 0x1E, 0x98, 0x85}; 
  //byte redcircle[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte yellowcircle[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte orangecircle[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte greencircle[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte prurplecircle[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  
  //*RectangleUID's
  byte whiterect[] = {0xFD, 0xC1, 0xFF, 0x52}; 
  //byte redrect[] = {0xXX, 0xXX, 0xXX, 0xXX};
  byte yellowrect[]={0xA4, 0x3D, 0x8F, 0x6A};
  //byte orangerect[]={0xXX, 0xXX, 0xXX, 0xXX};
  //byte greenrect[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte purplerect[]={0xXX, 0xXX, 0xXX, 0xXX};
  
  //*Square UID
  //byte bluesquare[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte redsquare[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte yellowsquare[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte orangesquare[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte greensquare[] = {0xXX, 0xXX, 0xXX, 0xXX};
  //byte purplesquare[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  
  //*Diamond UID
  //byte bluediamond[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte reddiamond[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte yellowediamond[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte orangediamond[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte greendiamond[] = {0xXX, 0xXX, 0xXX, 0xXX};
  //byte purplediamond[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  
  //*Star UID
  //byte bluestar[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte redstar[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte yellowstar[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte orangestar[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte greenstar[] = {0xXX, 0xXX, 0xXX, 0xXX};
  //byte purplestar[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  
  //*Triangle
  //byte bluetriangle[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte redtriangle[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte yellowtriangle[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte orangetriangle[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
  //byte greentriangle[] = {0xXX, 0xXX, 0xXX, 0xXX};
  //byte purpletriangle[] = {0xXX, 0xXX, 0xXX, 0xXX}; 
 
  int randomOption = random(3); // Generate a random number from 0 to 3

  switch (randomOption) {
    case 0:
      memcpy(targetColor, bluecircle, sizeof(bluecircle));
      digitalWrite(BLUE_LED_PIN, 1); // Turn on blue LED
      memcpy(targetShape, bluecircle, sizeof(bluecircle));
      digitalWrite(CIRCLE_LED_PIN, 1); // Turn on circle LED
      Serial.println("Target color: Blue, Target shape: Circle");
      break;
    
    case 1:
      memcpy(targetColor, whiterect, sizeof(whiterect));
      digitalWrite(WHITE_LED_PIN, 1); // Turn on white LED
      memcpy(targetShape, whiterect, sizeof(whiterect));
      digitalWrite(RECTANGLE_LED_PIN, 1); // Turn on rectangle LED
      Serial.println("Target color: White, Target shape: Rectangle");
      break;
      case 2:
      memcpy(targetColor, yellowrect, sizeof(yellowrect));
      digitalWrite(YELLOW_LED_PIN, 1); // Turn on white LED
      memcpy(targetShape, yellowrect, sizeof(yellowrect));
      digitalWrite(RECTANGLE_LED_PIN, 1); // Turn on rectangle LED
      Serial.println("Target color: Yellow, Target shape: Rectangle");
      break;

  }
}

