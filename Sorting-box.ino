#include <SPI.h>
#include <MFRC522.h>

// Configurable, see typical pin layout 
#define RST_PIN 9 
#define SS_PIN 10 
// Define LED pins 
//Indicators
#define CORRECT_LED_PIN 7
#define INCORRECT_COLOR_LED_PIN 8  
#define INCORRECT_SHAPE_LED_PIN 19
#define INCORRECT_HOLE_LED_PIN 17  
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
  pinMode(INCORRECT_SHAPE_LED_PIN, OUTPUT);   
  pinMode(INCORRECT_HOLE_LED_PIN, OUTPUT);   
  pinMode(INCORRECT_COLOR_LED_PIN, OUTPUT);   

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
  digitalWrite(INCORRECT_SHAPE_LED_PIN, LOW);  
  digitalWrite(INCORRECT_COLOR_LED_PIN, LOW);  
  digitalWrite(INCORRECT_HOLE_LED_PIN, LOW);  

  
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

bool colorcorrect=0;
bool shapecorrect=0;

// If 3 minutes have passed with no input, randomize the game
if (millis() - lastInputTime > 180000) {
      flashled();
      flashled();
      flashled();
      flashled();
      randomizeGame(); 
    }
   
//**RECTANGLE**
// RedRectangle
//Read if color & shape is present
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(RED_LED_PIN)) {
   //Check Tag 
   if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedRectangle) ) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleRectangle)) {  
     shapecorrect = 1; 
    }  
    //Check conditions
    if (shapecorrect&&colorcorrect && !digitalRead(RECTANGLE_SWITCH_PIN)) {  
    correct(); //Correct
    }
    if (!colorcorrect) {  
    incorrectcolor(); //Wrong color
    }if (!shapecorrect) {  
    incorrectshape(); //Wrong shape
    }if (digitalRead(RECTANGLE_SWITCH_PIN)){
    incorrecthole(); //Wrong hole
    } 
}

// OrangeRectangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(ORANGE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeRectangle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleRectangle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(RECTANGLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(RECTANGLE_SWITCH_PIN)){
    incorrecthole();
    } 
}

// YellowRectangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(YELLOW_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowRectangle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleRectangle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(RECTANGLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(RECTANGLE_SWITCH_PIN)){
    incorrecthole();
    } 
}

// GreenRectangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(GREEN_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenRectangle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleRectangle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(RECTANGLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(RECTANGLE_SWITCH_PIN)){
    incorrecthole();
    } 
}

// BlueRectangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(BLUE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueRectangle)) {  
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleRectangle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(RECTANGLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(RECTANGLE_SWITCH_PIN)){
    incorrecthole();
    } 
}

// PurpleRectangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(RECTANGLE_LED_PIN) && digitalRead(PURPLE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleRectangle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenRectangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedRectangle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(RECTANGLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(RECTANGLE_SWITCH_PIN)){
    incorrecthole();
    }  
}
//**CIRCLE**
// RedCircle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(RED_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedCircle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleCircle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(CIRCLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(CIRCLE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// OrangeCircle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(ORANGE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeCircle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleCircle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(CIRCLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(CIRCLE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// YellowCircle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(YELLOW_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowCircle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleCircle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(CIRCLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(CIRCLE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// GreenCircle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(GREEN_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenCircle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleCircle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(CIRCLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(CIRCLE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// BlueCircle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(BLUE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCircle)) {  
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleCircle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(CIRCLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(CIRCLE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// PurpleCircle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(CIRCLE_LED_PIN) && digitalRead(PURPLE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleCircle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenCircle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedCircle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(CIRCLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(CIRCLE_SWITCH_PIN)){
    incorrecthole();
    }  
}

//**STAR**
// RedStar
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(STAR_LED_PIN) && digitalRead(RED_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedStar)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleStar)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(STAR_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(STAR_SWITCH_PIN)){
    incorrecthole();
    }  
}

// OrangeStar
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(STAR_LED_PIN) && digitalRead(ORANGE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeStar)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleStar)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(STAR_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(STAR_SWITCH_PIN)){
    incorrecthole();
    }  
}

// YellowStar
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(STAR_LED_PIN) && digitalRead(YELLOW_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowStar)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleStar)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(STAR_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(STAR_SWITCH_PIN)){
    incorrecthole();
    }  
}

// GreenStar
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(STAR_LED_PIN) && digitalRead(GREEN_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenStar)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleStar)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(STAR_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(STAR_SWITCH_PIN)){
    incorrecthole();
    }  
}

// BlueStar
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(STAR_LED_PIN) && digitalRead(BLUE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueStar)) {  
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleStar)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(STAR_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(STAR_SWITCH_PIN)){
    incorrecthole();
    }  
}

// PurpleStar
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(STAR_LED_PIN) && digitalRead(PURPLE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleStar)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenStar)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedStar)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(STAR_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(STAR_SWITCH_PIN)){
    incorrecthole();
    }  
}

//**DIAMOND**
// RedDiamnond
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(DIAMOND_LED_PIN) && digitalRead(RED_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedDiamond)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleDiamond)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(DIAMOND_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(DIAMOND_SWITCH_PIN)){
    incorrecthole();
    }  
}

// OrangeDiamnond
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(DIAMOND_LED_PIN) && digitalRead(ORANGE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeDiamond)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleDiamond)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(DIAMOND_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(DIAMOND_SWITCH_PIN)){
    incorrecthole();
    }  
}

// YellowDiamnond
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(DIAMOND_LED_PIN) && digitalRead(YELLOW_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowDiamond)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleDiamond)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(DIAMOND_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(DIAMOND_SWITCH_PIN)){
    incorrecthole();
    }  
}

// GreenDiamnond
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(DIAMOND_LED_PIN) && digitalRead(GREEN_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenDiamond)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleDiamond)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(DIAMOND_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(DIAMOND_SWITCH_PIN)){
    incorrecthole();
    }  
}

// BlueDiamnond
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(DIAMOND_LED_PIN) && digitalRead(BLUE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueDiamond)) {  
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleDiamond)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(DIAMOND_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(DIAMOND_SWITCH_PIN)){
    incorrecthole();
    }  
}

// PurpleDiamnond
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(DIAMOND_LED_PIN) && digitalRead(PURPLE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleDiamond)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenDiamond)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedDiamond)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(DIAMOND_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(DIAMOND_SWITCH_PIN)){
    incorrecthole();
    }  
}

//**TRIANGLE**
// RedTriangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(TRIANGLE_LED_PIN) && digitalRead(RED_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedTriangle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleTriangle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(TRIANGLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(TRIANGLE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// OrangeTriangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(TRIANGLE_LED_PIN) && digitalRead(ORANGE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeTriangle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleTriangle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(TRIANGLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(TRIANGLE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// YellowTriangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(TRIANGLE_LED_PIN) && digitalRead(YELLOW_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowTriangle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleTriangle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(TRIANGLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(TRIANGLE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// GreenTriangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(TRIANGLE_LED_PIN) && digitalRead(GREEN_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenTriangle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleTriangle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(TRIANGLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(TRIANGLE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// BlueTriangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(TRIANGLE_LED_PIN) && digitalRead(BLUE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueTriangle)) {  
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleTriangle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(TRIANGLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(TRIANGLE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// PurpleTriangle
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(TRIANGLE_LED_PIN) && digitalRead(PURPLE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleTriangle)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleSquare)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenTriangle)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedTriangle)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(TRIANGLE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(TRIANGLE_SWITCH_PIN)){
    incorrecthole();
    }  
}

//**SQUARE**
// RedSquare
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(SQUARE_LED_PIN) && digitalRead(RED_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedSquare)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleSquare)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(SQUARE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(SQUARE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// OrangeSquare
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(SQUARE_LED_PIN) && digitalRead(ORANGE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeSquare)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleSquare)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(SQUARE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(SQUARE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// YellowSquare
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(SQUARE_LED_PIN) && digitalRead(YELLOW_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowSquare)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleSquare)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(SQUARE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(SQUARE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// GreenSquare
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(SQUARE_LED_PIN) && digitalRead(GREEN_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenSquare)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleSquare)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(SQUARE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(SQUARE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// BlueSquare
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(SQUARE_LED_PIN) && digitalRead(BLUE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueSquare)) {  
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleSquare)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(SQUARE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(SQUARE_SWITCH_PIN)){
    incorrecthole();
    }  
}

// PurpleSquare
while (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && digitalRead(SQUARE_LED_PIN) && digitalRead(PURPLE_LED_PIN)) {
    if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleSquare)) {
    colorcorrect = 1; 
    shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleRectangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleCircle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleDiamond)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleTriangle)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, PurpleStar)) {  
    colorcorrect = 1;
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, YellowSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, BlueSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, OrangeSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, GreenSquare)) {  
     shapecorrect = 1; 
    }else if (checkTag(mfrc522.uid.uidByte, mfrc522.uid.size, RedSquare)) {  
     shapecorrect = 1; 
    }  

    if (shapecorrect&&colorcorrect && !digitalRead(SQUARE_SWITCH_PIN)) {  
    correct();
    }
    if (!colorcorrect) {  
    incorrectcolor();
    }if (!shapecorrect) {  
    incorrectshape();
    }if (digitalRead(SQUARE_SWITCH_PIN)){
    incorrecthole();
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
  lastInputTime = millis(); //Reset the last input time 
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
  Serial.println("Correct");
  digitalWrite(CORRECT_LED_PIN, HIGH); 
  delay(1000);
  digitalWrite(CORRECT_LED_PIN, LOW); 
  randomizeGame(); 
}
// Incorrect indicators's
void incorrectcolor() {
    Serial.println("Incorrect color");
    digitalWrite(INCORRECT_COLOR_LED_PIN, HIGH); 
    delay(1000);
    digitalWrite(INCORRECT_COLOR_LED_PIN, LOW); 
    lastInputTime = millis(); 
}
void incorrectshape() {
    Serial.println("Incorrect shape");
    digitalWrite(INCORRECT_SHAPE_LED_PIN, HIGH); 
    delay(1000);
    digitalWrite(INCORRECT_SHAPE_LED_PIN, LOW); 
    lastInputTime = millis(); 
}

void incorrecthole() {
    Serial.println("Incorrect shape");
    digitalWrite(INCORRECT_HOLE_LED_PIN, HIGH); 
    delay(1000);
    digitalWrite(INCORRECT_HOLE_LED_PIN, LOW); 
    lastInputTime = millis(); 
}
// Flash LED's
void flashled() {
  delay(1000);
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
  delay(1000);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(ORANGE_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(PURPLE_LED_PIN, HIGH);
  digitalWrite(CIRCLE_LED_PIN, HIGH);
  digitalWrite(RECTANGLE_LED_PIN, HIGH);
  digitalWrite(SQUARE_LED_PIN, HIGH);
  digitalWrite(DIAMOND_LED_PIN, HIGH);
  digitalWrite(STAR_LED_PIN, HIGH);
  digitalWrite(TRIANGLE_LED_PIN, HIGH);
}
