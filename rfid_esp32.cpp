//Inventory management system using ESP32, Firebase and RFID 

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN    5  // ESP32 pin GPIO5 
#define RST_PIN   27 // ESP32 pin GPIO27 
#define RELAY_PIN 22 // ESP32 pin GPIO22 connects to relay
int Sdata = 0;
MFRC522 rfid(SS_PIN, RST_PIN);

byte authorizedUID[4] = {0xD3, 0xF8, 0x02, 0x1E};
#include <WiFi.h>
#include <FirebaseESP32.h>


#define FIREBASE_HOST "**********************************"
#define FIREBASE_AUTH "**********************************************"
#define WIFI_SSID "************"
#define WIFI_PASSWORD "***************"


//Define FirebaseESP32 data object
FirebaseData firebaseData;
FirebaseJson json;
int Vresistor = A0; 
int Vrdata = 0; 


void setup() {
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  pinMode(RELAY_PIN, OUTPUT); // initialize pin as an output.
  digitalWrite(RELAY_PIN, LOW); // deactivate the relay

  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
 pinMode(Vresistor, INPUT);


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

 

  //String path = "/data";
  

  Serial.println("------------------------------------");
  Serial.println("Connected...");
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

      if (rfid.uid.uidByte[0] == authorizedUID[0] &&
          rfid.uid.uidByte[1] == authorizedUID[1] &&
          rfid.uid.uidByte[2] == authorizedUID[2] &&
          rfid.uid.uidByte[3] == authorizedUID[3] ) {
        Serial.println("Authorized Tag");
        Vrdata = analogRead(Vresistor);
        Sdata = Sdata + 1;
       
        Serial.println(Sdata); 
        delay(100); 
        json.set("/data", Sdata);
        Firebase.updateNode(firebaseData,"/Sensor",json);
        digitalWrite(RELAY_PIN, HIGH); // activate the relay for 2 seconds
        delay(2000);
        digitalWrite(RELAY_PIN, LOW);  // deactivate the relay
      }
      else
      {
        Serial.print("Unauthorized Tag with UID:");
        for (int i = 0; i < rfid.uid.size; i++) {
          Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(rfid.uid.uidByte[i], HEX);
        }
        Serial.println();
      }

      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
 
    }
  }

}
