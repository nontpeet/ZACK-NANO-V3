#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


void setup()
{   
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.setRotation(2);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,25);
  display.print("INDY ROBOT");
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop()
{
read_test();

//int diatance = get_IR(analogRead(0));  //อ่านค่าระยะ เก็บในตัวแปร diatance
}


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
double get_IR (uint16_t value) {
        if (value < 16)  value = 16;
        return 2076.0 / (value - 11.0);
}

void read_test()
{      
  display.setTextSize(1);       //  กำหนดขนาดตัวอักษร
  display.setTextColor(WHITE);  //  กำหนดสีตัวอักษร
  display.setCursor(0,0);       //  กำหนดตำแหน่งที่จะแสดงผลตัวอักษร
   
  display.print("distance"); 
  display.println(get_IR(analogRead(0)),DEC);

  display.display();                  //  สั่งให้จอ OLED แสดงผล
  delay(200);                         //  หน่วงเวลาเพื่อแสดงผล 200 ms
  display.clearDisplay();             //  ทำการเคลียร์ค่าหน้าจอ OLED
}

