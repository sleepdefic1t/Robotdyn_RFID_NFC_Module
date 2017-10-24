## Robotdyn Compact RFID/NFC Reader/Writer Module (MFRC522)

This is a nice, small, inexpensive NFC module for Arduino/ESP8266.  
Unfortunately, there isn't much documentation;  
so I'm posting this for anyone interested.  
Any input or pull requests are welcomed

Original code will show attribution to the best of my ability to track down the sources.

-----

[***Robotdyn Compact RFID Reader/Writer and NFC module***](http://robotdyn.com/catalog/communication/rfid_reader_writer_nfc_module_mfrc522/)  
<img src="http://robotdyn.com/upload/resizer2/15/8e0/8e0fcdd34db8a250ead575f6764330a6.jpg" width="400">  
<img src="http://robotdyn.com/upload/resizer2/16/ba8/ba8447a4a059a2755010ca0c224bfe94.jpg" width="400">  

-----

### Install to Arduino IDE

The Arduino library location can be different for each system.  
Using macOS, it's typically installed in ```~/Documents/Arduino/libraries```


#### easy git method
1. clone this repo to Arduino Library folder:  
  -```cd ~/Documents/Arduino/libraries && git clone https://github.com/sleepdefic1t/Robotdyn_RFID_NFC_Module/```


#### .zip method
1. Download .zip of this repo.
- On the Gihub repo-page;  
look for the green "Clone or download ▼" button,  
and click "Download ZIP"

2. Add to Arduino IDE  
From the Arduino IDE Menu Bar  
- > 'Sketch' > 'Include Library  ▶︎' > 'Add .Zip Library...'  
- Select the .zip file of this repo.
 
-----

### Add to your Arduino Project
From the Arduino IDE,  
with your sketch file open  
- > Menu Bar > 'Sketch' > 'Include Library  ▶︎' > 'Robotdyn RFID/NFC'  
 
-----

# Reference

```arduino
class RFID
{
  public:
	RFID(int chipSelectPin, int NRSTPD);

	bool isCard();
	bool readCardSerial();
  
	void init();
	void reset();
  
	void setBitMask(unsigned char reg, unsigned char mask);
	void clearBitMask(unsigned char reg, unsigned char mask);
  
	void antennaOn(void);
	void antennaOff(void);
  
	void calculateCRC(unsigned char *pIndata, unsigned char len, unsigned char *pOutData);
  
	void writeMFRC522(unsigned char addr, unsigned char val);
  
	unsigned char readMFRC522(unsigned char addr);
  
	unsigned char MFRC522Request(unsigned char reqMode, unsigned char *TagType);
  
	unsigned char MFRC522ToCard(unsigned char command, unsigned char *sendData, unsigned char sendLen, unsigned char *backData, unsigned int *backLen);
  
	unsigned char anticoll(unsigned char *serNum);
  
	unsigned char auth(unsigned char authMode, unsigned char BlockAddr, unsigned char *Sectorkey, unsigned char *serNum);
  
	unsigned char read(unsigned char blockAddr, unsigned char *recvData);
  
	unsigned char write(unsigned char blockAddr, unsigned char *writeData);
  
	unsigned char selectTag(unsigned char *serNum);
  
	void halt();
	
	unsigned char serNum[5];
	
  private:
	int _chipSelectPin;
	int _NRSTPD;
};

```

-----
Demo SRC: [**Aliexpress**](https://www.aliexpress.com/store/product/Compact-RFID-Reader-Writer-and-NFC-module-MFRC522-13-56MHz-Power-5V-3-3V-For-Arduino/1950989_32667518116.html)  
RFID SRC: [***soapdx/arduino_rfid***](https://github.com/soapdx/arduino_rfid)
