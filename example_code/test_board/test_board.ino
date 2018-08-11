#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define PWML  5  //   motor L
#define IN1L  4  //  
#define IN2L  9  //

#define PWMR  6  //   motor R
#define IN1R  8  //  
#define IN2R  7  //

const int buttonPin = 2;

int adcValue_1 = 0;
int adcValue_2 = 0;
int adcValue_3 = 0;
int adcValue_4 = 0;
int adcValue_5 = 0;
int adcValue_6 = 0;
int adcValue_7 = 0;


int sp = 150;   //    ความเร็วมอเตอร์  0-255 



void setup()
{
  Serial.begin(9600);
  pinMode(PWML,OUTPUT);
  pinMode(IN1L,OUTPUT);
  pinMode(IN2L,OUTPUT);
  
  pinMode(PWMR,OUTPUT); 
  pinMode(IN1R,OUTPUT);
  pinMode(IN2R,OUTPUT);
  
  pinMode(buttonPin, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  delay(2000);
  display.clearDisplay();

  
}

void loop()
{
  Motor(100,100);     //เดินหน้าทั้งสองล้อ
  delay(1000);
  Motor(-100,-100);   //ถอยหลังทั้งสองล้อ
  delay(1000);
  Motor(-100,100);    //ล้อซ้ายถอย ล้อขวาเดินหน้า
  delay(1000);
  Motor(100,-100);    //ล้อซ้ายเดินหน้า ล้อขวาถอย
  delay(1000);
  Motor(0,0);         //หยุดทั้ง สองล้อ


  while(digitalRead(buttonPin)==HIGH)
    {
    read_test();
    }
 
}



  
 
///////////////////////////////////////////////////////////////////////
//  ฟังก์ชั่นสั่งงานมอเตอร์  Motor(ความเร็วซ้าย,ความเร็วขวา);
//
//  Motor(100,100);     //  เดินหน้าทั้งสองล้อ
//  Motor(-100,-100);   //  ถอยหลังทั้งสองล้อ
//  Motor(-100,100);    //  ล้อซ้ายถอย ล้อขวาเดินหน้า
//  Motor(100,-100);    //  ล้อซ้ายเดินหน้า ล้อขวาถอย
//  Motor(0,0);         //  หยุดทั้ง สองล้อ
//
//  สามารถกำหนดความเร็วได้  -255 ถึง 255
//
///////////////////////////////////////////////////////////////////////
void Motor(int sl,int sr){          
  if(sr>255)
    sr = 255;
  else if(sr<-255)
    sr = -255;
    
  if(sl>255)
    sl = 255;
  else if(sl<-255)
    sl = -255;
    
  if(sl>0){
      digitalWrite(IN1L,HIGH);
      digitalWrite(IN2L,LOW);
      analogWrite(PWML,sl);
  }else if(sl<0){    
      digitalWrite(IN1L,LOW);
      digitalWrite(IN2L,HIGH);
      analogWrite(PWML,-sl);
  }else{        
      digitalWrite(IN1L,HIGH);
      digitalWrite(IN2L,HIGH);
      analogWrite(PWML,255);
  }  
  
  if(sr>0){
      digitalWrite(IN1R,HIGH);
      digitalWrite(IN2R,LOW);
      analogWrite(PWMR,sr);
  }else if(sr<0){    
      digitalWrite(IN1R,LOW);
      digitalWrite(IN2R,HIGH);
      analogWrite(PWMR,-sr);
  }else{        
      digitalWrite(IN1R,HIGH);
      digitalWrite(IN2R,HIGH);
      analogWrite(PWMR,255);
  }    
}

///////////////////////////////////////////////////////////////////////
//  
//  ฟังก์ชั่นอ่านค่า Analog
//
///////////////////////////////////////////////////////////////////////
void readADC(){ 
  adcValue_1 = analogRead(0); 
  adcValue_2 = analogRead(1);
  adcValue_3 = analogRead(2);
  adcValue_4 = analogRead(4);
  adcValue_5 = analogRead(5);
  adcValue_6 = analogRead(6); 
  adcValue_7 = analogRead(7);
}

///////////////////////////////////////////////////////////////////////
//  
//  ฟังก์ชั่นอ่านค่า Analog แล้วแสดงผลออกจางจอ OLED
//
///////////////////////////////////////////////////////////////////////
void read_test()
{      
  display.setTextSize(1);       //  กำหนดขนาดตัวอักษร
  display.setTextColor(WHITE);  //  กำหนดสีตัวอักษร
  display.setCursor(0,0);       //  กำหนดตำแหน่งที่จะแสดงผลตัวอักษร
  
  display.print(" A0 : ");              //  แสดงข้อความออกจากจอ OLED
  display.println(analogRead(0),DEC);   //  อ่านค่า Analog ช่อง 0  และแสดงผลออกทางจอ OLED เป็นตัวเลขฐาน 10
  display.print(" A1 : ");
  display.println(analogRead(1),DEC);
  display.print(" A2 : ");
  display.println(analogRead(2),DEC);
  display.print(" A3 : ");
  display.println(analogRead(3),DEC);
  display.print(" A4 : ");
  display.println(analogRead(4),DEC);
  display.print(" A5 : ");
  display.println(analogRead(5),DEC);
  display.print(" A6 : ");
  display.println(analogRead(6),DEC);
  display.print(" A7 : ");
  display.println(analogRead(7),DEC);
  
  display.display();                  //  สั่งให้จอ OLED แสดงผล
  delay(200);                         //  หน่วงเวลาเพื่อแสดงผล 200 ms
  display.clearDisplay();             //  ทำการเคลียร์ค่าหน้าจอ OLED
}


