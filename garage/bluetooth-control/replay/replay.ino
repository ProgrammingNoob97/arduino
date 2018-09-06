#include <LowPower.h>

//Bluetooth Signals
const unsigned char bt_open  = 0xff;
const unsigned char bt_close = 0xa5;
const unsigned char bt_stop  = 0x7e;
const unsigned char bt_lock  = 0xb9;
//Relay pins
const int open     = 8;
const int close    = 9;

//Bluetooth pins
const int ledPin  = 5;
const int wakePin = 2;

unsigned char bt_signal;

void wakeUp()
{
    digitalWrite(ledPin, HIGH); //LED ON
    //Wake up Arduino, do not thing more!
}

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(wakePin, INPUT);
    pinMode(open, OUTPUT);
    pinMode(close, OUTPUT);   
    Serial.begin(9600);
}

void loop()
{
    if(digitalRead(wakePin) == LOW)
    {
        digitalWrite(ledPin, LOW);// Led OFF
        attachInterrupt(0, wakeUp, HIGH); //Set trigger to pin 2 for waking up arduino at HIGH
        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); //Arduino Sleeping time is interval time between led on and led off!!
    }

    if(Serial.available() > 0)
    {
        bt_signal = Serial.read();
        switch(bt_signal)
        {
            case bt_open:
                digitalWrite(open, HIGH)
                delay(500);
                digitalWrite(open, LOW)
                break;
            case bt_close:
                digitalWrite(close, HIGH);
                delay(500);
                digitalWrite(close, LOW);
                break;
            default:
                break;   
        }
    }
}
