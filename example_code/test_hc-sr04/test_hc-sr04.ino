/*
ทดสอบอ่านค่า Sensor hc-sr04 
www.indy-robot.com
*/
 
const int TRIG_PIN = 13;  //กำหนดขา Trig เป็นขา  12
const int ECHO_PIN = 12;  //กำหนดขา Echo เป็นขา  13
long duration, distanceCm;  //สร้างตัวแปรเพื่อใช้ในการรับค่าจาก Sensor
 
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
 
  pinMode(TRIG_PIN,OUTPUT);  //กำหนดให้ขา Trig เป็น Output
  pinMode(ECHO_PIN,INPUT);   //กำหนดให้ขา Echo เป็น Output
}
 
void loop()
{
  distanceCm = read_hcsr04();   //เรียกใช้ฟังก์ชั่นอ่านค่า และ เก็บค่าระยะในตัวแปร distanceCm
  Serial.print(distanceCm);    
  Serial.print("cm");
  Serial.println();
  delay(1000);
}


long read_hcsr04()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN,HIGH);
 
  // convert the time into a distance
  distanceCm = duration / 29.1 / 2 ;
  return distanceCm;
}
