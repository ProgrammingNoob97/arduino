#include <RCSwitch.h>
#include <LowPower.h>

//Bluetooth Signals
const unsigned char bt_open  = 0xff;
const unsigned char bt_close = 0xa5;
const unsigned char bt_stop  = 0x7e;
const unsigned char bt_lock  = 0xb9;

//RF315 Signals
const char *open_signal     = "101010001101111110110100"; //Open garage
const char *close_signal    = "101010001101111110111000"; //Close garage
const char *stop_signal     = "101010001101111110110010"; //Stop/Unlock garage
const char *lock_signal     = "101010001101111110110001"; //Lock garage

const int ledPin  = 5;
const int wakePin = 2;
//const int RFpower = 8; // RF Transmit power pin

unsigned char bt_signal;
RCSwitch rc = RCSwitch();

void wakeUp()
{
    digitalWrite(ledPin, HIGH); //LED ON
    //Wake up Arduino, do not thing more!
}

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(wakePin, INPUT);
    //pinMode(RFpower, OUTPUT);
    rc.enableTransmit(10);
    rc.setProtocol(1);
    rc.setPulseLength(248);
    rc.setRepeatTransmit(3);    
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
                rc.send(open_signal);
                delay(200);
                break;
            case bt_close:
                rc.send(close_signal);
                delay(200);
                break;
            case bt_stop:
                rc.send(stop_signal);
                delay(200);
                break;
            case bt_lock:
                rc.send(lock_signal);
                delay(200);
                break;
            default:
                break;   
        }
    }
}
