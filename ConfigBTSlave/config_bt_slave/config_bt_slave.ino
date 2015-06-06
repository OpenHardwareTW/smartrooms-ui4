#include<SoftwareSerial.h>
#define RxD 9
#define TxD 8

SoftwareSerial BluetoothEsclavoSerial(RxD, TxD);

void setup() {
  BluetoothEsclavoSerial.begin(38400);
  delay(500);
  BluetoothEsclavoSerial.flush();
  delay(500);
  
  
  Serial.begin(9600);
  Serial.println("Modo AT");

}

void loop() {
  if(BluetoothEsclavoSerial.available()){
    Serial.write(BluetoothEsclavoSerial.read());
  }
  if(Serial.available()){
    BluetoothEsclavoSerial.write(Serial.read());
  }
}
