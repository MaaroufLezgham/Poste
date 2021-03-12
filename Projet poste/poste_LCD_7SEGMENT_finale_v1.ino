#include <LedControl.h>
int DIN = 12;
int CS =  10;
int CLK = 11;
LedControl lc=LedControl(DIN,CLK,CS,8);
#include "RTClib.h"
RTC_DS1307 rtc;
#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
LiquidCrystal_I2C lcd(0x3F, 16, 4);
//LiquidCrystal_I2C lcd(0x27,20, 4);
char text[8]={' ' ,' ', ' ', ' ', ' ' ,' ', ' ', ' '};
#define DHTTYPE DHT11  
#define DHTPIN 2 
DHT dht(DHTPIN, DHTTYPE);
byte ZERO[] = {60, 66, 70, 74, 82, 98, 66, 60};
byte UN[] = {24, 40, 72, 8, 8, 8, 8, 28};
byte DEUX[] = {124, 2, 2, 60, 60, 64, 64, 62};
byte TROIS[] = {60, 2, 2, 60, 60, 2, 2, 62};
byte QUATRE[] = {64, 66, 66, 66, 60, 2, 2, 2};
byte CINQ[] = {60, 64, 64, 64, 60, 2, 2, 124};
byte SIX[] = {60, 64, 64, 64, 60, 66, 66, 60};
byte SEPT[] = {112, 136, 8, 8, 28, 8, 8, 8};
byte HUIT[] = {60, 66, 66, 60, 60, 66, 66, 60};
byte NEUF[] = {60, 66, 66, 66, 62, 2, 2, 62};
byte M[] = {66, 161, 149, 137, 129, 129, 129, 129};
byte H[] = {129, 129, 129, 129, 255, 129, 129, 129};
byte N[] = {1, 97, 97, 145, 137, 134, 134, 128};
byte S[] = {30, 33, 32, 32, 62, 2, 66, 62};
byte O[] = {60, 66, 129, 129, 129, 129, 66, 60};
byte I[] = {124, 16, 16, 16, 16, 16, 16, 124};
byte E[] = {60, 64, 128, 128, 252, 128, 64, 60};
byte GZERO[] = {0, 96, 145, 146, 148, 146, 145, 96};
byte GUN[] = {0, 0, 17, 50, 84, 18, 17, 56};
byte GDEUX[] = {0, 0, 1, 114, 20, 114, 65, 112};
byte GTROIS[] = {0, 0, 1, 114, 20, 114, 17, 112};
byte GQUATRE[] = {0, 0, 1, 66, 84, 114, 17, 0};
byte GCINQ[] = {0, 0, 1, 114, 68, 114, 17, 112};
byte GSIX[] = {0, 0, 1, 114, 68, 114, 81, 112};
byte GSEPT[] = {0, 0, 1, 114, 20, 58, 17, 16};
byte GHUIT[] = {0, 0, 1, 114, 84, 114, 81, 112};
byte GNEUF[] = {0, 0, 1, 114, 84, 114, 17, 112};
byte R[] = {120, 132, 132, 136, 240, 136, 132, 130};
byte D[] = {240, 136, 132, 130, 130, 132, 136, 240};
byte Y[] = {68, 68, 68, 68, 40, 16, 16, 16};
byte X[] = {129, 66, 36, 24, 24, 36, 66, 129};
byte y[8];
byte m[8];
int y0;
byte EX[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
String data= "DESIGNED  AS A PRESENT BY  <ENISO> AND <ESPITA> TO THE POST OFFICE OF  ZAOUIET SOUSSE";
String data0= "PRESS START TO BEGIN  <ENISO/ESPITA>" ;
//--------------------------------------
byte matrice[31][8]={
{ 0x3C,0x42,0x42,0x7E,0x42,0x42,0x42,0x00},// ---A
 {0x7C,0x42,0x42,0x7C,0x42,0x42,0x7C,0x00},//B
 {0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x00},//C
 {0x38,0x44,0x42,0x42,0x42,0x44,0x38,0x00},//D
 {0x3C,0x40,0x40,0x7C,0x40,0x40,0x3C,0x00}, //E
 {0x1C,0x20,0x20,0x3C,0x20,0x20,0x20,0x00},//F
 {0x3C,0x42,0x40,0x40,0x4E,0x44,0x38,0x00},// G
 {0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x00},// H
 {0x38,0x10,0x10,0x10,0x10,0x10,0x38,0x00},// I
 {0x0E,0x04,0x04,0x04,0x44,0x44,0x38,0x00},// J
 {0x20,0x24,0x28,0x30,0x30,0x28,0x24,0x00},// K
 {0x20,0x20,0x20,0x20,0x20,0x20,0x3E,0x00},// L
 {0x42,0x66,0x5A,0x42,0x42,0x42,0x42,0x00},// M
 {0x00,0x42,0x62,0x52,0x4A,0x44,0x40,0x00},// N
 {0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00},// O
 {0x3C,0x42,0x42,0x7C,0x40,0x40,0x40,0x00},// P
 {0x1C,0x22,0x22,0x22,0x22,0x1C,0x78,0x00},// Q
 {0x1C,0x22,0x22,0x3C,0x24,0x22,0x22,0x00},// R
 {0x1C,0x20,0x20,0x3C,0x04,0x04,0x38,0x00},// S
 {0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x00},// T
 {0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00},// U
 {0x44,0x44,0x44,0x44,0x44,0x28,0x10,0x00},// V
 {0x54,0x54,0x54,0x54,0x54,0x54,0x38,0x00},// W
 {0x00,0x42,0x24,0x18,0x18,0x24,0x42,0x00},// X
 {0x82,0x44,0x28,0x10,0x10,0x10,0x38,0x00},// Y
 {0x7E,0x04,0x08,0x10,0x20,0x40,0x7E,0x00},// Z
 {0,0,0,0,0,0,0,0},//" "
 {0x1C,0x1C,0x08,0x10,0x20,0x00,0x00,0x00},//"'"
 {0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x00},//"/"
{0x00,0x20,0x10,0x08,0x08,0x10,0x20,0x0},//">"
{0x00,0x10,0x20,0x40,0x40,0x20,0x10,0x00},//</"
  };
//---
uint16_t number,number1,number2,number3,number4,NMAX;
byte u0,u1,u2,u3;
int sp;
int nub;
int gh;
int buzzer=9;
int button1=8;
int button2=7;
int button3=6;
int button4=5;
int button5=4;
int last_number;
int hum;
int  temp;
String  sday,smonth;
int hours, minutes,seconds,days,months,years,daysOfTheWeek;
int hx;
int k;

void setup() {
 
  Serial.begin(9600);
  lcd.begin();
 dht.begin();
 rtc.begin();

 pinMode(button1,INPUT_PULLUP);
pinMode(button2,INPUT_PULLUP);
pinMode(button3,INPUT_PULLUP);
pinMode(button4,INPUT_PULLUP);
pinMode(button5,INPUT_PULLUP);
 Serial.println(digitalRead(button1));
  Serial.println(digitalRead(button2));
   Serial.println(digitalRead(button3));
    Serial.println(digitalRead(button4));
  pinMode(buzzer,OUTPUT);
 
        digitalWrite(buzzer,LOW);
       
     
        for(int adresse=0;adresse<8;adresse++)
  {            lc.shutdown(adresse,false);
               lc.setIntensity(adresse,8);
                lc.clearDisplay(adresse);
                
    }  
EEPROM.get(100,number);
EEPROM.get(200,NMAX);
EEPROM.get(300,gh);
sp=0;
k=0;
lcd.clear();
lcd.setCursor(0,0); 
lcd.print("******************");
lcd.setCursor(0,1);
lcd.print("Designed offered by");
lcd.setCursor(0,2);
lcd.print("ENISo  &&  ESPITA");
lcd.setCursor(0,3);
lcd.print("******************");
delay(2000);
}
//--------------


void dht11()
{
   hum = dht.readHumidity();
   temp = dht.readTemperature();
   hx= dht.computeHeatIndex(hum, temp, false);
}
   //-----------------
   void lcd_affichage()
   {
lcd.setCursor(0,0); 
lcd.print(sday);
lcd.print("/");
lcd.print(days);
lcd.print("/");
lcd.print(smonth);
lcd.print("/");
lcd.print(years);
//------------------------------------------
lcd.setCursor(0,1);
lcd.print(hours);
lcd.print(":");
lcd.print(minutes);
lcd.print(":");
lcd.print(seconds);
lcd.print("  ESPITA");
//-----------------------
lcd.setCursor(0,2); 
lcd.print("H=");
lcd.print(int(hum));
lcd.print("%");
lcd.print(" T=");
lcd.print(int(temp));
lcd.print("C");
lcd.print("  HX=");
lcd.print(int(hx));
lcd.print("C");

//------------------------
lcd.setCursor(0,3); 
lcd.print(number1);
lcd.print("/");
lcd.print(number2);
lcd.print("/");
lcd.print(number3);
lcd.print("/");
lcd.print(number4);
lcd.print(" ENISo_DEP_EI");
//-----------

   }
//------------
void rtc_time ()
{

  
DateTime now = rtc.now();
hours=now.hour();
minutes=now.minute();
seconds=now.second();
days=now.day();
months=now.month();
years=now.year();
daysOfTheWeek=now.dayOfTheWeek();
  }
//-------------------
void conv_to_bcd(uint16_t val)
{
  u0=val%10;
  val=val/10;
  u1=val%10;
  val=val/10;
 u2=val%10;
  val=val/10;
 u3=val%10;
 
}
//--------
void transG(byte(n))
{
   switch(n)
  {
  case 0:
  for(int i=0;i<8;i++)
  y[i]=GZERO[i];
  break;
  case 1:
  for(int i=0;i<8;i++)
  y[i]=GUN[i];
  break;
  case 2:
  for(int i=0;i<8;i++)
    y[i]=GDEUX[i];
  break;
  case 3:
  for(int i=0;i<8;i++)
   y[i]=GTROIS[i];
  break;
  case 4:
  for(int i=0;i<8;i++)
   y[i]=GQUATRE[i];
  break;
  case 5:
  for(int i=0;i<8;i++)
   y[i]=GCINQ[i];
  break;
  case 6:
  for(int i=0;i<8;i++)
    y[i]=GSIX[i];
  break;
  case 7:
  for(int i=0;i<8;i++)
   y[i]=GSEPT[i];
   break;
   case 8:
   for(int i=0;i<8;i++)
    y[i]=GHUIT[i];
  break;
  case 9:
  for(int i=0;i<8;i++)
   y[i]=GNEUF[i];
    break;
  }
}
//----------------
void find_days_months ()
{
  switch (daysOfTheWeek)
  {
    case 0:
    sday="Dimanche";
    break;
     case 1:
    sday="Lundi";
    break;
     case 2:
    sday="Mardi";
    break;
     case 3:
    sday="Mercredi";
    break;
     case 4:
    sday="Jeudi";
    break;
     case 5:
    sday="Vendredi";
    break;
     case 6:
    sday="samedi";
    break;
  }
  switch (months)
  {
    case 1:
    smonth="JAN";
    break;
   case 2:
    smonth="FEV";
    break;
     case 3:
    smonth="MAR";
    break;
     case 4:
    smonth="AVR";
    break;
     case 5:
    smonth="MAI";
    break;
     case 6:
    smonth="JUI";
    break;
     case 7:
    smonth="JUL";
    break;
     case 8:
     smonth="AOU";
    break;
     case 9:
    smonth="SEP";
    break;
    case 10:
    smonth="OCT";
    break;
     case 11:
    smonth="NOV";
    break;
     case 12:
    smonth="DEC";
    break;
  }
  
}

//------------------

void trans(byte(n))
{
   switch(n)
  {
  case 0:
  for(int i=0;i<8;i++)
  y[i]=ZERO[i];
  break;
  case 1:
  for(int i=0;i<8;i++)
  y[i]=UN[i];
  break;
  case 2:
  for(int i=0;i<8;i++)
    y[i]=DEUX[i];
  break;
  case 3:
  for(int i=0;i<8;i++)
   y[i]=TROIS[i];
  break;
  case 4:
  for(int i=0;i<8;i++)
   y[i]=QUATRE[i];
  break;
  case 5:
  for(int i=0;i<8;i++)
   y[i]=CINQ[i];
  break;
  case 6:
  for(int i=0;i<8;i++)
    y[i]=SIX[i];
  break;
  case 7:
  for(int i=0;i<8;i++)
   y[i]=SEPT[i];
   break;
   case 8:
   for(int i=0;i<8;i++)
    y[i]=HUIT[i];
  break;
  case 9:
  for(int i=0;i<8;i++)
   y[i]=NEUF[i];
    break;
  }
}

//-----------------------------------------------   


void led_clear()
{
  printByte3(EX);
  printByte2(EX);
  printByte1(EX);
  printByte0(EX);
  }

//-------------

//---

void loop() 
{
    
  switch(sp)
  {
     case 0:
      
   for (int i=3;i>0;i--)
    {
      text[i]=text[i-1];
    }
   text[0]=data[k];
aff_mesg(data);
k++;
if (k > data.length())
{
  led_clear();
  for (int i=0;i<4;i++)
  {
 text[i]=' ';
  }
 sp=1;
  led_clear();
 delay(1000);
k=0;
}
break;
//----------------------------------
case 1:
 for (int i=3;i>0;i--)
    {
      text[i]=text[i-1];
    }
   text[0]=data0[k];
aff_mesg(data0);
k++;
if (k>data0.length())
{
  led_clear();
  for (int i=0;i<4;i++)
  {
 text[i]=' ';
  }
 k=0;
}
//--
if (digitalRead(button3)==LOW) 
 {
  lcd.clear();
digitalWrite(buzzer,!digitalRead(buzzer));
 while(digitalRead(button3)==LOW) 
     {
     
            }
   digitalWrite(buzzer,LOW);
   EEPROM.put(100,0);
  EEPROM.put(300,0);
   lcd.setCursor(0,0);
  lcd.print("data removed");
  delay(1000);
  number=0;
  gh=0;
  lcd.clear();
     }
  //----------------------------------------- 

 else if (digitalRead(button4)==LOW) 
 {
 
    digitalWrite(buzzer,!digitalRead(buzzer));
 while(digitalRead(button4)==LOW) 
     {
     
       }
digitalWrite(buzzer,LOW);
NMAX=0;
lcd.clear();
sp=8;
 }
 //----------------------------------      
 else if (digitalRead(button5)==LOW )
 {
    digitalWrite(buzzer,!digitalRead(buzzer));
    
 while(digitalRead(button5)==LOW )
     {
      
       }
       digitalWrite(buzzer,LOW);
     number1=0;
     number2=0;
     number3=0;
     number4=0;
 conv_to_bcd(number);
   trans(u0);
   printByte0(y);
   trans(u1);
   printByte1(y);
   trans(u2);
   printByte2(y);
   transG(gh);
   printByte3(y);
   lcd.clear();
    sp=2;
   
 }
   break; 
  
 case 2:
   dht11();
     rtc_time ();
     find_days_months ();
    lcd_affichage(); 
    if (digitalRead(button1)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button1)==LOW)
     {
  
     }
       digitalWrite(buzzer,LOW);
   gh=1;
   number++;
   number1++;
   lcd.clear();
    led_clear();
      }
      //----------------------------------------- 
   else if (digitalRead(button2)==LOW)
    {
   digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button2)==LOW)
     {
     
     }
       digitalWrite(buzzer,LOW);
   lcd.clear();
  gh=2;
   number++; 
      number2++;
       led_clear();
       }
   //----------------------------------------------
 else if (digitalRead(button3)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button3)==LOW)
     {
     
     }
      digitalWrite(buzzer,LOW);
    lcd.clear();
     led_clear();
      gh=3;
  number++; 
     number3++;
   
   }
 //----------------------------------------- 
    else if (digitalRead(button4)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button4)==LOW)
     {
   
     }
      digitalWrite(buzzer,LOW);
    lcd.clear();
     led_clear();
       gh=4;
  number++; 
     number4++;
   
   }
   //-----------------------------------------------
  
 else if (digitalRead(button5)==LOW )
    {
    digitalWrite(buzzer,!digitalRead(buzzer));
delay(100);
  while  (digitalRead(button5)==LOW)
     {
     
     }
      digitalWrite(buzzer,LOW);
      lcd.clear();
       led_clear();
      sp=3;
      }
 //----------------------------------------- 
    
 if (last_number!=number)
  {
  last_number=number;
    if(number >= NMAX)
  {
    number=0;
  }
   EEPROM.put(100,number);
   EEPROM.put(300,gh);
   conv_to_bcd(number);
   trans(u0);
   printByte0(y);
   trans(u1);
   printByte1(y);
   trans(u2);
   printByte2(y);
   transG(gh);
   printByte3(y);
  }
 break;
 //----------------------------------------- 
case 3:
adjust_minutes();
break;
case 4:
adjust_hours();
break;
case 5:
adjust_days();
break;
case 6:
adjust_months();
break;
case 7:
adjust_years();
break;
case 8:
adjust_NMax();
break;
  }
   }

//----------------------------------------------------------------


//------

void adjust_minutes()
{
  lcd.setCursor(0,0);
  lcd.print("adjust_minutes ");
   lcd.setCursor(0,1);
  lcd.print(minutes);
   conv_to_bcd(minutes);
   trans(u0);
   printByte0(y);
   trans(u1);
   printByte1(y);
   printByte2(N);
  printByte3(M);
   //----------------------------------------- 
    if (digitalRead(button1)==LOW )
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button1)==LOW)
     {
      
     }
  digitalWrite(buzzer,LOW);
minutes++;
 if (minutes>59)
      {
        minutes=0;
      }    
      }
    //-----------------------------------------    
    else if (digitalRead(button2)==LOW )
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button2)==LOW)
     {
           }
      digitalWrite(buzzer,LOW);
      minutes--;
       if (minutes <0)
      {
        minutes=59;
      }    
    
      }
      
 //----------------------------------------- 
else if (digitalRead(button3)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button3)==LOW)
     {
       }
 rtc.adjust(DateTime(years, months, days, hours, minutes, seconds));
  digitalWrite(buzzer,LOW);
lcd.clear();
 sp=0;
    }
 //----------------------------------------- 
    else if (digitalRead(button4)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button4)==LOW )
     {
      
     }
      rtc.adjust(DateTime(years, months, days, hours, minutes, seconds));
        digitalWrite(buzzer,LOW);
      lcd.clear();
        sp=4;
        }
        
       
} 
//--------------------------------------------------
void adjust_hours()

   {
    lcd.setCursor(0,0);
  lcd.print("adjust_hours ");
   lcd.setCursor(0,1);
  lcd.print(hours);
  
    conv_to_bcd(hours);
    trans(u0);
   printByte0(y);
   trans(u1);
   printByte1(y);
   printByte2(R);
  printByte3(H);
   //----------------------------------------- 
    if (digitalRead(button1)==LOW )
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button1)==LOW)
     {
      
     }
  digitalWrite(buzzer,LOW);
hours++;
  if (hours >23)
      {
        hours=0;
      }   
      }
      //-----------------------------------------  
    else if (digitalRead(button2)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button2)==LOW)
     {
      
     }
      digitalWrite(buzzer,LOW);
   hours--;
     if (hours<0)
      {
       hours=23;
      }   
    
      }
 //----------------------------------------- 
else if (digitalRead(button3)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button3)==LOW)
     {
      
     }
 rtc.adjust(DateTime(years, months, days, hours, minutes, seconds));
  digitalWrite(buzzer,LOW);
  lcd.clear();
  sp=0;
    }
  //----------------------------------------- 
    else if (digitalRead(button4)==LOW )
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button4)==LOW)
     {
      
     }
    
          rtc.adjust(DateTime(years, months, days, hours, minutes, seconds));
        digitalWrite(buzzer,LOW);
        lcd.clear();
        sp=5;
        }  
        
   }  
  //--------------------------------------------------------------------------------
void adjust_days()
{
  lcd.setCursor(0,0);
  lcd.print("adjust_days ");
   lcd.setCursor(0,1);
  lcd.print(days);
      conv_to_bcd(days);
    trans(u0);
   printByte0(y);
   trans(u1);
   printByte1(y);
   printByte2(Y);
  printByte3(D);
   //----------------------------------------- 
    if (digitalRead(button1)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button1)==LOW)
     {
      
     }
  digitalWrite(buzzer,LOW);
days++;
   if (days>31)
      {
        days=0;
      }   
      }
   //-----------------------------------------   
    else if (digitalRead(button2)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button2)==LOW)
     {
      
     }
      digitalWrite(buzzer,LOW);
     days--;
        if (days<1)
      {
        days=31;
      }   
    
      }
//---------------------------------------------------------------
else if (digitalRead(button3)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button3)==LOW)
     {
      
     }
 rtc.adjust(DateTime(years, months, days, hours, minutes, seconds));
  digitalWrite(buzzer,LOW);
  lcd.clear();
  sp=0;
    }
    //----------------------------------------------------------------
    else if (digitalRead(button4)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button4)==LOW)
     {
      
     }
      rtc.adjust(DateTime(years, months, days, hours, minutes, seconds));
        digitalWrite(buzzer,LOW);
        sp=6;
        lcd.clear();
        }   
      
      }
//---------------------------------------------------------------------------------
void adjust_months()
{
  lcd.setCursor(0,0);
  lcd.print("adjust_months");
   lcd.setCursor(0,1);
  lcd.print(months);
  
    conv_to_bcd(months);
    trans(u0);
   printByte0(y);
   trans(u1);
   printByte1(y);
   printByte2(O);
  printByte3(M);
  //-----------------------------------------------------------
    if (digitalRead(button1)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button1)==LOW)
     {
           }
  digitalWrite(buzzer,LOW);
months++;
  if (months > 12)
      {
       months=0;
      } 
        
      }
  //----------------------------------------------------------------------------    
    else if (digitalRead(button2)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button2)==LOW)
     {
           }
      digitalWrite(buzzer,LOW);
     months--;
      if (months < 1)
      {
       months=12;
      }   
      }
//---------------------------------------------------------------------------------
else if (digitalRead(button3)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button3)==LOW)
     {
      
     }
 
  digitalWrite(buzzer,LOW);
  lcd.clear();
  sp=0;
    }
    //-----------------------------------------------------------------------------
    else if (digitalRead(button4)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button4)==LOW)
     {
      
     }
      rtc.adjust(DateTime(years, months, days, hours, minutes, seconds));
        digitalWrite(buzzer,LOW);
        lcd.clear();
        sp=7;
        }   
       
} 
      //-----
void adjust_years()
{
  lcd.setCursor(0,0);
  lcd.print("adjust_years");
   lcd.setCursor(0,1);
  lcd.print(years);
  
    conv_to_bcd(years);
    trans(u0);
   printByte0(y);
   trans(u1);
   printByte1(y);
   printByte2(R);
  printByte3(Y);
  //-----------------------------------------------------------------------
   if (digitalRead(button1)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button1)==LOW)
     {
      
     }
  digitalWrite(buzzer,LOW);
years++;
    if (years>2060)
      {
     years=2020;
      } 
    }  
    //-------------------------------------------------------------------------------------
    else if (digitalRead(button2)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button2)==LOW)
     {
      
     }
      digitalWrite(buzzer,LOW);
      years--;
      if (years<2020)
      {
     years=2020;
      }   
      }
//---------------------------------------------------------------------------------
else if (digitalRead(button3)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button3)==LOW)
     {
      
     }
   digitalWrite(buzzer,LOW);
    rtc.adjust(DateTime(years, months, days, hours, minutes, seconds));
    lcd.clear();
  sp=0;
    }
    //------------------------------------------------------------------------------
    else if (digitalRead(button4)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));

  while  (digitalRead(button4)==LOW)
     {
      
     }
      rtc.adjust(DateTime(years, months, days, hours, minutes, seconds));
        digitalWrite(buzzer,LOW);
        lcd.clear();
       sp=8;
        }   
     

}
 //--------------------  
   void adjust_NMax()
   {
    lcd.setCursor(0,0);
  lcd.print("adjust_NMAX");
   lcd.setCursor(0,1);
  lcd.print(NMAX);
      conv_to_bcd(NMAX);
    trans(u0);
    printByte0(y);
    trans(u1);
    printByte1(y);
    trans(u2);
    printByte2(y);
    trans(u3);
   printByte3(y);
  
   
    if (digitalRead(button1)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));
  while (digitalRead(button1)==LOW)
     {
      
     }
NMAX=NMAX+100;
  if (NMAX>1000)
      {
   NMAX=1000;
      }   
  digitalWrite(buzzer,LOW);
      }
      //--------------------------------------------------
   else if (digitalRead(button2)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));
  while (digitalRead(button2)==LOW)
     {
      
     }
NMAX=NMAX-100;
if (NMAX<0)
      {
   NMAX=0;
      } 
  digitalWrite(buzzer,LOW);
      }
//------------------------------------------------------------
 else if (digitalRead(button3)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));
  while (digitalRead(button3)==LOW)
     {
      
     }
     lcd.clear();
     digitalWrite(buzzer,LOW);
  EEPROM.put(200,NMAX);
sp=0;
 
      }
      //-----------------------------------------------
            
    else if (digitalRead(button4)==LOW)
    {
    digitalWrite(buzzer,!digitalRead(buzzer));
  while (digitalRead(button4)==LOW)
     {
      
     }
     lcd.clear();
     digitalWrite(buzzer,LOW);
         EEPROM.put(200,NMAX);
        sp=3;
    
      }
        
        
  }

  

 void aff_mesg( String str)
{ 
  transstr(text[7]);
 for(int i=0;i<8;i++)
{
 m[i]=matrice[y0-1][i]; 

}
 
printByte7(m);
 //----
 (text[6]);
 
 for(int i=0;i<8;i++)
{
m[i]=matrice[y0-1][i]; 
 
}
printByte6(m);
//-------
transstr(text[5]); 
for(int i=0;i<8;i++)
{
  m[i]=matrice[y0-1][i]; 
}
printByte5(m);
//-------
 transstr(text[4]);

for(int i=0;i<8;i++)
{
m[i]=matrice[y0-1][i]; 
 // Serial.println(m[i],BIN);
}

printByte4(m);
 //-------
transstr(text[3]);

for(int i=0;i<8;i++)
{
 
m[i]=matrice[y0-1][i]; 
  //Serial.println(m[i],BIN);
}
printByte3(m); 
//-------
transstr(text[2]);

for(int i=0;i<8;i++)
{
m[i]=matrice[y0-1][i]; 
  // Serial.println(m[i],BIN);
}
printByte2(m);
//-------
transstr(text[1]);

for(int i=0;i<8;i++)
{
 m[i]=matrice[y0-1][i]; 
}
printByte1(m);
//-------  
transstr(text[0]);

for(int i=0;i<8;i++)
{
m[i]=matrice[y0-1][i]; 

}
printByte0(m);

delay(200);
}
 
void printByte0(byte character [])
{
  int i = 0;
  
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
   }

//--------------------------------------------
void printByte1(byte character [])
{
  int i = 0;
  
  for(i=0;i<8;i++)
  {
    lc.setRow(1,i,character[i]);
  }
   }
   //-----------------------------------------------------
   void printByte2(byte character [])
{
  int i = 0;
  
  for(i=0;i<8;i++)
  {
    lc.setRow(2,i,character[i]);
  }
   }
   //--------------
   void printByte3(byte character [])
{
  int i = 0;
  
  for(i=0;i<8;i++)
  {
    lc.setRow(3,i,character[i]);
  }
   }
   //--------------
   void printByte4(byte character [])
{
  int i = 0;
  
  for(i=0;i<8;i++)
  {
    lc.setRow(4,i,character[i]);
  }
   }
   //------
    void printByte5(byte character [])
{
  int i = 0;
  
  for(i=0;i<8;i++)
  {
    lc.setRow(5,i,character[i]);
  }
   }
   //---
    void printByte6(byte character [])
{
  int i = 0;
  
  for(i=0;i<8;i++)
  {
    lc.setRow(6,i,character[i]);
  }
   }
   //--
    void printByte7(byte character [])
{
  int i = 0;
  
  for(i=0;i<8;i++)
  {
    lc.setRow(7,i,character[i]);
  }
   }
  //--
  void transstr(char c)
{
  switch (c)
  {
  case 'A':
  y0=1;
  break;
  case 'B':
  y0=2;
  break;
  case 'C':
  y0=3;
  break;
  case 'D':
  y0=4;
  break;
  case 'E':
  y0=5;
  break;
  case 'F':
  y0=6;
  break;
  case 'G':
  y0=7;
  break;
  case 'H':
  y0=8;
  break;
  case 'I':
  y0=9;
  break;
  case 'J':
  y0=10;
  break;
  case 'K':
  y0=11;
  break;
  case 'L':
  y0=12;
  break;
  //------
case 'M':
  y0=13;
  break;
  case 'N':
  y0=14;
  break;
//--------
case 'O':
  y0=15;
  break;
  case 'P':
  y0=16;
  break;
  //----------
case 'Q':
  y0=17;
  break;
  case 'R':
  y0=18;
  break;
  //-----------
case 'S':
  y0=19;
  break;
  case 'T':
  y0=20;
  break;
  //----------
case 'U':
  y0=21;
  break;
  case 'V':
  y0=22;
  break;
  //------
case 'W':
  y0=23;
  break;
  case 'X':
  y0=24;
  break;
  //------
case 'Y':
  y0=25;
  break;
  case 'Z':
  y0=26;
  break;
   case ' ':
  y0=27;
  break;
   case '\'': //'//
  y0=28;
  break;
   case '/':
  y0=29;
  break;
   case '>':
  y0=30;
  break;
  case '<':
  y0=31;
  break;
  }
}
