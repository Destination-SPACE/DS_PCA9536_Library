#include <Wire.h>
#include <DS_PCA9536.h>

PCA9536 PCA;
PCA9536Data_t pcadata;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.print("PCA9536 test");
  if(!PCA.begin()){
    Serial.print("\nPCA9536 could not be found...");
    while(true){
      delay(10);
    }
  }
  PCA.reset();
  Serial.print("\n");
}

void loop() {
  Serial.print("\n");
  char buffer[128];
  
  PCA.read(pcadata);
  sprintf(buffer, "\n\nLeft:\t%d\nMiddle:\t%d\nRight:\t%d", pcadata.bit0, pcadata.bit1, pcadata.bit3);
  Serial.print(buffer);

  delay(1000);
}
