#include <Servo.h>

#define SERVO_HAND_RIGHT_PIN 5
#define SERVO_HAND_LEFT_PIN 6
#define SERVO_ARM_RIGHT_PIN 10
#define SERVO_ARM_LEFT_PIN 9
#define SERVO_HEAD_PIN 11

#define SET_SERVO_HOME 0
#define SET_SERVO_ARM_LEFT_HOME 180
#define SET_SERVO_HEAD_HOME 100

Servo ServoHandRight;
Servo ServoHandLeft;
Servo ServoArmRight;
Servo ServoArmLeft;
Servo ServoHead;
/*-----------------------------------------------*/
void ServoSetup()
{
  ServoHandRight.attach(SERVO_HAND_RIGHT_PIN);
  ServoHandLeft.attach(SERVO_HAND_LEFT_PIN);
  ServoArmRight.attach(SERVO_ARM_RIGHT_PIN);
  ServoArmLeft.attach(SERVO_ARM_LEFT_PIN);
  ServoHead.attach(SERVO_HEAD_PIN);
}
/*-----------------------------------------------*/
void ServoHome()
{
  ServoHandRight.write(SET_SERVO_HOME);
  ServoHandLeft.write(SET_SERVO_HOME);
  ServoArmRight.write(SET_SERVO_HOME);
  ServoArmLeft.write(SET_SERVO_ARM_LEFT_HOME);
  ServoHead.write(SET_SERVO_HEAD_HOME);
}
/*-----------------------------------------------*/
void ServoStop()
{
  ServoHead.detach();
  ServoArmLeft.detach();
  ServoArmRight.detach();
  ServoHandLeft.detach();
  ServoHandRight.detach();
}
/*-----------------------------------------------*/
void MoveHead(uint32_t Angle)
{
  //Angle range 80 to 130 
  if((Angle >= 80) && (Angle <= 130))
  {
    ServoHead.write(Angle);
  }
  else
  {
    Serial.println("ServoHeadOverRange");
  }
}
/*-----------------------------------------------*/
void MoveArmLeft(uint32_t Angle)
{
  if((Angle >= 135) && (Angle <= 180))
  {
  ServoArmLeft.write(Angle);
  }
  else
  {
    Serial.println("ServoArmLeftOverRange");
  }
}
/*-----------------------------------------------*/
void MoveArmRight(uint32_t Angle)
{ 
  if((Angle >= 0) && (Angle <= 45))
  {
  ServoArmRight.write(Angle);
  }
  else
  {
    Serial.println("ServoArmRightOverRange");
  }
}
/*-----------------------------------------------*/
void BeginHead() 
{ //หันหน้าตรง   face origin
  ServoHead.write(100);
}
/*-----------------------------------------------*/
void HeadShake(uint8_t x, uint8_t y, uint32_t Speed) 
{ //ส่ายหัว    turn left and turn right head input x is in the range 0-100 and input y is in the range 100-180
  ServoHead.attach(SERVO_HEAD_PIN);
  for (int pos = 100; pos <= x; pos++) {  // หมุนจาก 100 ถึง 130 องศา
    ServoHead.write(pos);  // สั่งให้ Servo หมุนไปยังตำแหน่งที่กำหนด
    delay(Speed);  // หน่วงเวลาเพื่อให้มีการหมุนช้าๆ
  }
  for (int pos = x; pos >= y; pos--) 
  {  // หมุนจาก 100 ถึง 80 องศา
    ServoHead.write(pos);  // สั่งให้ Servo หมุนไปยังตำแหน่งที่กำหนด
    delay(Speed);  // หน่วงเวลาเพื่อให้มีการหมุนช้าๆ
  }
  for (int pos = y; pos <= 100; pos++) 
  {  // หมุนจาก 80 ถึง 100 องศา
    ServoHead.write(pos);  // สั่งให้ Servo หมุนไปยังตำแหน่งที่กำหนด
    delay(Speed);  // หน่วงเวลาเพื่อให้มีการหมุนช้าๆ
  }
  ServoHead.detach();
}
/*-----------------------------------------------*/
void HeadTurnLeft(int x) 
{     //ส่ายหัว ไปทางซ้าย  x คือค่าองศา ตั้งแต่ 0-100  turn left input x is in the range 0-100
  if ( 0 <= x <= 100) {
    ServoHead.write(x);
  }
}
/*-----------------------------------------------*/
void HeadTurnRight(int x) 
{  //ส่ายหัว ไปทางขวา  x คือค่าองศา ตั้งแต่ 100-180  turn Right input x is in the range 100-180
  if ( 100 <= x <= 180) 
  {
    ServoHead.write(x);
  }
}
/*-----------------------------------------------*/
void LiftRightHand(uint32_t Angle, uint32_t Delay) 
{  //ยกมือ ขวา ขึ้น 
  if((Angle > 45) && (Angle < 0))
  {
    Angle = 45; //Default Angle
    Serial.println("LiftRightHandOverrange");
  }
    for(int x = 0; x < Angle; x++)
  {
    ServoArmRight.write(x);
    delay(Delay);
  }
}
/*-----------------------------------------------*/
void LiftLeftHand(uint32_t Angle, uint32_t Delay) 
{ //ยกมือ ซ้าย ขึ้น
  if((Angle > 180) && (Angle < 135))
  {
    Angle = 135; //Default Angle
    Serial.println("LiftLeftHandOverrange");
  }
    for(int x = 180; x > Angle; x--)
  {
    ServoArmLeft.write(x);
    delay(Delay);
  }
}
/*-----------------------------------------------*/
void BeginRightHand()
{ // มือ ซ้าย อยู่ในท่าปกติ origin Right hand
  ServoArmRight.write(0);
}
/*-----------------------------------------------*/
void BeginLeftHand() 
{ // มือ ขวา อยู่ในท่าปกติ origin left hand
  ServoArmLeft.write(180); //arm right
}
/*-----------------------------------------------*/
void HandRightGripe(uint32_t Angle)
{
    if(Angle == 0)
  {
    Angle = 35; //Default Angle
  }
  ServoHandRight.write(Angle);
}
/*-----------------------------------------------*/
void HandLeftGripe(uint32_t Angle)
{
    if(Angle == 0)
  {
    Angle = 35; //Default Angle
  }
  ServoHandLeft.write(Angle);
}
/*-----------------------------------------------*/
void HandRightRelease(uint32_t Angle)
{
  if(Angle == 0)
  {
    Angle = 0; //Default Angle
  }
  ServoHandRight.write(Angle);
}
/*-----------------------------------------------*/
void HandLeftRelease(uint32_t Angle)
{
  if(Angle == 0)
  {
    Angle = 0; //Default Angle
  }
  ServoHandLeft.write(Angle);
}
/*-----------------------------------------------*/
void PutRightHand(uint32_t Angle, uint32_t Delay)
{
  for(int x = Angle; x > 0; x--)
  {
    ServoArmRight.write(x);
    delay(Delay);
  }
}
/*-----------------------------------------------*/
void PutLeftHand(uint32_t Angle, uint32_t Delay)
{
  for(int x = Angle; x < 180; x++)
  {
    ServoArmLeft.write(x);
    delay(Delay);
  }
}
/*-----------------------------------------------*/
