#include <PrecalcMath.h>

int counter=-1024;

void setup() {
  Serial.begin(9600);
  delay(3000);
}

void loop() {
  	int j;
    int sn=PrecalcMath::sin360(counter)+128;
    int cs=PrecalcMath::cos360(counter)+128;

	analogWrite(A0, PrecalcMath::linearizeLight(sn) ); // light led in A0 according to sin value

    counter+=2;
    delay(1);
}
