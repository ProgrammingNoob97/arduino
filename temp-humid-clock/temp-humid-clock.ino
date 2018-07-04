#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "RTClib.h"


#define DHTPIN  8
#define DHTTYPE DHT11

RTC_DS3231 rtc;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat"};

char hour[2];
char minute[2];

unsigned long timing;
unsigned long sensor_timing;

void setup () {
    dht.begin();
    lcd.begin(16, 2);   
    if (! rtc.begin()) {
        lcd.setCursor(0, 0);
        lcd.println("No RTC!");
        while (1);
  }

  if (rtc.lostPower()) {
    lcd.setCursor(0, 0);
    lcd.print("RTC lost power!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  
  while(rtc.now().second() != 0);
  timing = millis();
  lcd.setCursor(12, 0);
  lcd.print(":");
}


void loop()
{
    if((unsigned long)(millis() - timing) == 60000)
    {
    DateTime now = rtc.now();

    sprintf(hour, "%2d", now.hour());
    sprintf(minute, "%2d", now.minute());

    lcd.setCursor(4, 0);
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.setCursor(9, 0);
    lcd.print(hour);
    lcd.setCursor(13, 0);
    lcd.print(minute);

    timing = millis();
    
    }

   if((unsigned long)(millis() - sensor_timing) == 1000)
    {
        int temp = dht.readTempature();
        int humid = dht.readHumidity();

        lcd.setCursor();
        lcd.print();
        lcd.setCursor();
        lcd.print();
    }
}