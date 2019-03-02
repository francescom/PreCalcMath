#include <PrecalcMath.h>

int counter=-1024;

void setup() {
  Serial.begin(9600);
  delay(3000);
}

void loop() {
  	int j;
    int sn=PrecalcMath::sin255(counter)+128;
    int cs=PrecalcMath::cos255(counter)+128;

  	serialFeddBack(sn,cs);
  
    counter+=8;
    delay(1);
}











void serialFeddBack(uint8_t sn,uint8_t cs) {
  	int j;
    sn=sn>>3;
    cs=cs>>3;
  
    for(j=1;j<myMin(sn,cs);j++) {
      Serial.print(" ");
    }
  	if(sn!=cs) {
      Serial.print("*");
      for(;j<myMax(sn,cs);j++) {
        Serial.print(" ");
      }
    }
    Serial.println("*");
}

inline const int8_t myMin(const int8_t a, const int8_t b) {
  return (a<b)?a:b;
}

inline const int8_t myMax(const int8_t a, const int8_t b) {
  return (b<a)?a:b;
}

