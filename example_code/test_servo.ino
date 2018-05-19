#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Servo myservo;  

int potpin = 7;     // กำหนดขา Analog ที่จะใช้ทดสอบ ในที่นี้ใช้ ขา 7 ซึ่งต่ออยู่กับ VR หรือ POT
int servo_pin = 10; // กำหนดขา SERVO  ที่จะทดสอบ  โดยบอร์ด ZACK NANO V3  จะมี ขา D10,D11,D12
int val;        

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  display.clearDisplay();
  myservo.attach(servo_pin);       
}

void loop() {
  val = analogRead(potpin);            // อ่านค่า Analog จาก VR หรือ POT โดยค่าที่อ่านได้จะเป็นค่า 0 ถึง 1023
  val = map(val, 0, 1023, 0, 180);     // ทำการแปลงค่า 0-1023 ให้เป็นค่า  0-180  หมายเหตุ SERVO จะต้องสั่งงาน  0-180 เท่านั้น
  myservo.write(val);                  // สั่งงาน SERVO 
  delay(15);                           // หน่วงเวลา 15 ms

  display.setTextSize(2);              // กำหนดขนาดตัวอักษร
  display.setTextColor(WHITE);         // กำหนดสีตัวอักษร
  display.setCursor(1,0);              // กำหนดตำแหน่งตัวอักษร
  display.print("servo ");             // แสดงข้อความ ออกทางหน้อจอ
  display.println(val,DEC);            // แสดงตัวแปร องศาของ SERVO ออกทางหน้าจอ
  display.display();                   // แสดงค่าออกทาง OLED
  delay(15);                           // หน่วงเวลา 15 ms
  display.clearDisplay();              // สั่งเคลัยร์หน้าจอ
}

