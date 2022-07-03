#include <SoftwareSerial.h>
#define IN1a 8
#define IN2a 9
#define IN3a 2
#define IN4a 3
#define IN1b 4
#define IN2b 5
#define IN3b 6
#define IN4b 7
#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0
SoftwareSerial mySerial(10, 11); // RX, TX
 
void setup() {
  Serial.begin(9600);
 
  Serial.println("Da san sang");
  pinMode(IN1a, OUTPUT);
  pinMode(IN2a, OUTPUT);
  pinMode(IN3a, OUTPUT);
  pinMode(IN4a, OUTPUT);
  pinMode(IN1b, OUTPUT);
  pinMode(IN2b, OUTPUT);
  pinMode(IN3b, OUTPUT);
  pinMode(IN4b, OUTPUT);
  mySerial.begin(9600);
}
 void motor_1a_Dung() {
  digitalWrite(IN1a, LOW);
  digitalWrite(IN2a, LOW);
}
 
void motor_2a_Dung() {
  digitalWrite(IN3a, LOW);
  digitalWrite(IN4a, LOW);
}
void motor_1a_Tien(int speed) { //speed: từ 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN1a, HIGH);// chân này không có PWM
  analogWrite(IN2a, 255 - speed);
}
 
void motor_1a_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN1a, LOW);// chân này không có PWM
  analogWrite(IN2a, speed);
}
 
 
void motor_2a_Lui(int speed) { //speed: từ 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN3a, LOW);// chân này không có PWM
  analogWrite(IN4a, speed);
}
 
void motor_2a_Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN3a, HIGH);// chân này không có PWM
  analogWrite(IN4a, 255 - speed);
}
void motor_1b_Dung() {
  digitalWrite(IN1b, LOW);
  digitalWrite(IN2b, LOW);
}
 
void motor_2b_Dung() {
  digitalWrite(IN3b, LOW);
  digitalWrite(IN4b, LOW);
}
 
void motor_1b_Lui(int speed) { //speed: từ 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN1b, HIGH);// chân này không có PWM
  analogWrite(IN2b, 255 - speed);
}
 
void motor_1b_Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN1b, LOW);// chân này không có PWM
  analogWrite(IN2b, speed);
}
 
void motor_2b_Lui(int speed) { //speed: từ 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  analogWrite(IN3b, speed);
  digitalWrite(IN4b, LOW);// chân này không có PWM
}
 
void motor_2b_Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  analogWrite(IN3b, 255 - speed);
  digitalWrite(IN4b, HIGH);// chân này không có PWM
}
void loop() {
  if (mySerial.available() > 0) {
        delay(20);
    String a="";
    while (mySerial.available() > 0) {
      char ch = mySerial.read(); //đọc
        if (a.length()<=9)
       { a+=ch; }
        
        long b = a.toInt();
       if (100000000<=b && 510231023>=b)
      {
      int j = b/100000000;
          b = b - j*100000000;
          int joy_X = b/10000;
          int joy_Y =b - joy_X*10000;
          int sp=0;
          if (j==2) {
            Serial.println("2");
      motor_1b_Lui(255);
      motor_2b_Tien(255);
      motor_1a_Dung();
      motor_2a_Dung();
            }
          else if (j==3) {
            Serial.println("3");
      motor_1a_Tien(255);
      motor_2a_Lui(255);
      motor_1b_Lui(255);
      motor_2b_Tien(255);
            }
          else if (j==4) {
            Serial.println("4");
      motor_1b_Tien(255);
      motor_2b_Lui(255);
      motor_1a_Dung();
      motor_2a_Dung();
            }
          else if (j==5) {
            Serial.println("5");
      motor_1a_Lui(255);
      motor_2a_Tien(255);
      motor_1b_Tien(255);
      motor_2b_Lui(255);
            }
           else { 
//---------------------------------------
    if ((joy_X < 350) && (joy_Y < 350) ) //Joy moved up

    {
      sp = (512 - joy_Y) / (512/255) ;
      Serial.println("Tren Phai");
      Serial.println(sp);
      Serial.println(joy_Y);
      motor_1b_Dung();
      motor_1a_Dung();
      motor_2b_Tien(sp);
      motor_2a_Tien(sp);
      } 

    if((joy_X > 650) && (joy_Y < 350) )//Joy moved down

    { sp = (512 - joy_Y) / (512/255) ;
      Serial.println("Duoi Phai");
      Serial.println(sp);
      Serial.println(joy_Y);
      motor_2a_Dung();
      motor_2b_Dung();
      motor_1a_Lui(sp);
      motor_1b_Lui(sp);
      } //Glow Lower LED
    if ((joy_X <= 650 && joy_X >= 350 ) && (joy_Y < 350) )
     { 
      sp = (512 - joy_Y) / (512/255) ;
      Serial.println(sp);
      Serial.println(joy_Y);
      Serial.println("Phai");
      motor_1a_Lui(sp);
      motor_2a_Tien(sp);
      motor_1b_Lui(sp);
      motor_2b_Tien(sp);
    }

    if ((joy_X < 350) && (joy_Y > 650) ) //Joy moved up

    { 
      sp = (joy_Y - 512) / (512/255) ;
      Serial.println("Tren Trai");
      Serial.println(sp);
      Serial.println(joy_Y);
      motor_2a_Dung();
      motor_2b_Dung();
      motor_1a_Tien(sp);
      motor_1b_Tien(sp);
      } //Glow upper LED

     if((joy_X > 650) && (joy_Y >650) )//Joy moved down

      { 
       sp = (joy_Y - 512) / (512/255) ;
      Serial.println("Duoi Trai");
      Serial.println(sp);
      Serial.println(joy_Y);
      motor_1b_Dung();
      motor_1a_Dung();
      motor_2a_Lui(sp);
      motor_2b_Lui(sp);
        } 
    if ((joy_X <= 650 && joy_X >= 350 ) && (joy_Y >650) )
      {
      sp = (joy_Y - 512) / (512/255) ;
      Serial.println(sp);
      Serial.println(joy_Y);
      Serial.println("Trai");
      motor_1a_Tien(sp);
      motor_2a_Lui(sp);
      motor_1b_Tien(sp);
      motor_2b_Lui(sp);
      
        } 
      if ((joy_X < 350) && (joy_Y <= 650) && (joy_Y >= 350) )

    {
      sp = (512 - joy_X) / (512/255) ;
      Serial.println("Tien");
      Serial.println(sp);
      Serial.println(joy_X);
      motor_1a_Tien(sp);
      motor_1b_Tien(sp);
      motor_2b_Tien(sp);
      motor_2a_Tien(sp);
      } 

      if((joy_X > 650) && (joy_Y <= 650) && (joy_Y >= 350) )//Joy moved down

     {
      Serial.println("Lui"); 
      sp = (joy_X - 512) / (512/255) ;
      Serial.println(sp);
      Serial.println(joy_X);
      motor_1a_Lui(sp);
      motor_1b_Lui(sp);
      motor_2b_Lui(sp);
      motor_2a_Lui(sp);
      
      }   
    if ( (joy_X <= 650) && (joy_X >= 350)  && (joy_Y <= 650) && (joy_Y >= 350)  )  {
      motor_2b_Dung();
      motor_2a_Dung();
      motor_1a_Dung();
      motor_1b_Dung();
      // dung lai
      }  
//---------------------------------------- 
            }
      }
      delay(3);
    }
  }
}
