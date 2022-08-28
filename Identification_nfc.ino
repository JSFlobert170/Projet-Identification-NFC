#include <Wire.h>
#include <Adafruit_PN532.h>

// If using the breakout or shield with I2C, define just the pins connected
// to the IRQ and reset lines.  Use the values below (2, 3) for the shield!
#define PN532_IRQ   (2)
#define PN532_RESET (3)  // Not connected by default on the NFC Shield

// Or use this line for a breakout or shield with an I2C connection:
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

void setup(void) {
  Serial.begin(115200);

  nfc.begin();



  // configure board to read RFID tags
  nfc.SAMConfig();

  Serial.println("I am waiting for card...");
}


void loop(void) {
  }


void fonctionTag(){

  uint8_t success;                          // Flag to check if there was an error with the PN532
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Display some basic information about the card
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println();

    if (uidLength == 4)
    {
      // Code ajoute
      uint8_t ref[] = {0x09, 0xC0, 0x67, 0x9F, 0x00, 0x00, 0x00};
      bool ok = true;
      uint8_t i = 0;


      for (i = 0; i < uidLength; i++) {
        if (ref[i] != uid[i])
          ok = false;
      }

      if (ok)
        Serial.println("===============   OK    =================");
        
      else
        Serial.println("==============  NOT OK  ================");
        

    }

    Serial.println();
    Serial.println();
    delay(900);
  }
  Serial.flush();
  
  }

