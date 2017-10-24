# src: https://www.aliexpress.com/store/product/Compact-RFID-Reader-Writer-and-NFC-module-MFRC522-13-56MHz-Power-5V-3-3V-For-Arduino/1950989_32667518116.html
#include <RFID.h>
#include <SPI.h>

//RFID rfid(10, 5);    // D10--SDA, D5--RST
RFID rfid(4, 16);    // Adafruit Feather Huzzah 8266 [SDA--SDA, RST--RST(Board1--#16)]

unsigned char serNum[5];
 
unsigned char writeDate[16] ={'R', 'o', 'b', 'o', 't', 'D', 'y', 'n', '-', 'T', 'e', 's', 't', 0, 0, 0};
 
unsigned char sectorKeyA[16][16] = {
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},};
 
unsigned char sectorNewKeyA[16][16] = {
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff,0x07,0x80,0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff,0x07,0x80,0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},};
 
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}
 
void loop()
{
  unsigned char i,tmp;
  unsigned char status;
  unsigned char str[MAX_LEN];
  unsigned char RC_size;
  unsigned char blockAddr;
 
  rfid.isCard();
 
  if (rfid.readCardSerial())
  {
    Serial.print("The card's number is  : ");
    Serial.print(rfid.serNum[0],HEX);
    Serial.print(rfid.serNum[1],HEX);
    Serial.print(rfid.serNum[2],HEX);
    Serial.print(rfid.serNum[3],HEX);
    Serial.print(rfid.serNum[4],HEX);
    Serial.println(" ");
  }
 
  rfid.selectTag(rfid.serNum);
  
  blockAddr = 7;
  if (rfid.auth(PICC_AUTHENT1A, blockAddr, sectorKeyA[blockAddr/4], rfid.serNum) == MI_OK) 
  {
    status = rfid.write(blockAddr, sectorNewKeyA[blockAddr/4]);
    Serial.print("set the new card password, and can modify the data of the Sector: ");
    Serial.println(blockAddr/4,DEC);
    blockAddr = blockAddr - 3 ;
    status = rfid.write(blockAddr, writeDate);
    if(status == MI_OK)
    {
      Serial.println("Write card OK!");
    }
  }
 
  blockAddr = 7; 
  status = rfid.auth(PICC_AUTHENT1A, blockAddr, sectorNewKeyA[blockAddr/4], rfid.serNum);
  if (status == MI_OK)
  {
    blockAddr = blockAddr - 3 ;
    if( rfid.read(blockAddr, str) == MI_OK)
    {
      Serial.print("Read from the card ,the data is : ");
      Serial.println((char *)str);
    }
  }
  
  rfid.halt();
  delay(500);
}
 
