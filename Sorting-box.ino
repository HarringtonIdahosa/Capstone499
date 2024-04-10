#include <SPI.h>
#include <MFRC522.h>

// Configurable, see typical pin layout 
#define RST_PIN 9 
#define SS_PIN 10 
// Define LED pins 
//Indicators
#define CORRECT_LED_PIN 7
#define INCORRECT_LED_PIN 8
//Colors
#define YELLOW_LED_PIN A0
#define BLUE_LED_PIN 2
#define RED_LED_PIN 13
#define ORANGE_LED_PIN 14
#define GREEN_LED_PIN 15
#define PURPLE_LED_PIN 16
//Shapes
#define CIRCLE_LED_PIN 4
#define RECTANGLE_LED_PIN 5
#define SQUARE_LED_PIN 6
#define DIAMOND_LED_PIN 10
#define STAR_LED_PIN 11
#define TRIANGLE_LED_PIN 12
//Define switch pins
#define RECTANGLE_SWITCH_PIN A1
#define CIRCLE_SWITCH_PIN A2
#define SQUARE_SWITCH_PIN A3
#define DIAMOND_SWITCH_PIN A4
#define STAR_SWITCH_PIN A5
#define TRIANGLE_SWITCH_PIN A6

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance for the RFID reader
   
// Array's to store the target UIDs

//Circle UID
byte BlueCircle[] = {0x74, 0x1E, 0x98, 0x85};
byte RedCircle[] = {0xAB, 0xCD, 0xEF, 0x01};
byte YellowCircle[] = {0x29, 0xC1, 0xBF, 0x7A};
byte OrangeCircle[] = {0x12, 0x34, 0x56, 0x78};
byte GreenCircle[] = {0x9A, 0xBC, 0xDE, 0xF0};
byte PurpleCircle[] = {0x45, 0x67, 0x89, 0x0A};

//Rectangle UID
byte BlueRectangle[] = {0xFD, 0xC1, 0xFF, 0x52};
byte RedRectangle[] = {0x1A, 0x2B, 0x3C, 0x4D};
byte YellowRectangle[] = {0xA4, 0x3D, 0x8F, 0x6A};
byte OrangeRectangle[] = {0x5E, 0x6F, 0x7A, 0x8B};
byte GreenRectangle[] = {0x9C, 0xAD, 0xBE, 0xCF};
byte PurpleRectangle[] = {0xD0, 0xE1, 0xF2, 0x03};

//Square UID
byte BlueSquare[] = {0x14, 0x25, 0x36, 0x47};
byte RedSquare[] = {0x58, 0x69, 0x7A, 0x8B};
byte YellowSquare[] = {0x9C, 0xAD, 0xBE, 0xCF};
byte OrangeSquare[] = {0xD0, 0xE1, 0xF2, 0x03};
byte GreenSquare[] = {0x14, 0x25, 0x36, 0x47};
byte PurpleSquare[] = {0x58, 0x69, 0x7A, 0x8B};

//Diamond UID
byte BlueDiamond[] = {0x9C, 0xAD, 0xBE, 0xCF};
byte RedDiamond[] = {0xD0, 0xE1, 0xF2, 0x03};
byte YellowDiamond[] = {0x14, 0x25, 0x36, 0x47};
byte OrangeDiamond[] = {0x58, 0x69, 0x7A, 0x8B};
byte GreenDiamond[] = {0x9C, 0xAD, 0xBE, 0xCF};
byte PurpleDiamond[] = {0xD0, 0xE1, 0xF2, 0x03};

//Star UID
byte BlueStar[] = {0x14, 0x25, 0x36, 0x47};
byte RedStar[] = {0x58, 0x69, 0x7A, 0x8B};
byte YellowStar[] = {0x9C, 0xAD, 0xBE, 0xCF};
byte OrangeStar[] = {0xD0, 0xE1, 0xF2, 0x03};
byte GreenStar[] = {0x14, 0x25, 0x36, 0x47};
byte PurpleStar[] = {0x58, 0x69, 0x7A, 0x8B};

//Triangle
byte BlueTriangle[] = {0x9C, 0xAD, 0xBE, 0xCF};
byte RedTriangle[] = {0xD0, 0xE1, 0xF2, 0x03};
byte YellowTriangle[] = {0x14, 0x25, 0x36, 0x47};
byte OrangeTriangle[] = {0x58, 0x69, 0x7A, 0x8B};
byte GreenTriangle[] = {0x9C, 0xAD, 0xBE, 0xCF};
byte PurpleTriangle[] = {0xD0, 0xE1, 0xF2, 0x03};
 
unsigned long lastInputTime = 0; // Variable to store the time of the last input

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial); // Do nothing if no serial port is opened 
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 for the first reader
  
  // Set all LED pins as outputs
  pinMode(CORRECT_LED_PIN, OUTPUT);
  pinMode(INCORRECT_LED_PIN, OUTPUT);
  
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN,OUTPUT);
  pinMode(ORANGE_LED_PIN,OUTPUT);
  pinMode(GREEN_LED_PIN,OUTPUT);
  pinMode(PURPLE_LED_PIN, OUTPUT);
  
  pinMode(CIRCLE_LED_PIN, OUTPUT);
  pinMode(RECTANGLE_LED_PIN, OUTPUT);
  pinMode(SQUARE_LED_PIN, OUTPUT);
  pinMode(DIAMOND_LED_PIN, OUTPUT);
  pinMode(STAR_LED_PIN, OUTPUT);
  pinMode(TRIANGLE_LED_PIN, OUTPUT);
  // Set button pin as input with internal pull-up resistor
  pinMode(RECTANGLE_SWITCH_PIN, INPUT_PULLUP);
  pinMode(CIRCLE_SWITCH_PIN, INPUT_PULLUP);
  pinMode(SQUARE_SWITCH_PIN, INPUT_PULLUP);
  pinMode(DIAMOND_SWITCH_PIN, INPUT_PULLUP);
  pinMode(STAR_SWITCH_PIN, INPUT_PULLUP);
  pinMode(TRIANGLE_SWITCH_PIN, INPUT_PULLUP);
  // Initially turn off output
  digitalWrite(CORRECT_LED_PIN, LOW);
  digitalWrite(INCORRECT_LED_PIN, LOW);
  
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(ORANGE_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(PURPLE_LED_PIN, LOW);
  
  digitalWrite(CIRCLE_LED_PIN, LOW);
  digitalWrite(RECTANGLE_LED_PIN, LOW);
  digitalWrite(SQUARE_LED_PIN, LOW);
  digitalWrite(DIAMOND_LED_PIN, LOW);
  digitalWrite(STAR_LED_PIN, LOW);
  digitalWrite(TRIANGLE_LED_PIN, LOW);

  randomizeGame(); // Set a new target color and shape randomly
}

void loop() {

// If both sets of color and shape LEDs are off the user is correct
  if (!digitalRead(BLUE_LED_PIN) && !digitalRead(YELLOW_LED_PIN)&& !digitalRead(RED_LED_PIN)&& !digitalRead(GREEN_LED_PIN)&& !digitalRead(ORANGE_LED_PIN)&& !digitalRead(PURPLE_LED_PIN) && !digitalRead(CIRCLE_LED_PIN) && !digitalRead(RECTANGLE_LED_PIN)&& !digitalRead(TRIANGLE_LED_PIN)&& !digitalRead(STAR_LED_PIN)&& !digitalRead(SQUARE_LED_PIN)&& !digitalRead(DIAMOND_LED_PIN)) {
    correct();
    randomizeGame(); 
  }

// If 3 minutes have passed, randomize the game
if (millis() - lastInputTime > 180000) {
      incorrect();
      randomizeGame(); 
      lastInputTime = millis(); // Reset the last input time
    }
//**RECTANGLE**
// RedRectangle
//Read if color & shape is present
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(RED_LED_PIN)) {
   //Check Tag & switch conditions
   if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedRectangle) && !digitalRead(RECTANGLE_SWITCH_PIN)) {
        //Turn off LED's
        digitalWrite(RED_LED_PIN, LOW); 
        digitalWrite(RECTANGLE_LED_PIN, LOW); 
        lastInputTime = millis(); //Reset the last input time 
    } else {
        incorrect(); //If conditions aren't met indicate
    } 
}

// OrangeRectangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(ORANGE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeRectangle) && !digitalRead(RECTANGLE_SWITCH_PIN)) {
        digitalWrite(ORANGE_LED_PIN, LOW); 
        digitalWrite(RECTANGLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// YellowRectangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(YELLOW_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowRectangle) && !digitalRead(RECTANGLE_SWITCH_PIN)) {
        digitalWrite(YELLOW_LED_PIN, LOW); 
        digitalWrite(RECTANGLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// GreenRectangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(GREEN_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenRectangle) && !digitalRead(RECTANGLE_SWITCH_PIN)) {
        digitalWrite(GREEN_LED_PIN, LOW); 
        digitalWrite(RECTANGLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// BlueRectangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(BLUE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueRectangle) && !digitalRead(RECTANGLE_SWITCH_PIN)) {  
        digitalWrite(BLUE_LED_PIN, LOW); 
        digitalWrite(RECTANGLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// PurpleRectangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(PURPLE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleRectangle) && !digitalRead(RECTANGLE_SWITCH_PIN)) {
        digitalWrite(PURPLE_LED_PIN, LOW); 
        digitalWrite(RECTANGLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}
//**CIRCLE**
// RedCircle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(RED_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedCircle) && !digitalRead(CIRCLE_SWITCH_PIN)) {
        digitalWrite(RED_LED_PIN, LOW); 
        digitalWrite(CIRCLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// OrangeCircle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(ORANGE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeCircle) && !digitalRead(CIRCLE_SWITCH_PIN)) {
        digitalWrite(ORANGE_LED_PIN, LOW); 
        digitalWrite(CIRCLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// YellowCircle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(YELLOW_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowCircle) && !digitalRead(CIRCLE_SWITCH_PIN)) {
        digitalWrite(YELLOW_LED_PIN, LOW); 
        digitalWrite(CIRCLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// GreenCircle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(GREEN_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenCircle) && !digitalRead(CIRCLE_SWITCH_PIN)) {
        digitalWrite(GREEN_LED_PIN, LOW); 
        digitalWrite(CIRCLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// BlueCircle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(BLUE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCircle) && !digitalRead(CIRCLE_SWITCH_PIN)) {  
        digitalWrite(BLUE_LED_PIN, LOW); 
        digitalWrite(CIRCLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// PurpleCircle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(PURPLE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleCircle) && !digitalRead(CIRCLE_SWITCH_PIN)) {
        digitalWrite(PURPLE_LED_PIN, LOW); 
        digitalWrite(CIRCLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

//**STAR**
// RedStar
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(STAR_LED_PIN) && digitalRead(RED_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedStar) && !digitalRead(STAR_SWITCH_PIN)) {
        digitalWrite(RED_LED_PIN, LOW); 
        digitalWrite(STAR_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// OrangeStar
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(STAR_LED_PIN) && digitalRead(ORANGE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeStar) && !digitalRead(STAR_SWITCH_PIN)) {
        digitalWrite(ORANGE_LED_PIN, LOW); 
        digitalWrite(STAR_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// YellowStar
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(STAR_LED_PIN) && digitalRead(YELLOW_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowStar) && !digitalRead(STAR_SWITCH_PIN)) {
        digitalWrite(YELLOW_LED_PIN, LOW); 
        digitalWrite(STAR_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// GreenStar
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(STAR_LED_PIN) && digitalRead(GREEN_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenStar) && !digitalRead(STAR_SWITCH_PIN)) {
        digitalWrite(GREEN_LED_PIN, LOW); 
        digitalWrite(STAR_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// BlueStar
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(STAR_LED_PIN) && digitalRead(BLUE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueStar) && !digitalRead(STAR_SWITCH_PIN)) {  
        digitalWrite(BLUE_LED_PIN, LOW); 
        digitalWrite(STAR_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// PurpleStar
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(STAR_LED_PIN) && digitalRead(PURPLE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleStar) && !digitalRead(STAR_SWITCH_PIN)) {
        digitalWrite(PURPLE_LED_PIN, LOW); 
        digitalWrite(STAR_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

//**DIAMOND**
// RedDiamnond
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(DIAMOND_LED_PIN) && digitalRead(RED_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedDiamond) && !digitalRead(DIAMOND_SWITCH_PIN)) {
        digitalWrite(RED_LED_PIN, LOW); 
        digitalWrite(DIAMOND_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// OrangeDiamnond
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(DIAMOND_LED_PIN) && digitalRead(ORANGE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeDiamond) && !digitalRead(DIAMOND_SWITCH_PIN)) {
        digitalWrite(ORANGE_LED_PIN, LOW); 
        digitalWrite(DIAMOND_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// YellowDiamnond
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(DIAMOND_LED_PIN) && digitalRead(YELLOW_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowDiamond) && !digitalRead(DIAMOND_SWITCH_PIN)) {
        digitalWrite(YELLOW_LED_PIN, LOW); 
        digitalWrite(DIAMOND_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// GreenDiamnond
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(DIAMOND_LED_PIN) && digitalRead(GREEN_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenDiamond) && !digitalRead(DIAMOND_SWITCH_PIN)) {
        digitalWrite(GREEN_LED_PIN, LOW); 
        digitalWrite(DIAMOND_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// BlueDiamnond
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(DIAMOND_LED_PIN) && digitalRead(BLUE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueDiamond) && !digitalRead(DIAMOND_SWITCH_PIN)) {  
        digitalWrite(BLUE_LED_PIN, LOW); 
        digitalWrite(DIAMOND_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// PurpleDiamnond
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(DIAMOND_LED_PIN) && digitalRead(PURPLE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleDiamond) && !digitalRead(DIAMOND_SWITCH_PIN)) {
        digitalWrite(PURPLE_LED_PIN, LOW); 
        digitalWrite(DIAMOND_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

//**TRIANGLE**
// RedTriangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(TRIANGLE_LED_PIN) && digitalRead(RED_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedTriangle) && !digitalRead(TRIANGLE_SWITCH_PIN)) {
        digitalWrite(RED_LED_PIN, LOW); 
        digitalWrite(TRIANGLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// OrangeTriangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(TRIANGLE_LED_PIN) && digitalRead(ORANGE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeTriangle) && !digitalRead(TRIANGLE_SWITCH_PIN)) {
        digitalWrite(ORANGE_LED_PIN, LOW); 
        digitalWrite(TRIANGLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// YellowTriangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(TRIANGLE_LED_PIN) && digitalRead(YELLOW_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowTriangle) && !digitalRead(TRIANGLE_SWITCH_PIN)) {
        digitalWrite(YELLOW_LED_PIN, LOW); 
        digitalWrite(TRIANGLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// GreenTriangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(TRIANGLE_LED_PIN) && digitalRead(GREEN_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenTriangle) && !digitalRead(TRIANGLE_SWITCH_PIN)) {
        digitalWrite(GREEN_LED_PIN, LOW); 
        digitalWrite(TRIANGLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// BlueTriangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(TRIANGLE_LED_PIN) && digitalRead(BLUE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueTriangle) && !digitalRead(TRIANGLE_SWITCH_PIN)) {  
        digitalWrite(BLUE_LED_PIN, LOW); 
        digitalWrite(TRIANGLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// PurpleTriangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(TRIANGLE_LED_PIN) && digitalRead(PURPLE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleTriangle) && !digitalRead(TRIANGLE_SWITCH_PIN)) {
        digitalWrite(PURPLE_LED_PIN, LOW); 
        digitalWrite(TRIANGLE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

//**SQUARE**
// RedSquare
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(SQUARE_LED_PIN) && digitalRead(RED_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedSquare) && !digitalRead(SQUARE_SWITCH_PIN)) {
        digitalWrite(RED_LED_PIN, LOW); 
        digitalWrite(SQUARE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// OrangeSquare
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(SQUARE_LED_PIN) && digitalRead(ORANGE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeSquare) && !digitalRead(SQUARE_SWITCH_PIN)) {
        digitalWrite(ORANGE_LED_PIN, LOW); 
        digitalWrite(SQUARE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// YellowSquare
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(SQUARE_LED_PIN) && digitalRead(YELLOW_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowSquare) && !digitalRead(SQUARE_SWITCH_PIN)) {
        digitalWrite(YELLOW_LED_PIN, LOW); 
        digitalWrite(SQUARE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// GreenSquare
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(SQUARE_LED_PIN) && digitalRead(GREEN_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenSquare) && !digitalRead(SQUARE_SWITCH_PIN)) {
        digitalWrite(GREEN_LED_PIN, LOW); 
        digitalWrite(SQUARE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// BlueSquare
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(SQUARE_LED_PIN) && digitalRead(BLUE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueSquare) && !digitalRead(SQUARE_SWITCH_PIN)) {  
        digitalWrite(BLUE_LED_PIN, LOW); 
        digitalWrite(SQUARE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}

// PurpleSquare
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(SQUARE_LED_PIN) && digitalRead(PURPLE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleSquare) && !digitalRead(SQUARE_SWITCH_PIN)) {
        digitalWrite(PURPLE_LED_PIN, LOW); 
        digitalWrite(SQUARE_LED_PIN, LOW); 
        lastInputTime = millis(); 
    } else {
        incorrect();
    } 
}


} //end of loop

// Function to check RFID tag against the target
bool checkTag(byte* tagData, byte tagSize, byte* targetData) {
  return (memcmp(tagData, targetData, tagSize) == 0);
}

// Function to randomly set the target color and shape
void randomizeGame() {
   // Initially Turn off game LED's
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(ORANGE_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(PURPLE_LED_PIN, LOW);
  
  digitalWrite(CIRCLE_LED_PIN, LOW);
  digitalWrite(RECTANGLE_LED_PIN, LOW);
  digitalWrite(SQUARE_LED_PIN, LOW);
  digitalWrite(DIAMOND_LED_PIN, LOW);
  digitalWrite(STAR_LED_PIN, LOW);
  digitalWrite(TRIANGLE_LED_PIN, LOW);
  randomSeed(analogRead(36)); // Seed the random number generator with a random value

switch (random(36)) {
    //LED case's
      case 0:
      digitalWrite(BLUE_LED_PIN, HIGH); 
      digitalWrite(CIRCLE_LED_PIN, HIGH); 
      Serial.println("Target color: Blue, Target shape: Circle");
      break;
      case 1:
      digitalWrite(YELLOW_LED_PIN, HIGH); 
      digitalWrite(CIRCLE_LED_PIN, HIGH); 
      Serial.println("Target color: Yellow, Target shape: Circle");
      break;
      case 2:
      digitalWrite(ORANGE_LED_PIN, HIGH); 
      digitalWrite(CIRCLE_LED_PIN, HIGH); 
      Serial.println("Target color: Orange, Target shape: Circle");
      break;
      case 3:
      digitalWrite(RED_LED_PIN, HIGH); 
      digitalWrite(CIRCLE_LED_PIN, HIGH); 
      Serial.println("Target color: Red, Target shape: Circle");
      break;
      case 4:
      digitalWrite(GREEN_LED_PIN, HIGH); 
      digitalWrite(CIRCLE_LED_PIN, HIGH); 
      Serial.println("Target color: Green, Target shape: Circle");
      break;
      case 5:
      digitalWrite(PURPLE_LED_PIN, HIGH); 
      digitalWrite(CIRCLE_LED_PIN, HIGH); 
      Serial.println("Target color: Purple, Target shape: Circle");
      break;
      case 6:
      digitalWrite(BLUE_LED_PIN, HIGH); 
      digitalWrite(RECTANGLE_LED_PIN, HIGH);
      Serial.println("Target color: Blue, Target shape: Rectangle");
      break;
      case 7:
      digitalWrite(YELLOW_LED_PIN, HIGH);
      digitalWrite(RECTANGLE_LED_PIN, HIGH); 
      Serial.println("Target color: Yellow, Target shape: Rectangle");
      break;
      case 8:
      digitalWrite(ORANGE_LED_PIN, HIGH);
      digitalWrite(RECTANGLE_LED_PIN, HIGH); 
      Serial.println("Target color: Orange, Target shape: Rectangle");
      break;
      case 9:
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(RECTANGLE_LED_PIN, HIGH); 
      Serial.println("Target color: Red, Target shape: Rectangle");
      break;
      case 10:
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(RECTANGLE_LED_PIN, HIGH); 
      Serial.println("Target color: Green, Target shape: Rectangle");
      break;
      case 11:
      digitalWrite(PURPLE_LED_PIN, HIGH);
      digitalWrite(RECTANGLE_LED_PIN, HIGH); 
      Serial.println("Target color: Purple, Target shape: Rectangle");
      break;
      case 12:
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(STAR_LED_PIN, HIGH); 
      Serial.println("Target color: Blue, Target shape: Star");
      break;
      case 13:
      digitalWrite(YELLOW_LED_PIN, HIGH);
      digitalWrite(STAR_LED_PIN, HIGH); 
      Serial.println("Target color: Yellow, Target shape: Star");
      break;
      case 14:
      digitalWrite(ORANGE_LED_PIN, HIGH);
      digitalWrite(STAR_LED_PIN, HIGH); 
      Serial.println("Target color: Orange, Target shape: Star");
      break;
      case 15:
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(STAR_LED_PIN, HIGH); 
      Serial.println("Target color: Red, Target shape: Star");
      break;
      case 16:
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(STAR_LED_PIN, HIGH); 
      Serial.println("Target color: Green, Target shape: Star");
      break;
      case 17:
      digitalWrite(PURPLE_LED_PIN, HIGH);
      digitalWrite(STAR_LED_PIN, HIGH); 
      Serial.println("Target color: Purple, Target shape: Star");
      break;
      case 18:
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(SQUARE_LED_PIN, HIGH); 
      Serial.println("Target color: Blue, Target shape: Square");
      break;
      case 19:
      digitalWrite(YELLOW_LED_PIN, HIGH);
      digitalWrite(SQUARE_LED_PIN, HIGH); 
      Serial.println("Target color: Yellow, Target shape: Square");
      break;
      case 20:
      digitalWrite(ORANGE_LED_PIN, HIGH);
      digitalWrite(SQUARE_LED_PIN, HIGH); 
      Serial.println("Target color: Orange, Target shape: Square");
      break;
       case 21:
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(SQUARE_LED_PIN, HIGH); 
      Serial.println("Target color: Red, Target shape: Square");
      break;
      case 22:
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(SQUARE_LED_PIN, HIGH); 
      Serial.println("Target color: Green, Target shape: Square");
      break;
      case 23:
      digitalWrite(PURPLE_LED_PIN, HIGH);
      digitalWrite(SQUARE_LED_PIN, HIGH); 
      Serial.println("Target color: Purple, Target shape: Square");
      break;
      case 24:
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(DIAMOND_LED_PIN, HIGH); 
      Serial.println("Target color: Blue, Target shape: Diamond");
      break;
      case 25:
      digitalWrite(YELLOW_LED_PIN, HIGH);
      digitalWrite(DIAMOND_LED_PIN, HIGH); 
      Serial.println("Target color: Yellow, Target shape: Diamond");
      break;
      case 26:
      digitalWrite(ORANGE_LED_PIN, HIGH);
      digitalWrite(DIAMOND_LED_PIN, HIGH); 
      Serial.println("Target color: Orange, Target shape: Diamond");
      break;
      case 27:
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(DIAMOND_LED_PIN, HIGH); 
      Serial.println("Target color: Red, Target shape: Diamond");
      break;
      case 28:
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(DIAMOND_LED_PIN, HIGH); 
      Serial.println("Target color: Green, Target shape: Diamond");
      break;
      case 29:
      digitalWrite(PURPLE_LED_PIN, HIGH);
      digitalWrite(DIAMOND_LED_PIN, HIGH); 
      Serial.println("Target color: Purple, Target shape: Diamond");
      break;
      case 30:
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(TRIANGLE_LED_PIN, HIGH); 
      Serial.println("Target color: Blue, Target shape: Triangle");
      break;
      case 31:
      digitalWrite(YELLOW_LED_PIN, HIGH);
      digitalWrite(TRIANGLE_LED_PIN, HIGH); 
      Serial.println("Target color: Yellow, Target shape: Triangle");
      break;
      case 32:
      digitalWrite(ORANGE_LED_PIN, HIGH);
      digitalWrite(TRIANGLE_LED_PIN, HIGH); 
      Serial.println("Target color: Orange, Target shape: Triangle");
      break;
      case 33:
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(TRIANGLE_LED_PIN, HIGH); 
      Serial.println("Target color: Red, Target shape: Triangle");
      break;
      case 34:
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(TRIANGLE_LED_PIN, HIGH); 
      Serial.println("Target color: Green, Target shape: Triangle");
      break;
      case 35:
      digitalWrite(PURPLE_LED_PIN, HIGH);
      digitalWrite(TRIANGLE_LED_PIN, HIGH); 
      Serial.println("Target color: Purple, Target shape: Triangle");
      break;
 }
}
// Correct indicator
void correct() {
    Serial.println("Correct");
    digitalWrite(CORRECT_LED_PIN, HIGH); 
    delay(1000);
    digitalWrite(CORRECT_LED_PIN, LOW); 
}
// Incorrect indicator
void incorrect() {
    Serial.println("Incorrect");
    digitalWrite(INCORRECT_LED_PIN, HIGH); 
    delay(1000);
    digitalWrite(INCORRECT_LED_PIN, LOW); 
}
