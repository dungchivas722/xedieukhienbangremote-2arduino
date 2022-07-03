#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
int bientroX1 = A0 ; 
int bientroY1 = A1 ; 
int bientroX2 = A2 ; 
int bientroY2 = A3 ;     
void setup() {
 
  mySerial.begin(9600);
     pinMode(2, INPUT);
     pinMode(A0, INPUT);
     pinMode(A1, INPUT);
     pinMode(A2, INPUT);
     pinMode(A3, INPUT);
}
 
void loop() {
long  x1 = analogRead(bientroX1);  // doc gia tri cua truc X1
long  y1 = analogRead(bientroY1);  // doc gia tri cua truc Y1
long  x2 = analogRead(bientroX2);  // doc gia tri cua truc X2
long  y2 = analogRead(bientroY2);  // doc gia tri cua truc Y2
long dem =100000000;
  if ((x2<= 800 && x2>= 200 ) && (y2 < 200) )
   { dem += 200000000;  }
  if ((x2<= 800 && x2>= 200 ) && (y2 >800) )
   { dem += 400000000;  }    
  if ((x2< 200) && (y2 <= 800) && (y2 >= 200) )
   { dem += 100000000;  } 
  if ((x2> 800) && (y2 <= 800) && (y2 >= 200) )
   { dem += 300000000;} 
      dem = dem + x1*10000 + y1;
  String myStr;
  myStr = String (dem);
  mySerial.println(myStr);
  delay(100);
    }
