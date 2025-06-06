#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2);
/*-----------------------------------------------*/
void LcdSetup()
{
  lcd.begin();
  lcd.display();        //เปิดหน้าจอ
  lcd.backlight();      //เปิดไฟ backlight
  lcd.clear();          //ล้างหน้าจอ
  DisplayLcd(5,"Level4",0,"");
}
/*-----------------------------------------------*/
void DisplayLcd(uint8_t Row1,String Text1,uint8_t Row2,String Text2)
{
  lcd.clear();
  lcd.setCursor(Row1,0); 
  lcd.print(Text1); 
  lcd.setCursor(Row2,1); 
  lcd.print(Text2); 
}
/*-----------------------------------------------*/
void DisplayOff() 
{
  lcd.clear();
}
/*-----------------------------------------------*/
