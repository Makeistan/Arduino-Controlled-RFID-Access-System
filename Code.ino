//LCD_I2C
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//RFID setup
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
String ID = "";
String AllowedID = " 41 7C 0A 85";

void setupLCD(){
  lcd.init();       // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Starting...");
  lcd.setCursor(0,1);
  lcd.print("Code By Houneie");
  delay(1000);
  lcd.clear();
}

void checkID(String ID){
  lcd.clear();
  if(ID == AllowedID){
  lcd.setCursor(0,0);
  lcd.print("Welcome");
  lcd.setCursor(0,1);
  lcd.print("Abdul Rehman");
  }
  else{
  lcd.setCursor(0,0);
  lcd.print("You Are Not in");
  lcd.setCursor(0,1);
  lcd.print("Allowed List");
  }
}

void setup(){
  Serial.begin(9600);
  setupLCD();
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  lcd.setCursor(0,0);
  lcd.print("Scan Card");
}

void loop()
{
  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.println(F("ID tag is:"));
  byte letter;
  ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) 
  {
     //Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(rfid.uid.uidByte[i], HEX);
     ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
     ID.concat(String(rfid.uid.uidByte[i], HEX));
  }
  ID.toUpperCase();
  Serial.println(ID);
  Serial.println();

  lcd.setCursor(0,0);
  lcd.print("Card Scanned");
  lcd.setCursor(0,1);
  lcd.print("ID: " + ID);

  checkID(ID);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scan Card");
  
}
