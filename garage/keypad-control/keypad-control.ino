#include <Keypad.h>
#include <RCSwitch.h>
#include <EEPROM.h>

bool is_change= false;
bool is_check = false;
//Initialize buzzer pin
const int buzzer = 11;

//Initialize close button
const int close_button = 12;

//Initialize transmitting pins
const int transmitt = 13;

//Initialize RBG LED pins
const int led_red   = 9;
const int led_green = 10;

//Initialize keypad
const byte rows = 4;
const byte cols = 3;

char keys[rows][cols] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

byte rowPins[rows] = {5, 4, 3, 2};
byte colPins[cols] = {8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

RCSwitch rc = RCSwitch();
//Define RF315Mhz signals
const char *open_signal = "101010001101111110110100"; //Open garage
const char *close_signal= "101010001101111110111000"; //Close garage
const char *stop_signal = "101010001101111110110010"; //Stop/Unlock garage

void open_garage(void)
{
    rc.send(open_signal);
    delay(200);
}

void close_garage(void)
{
    rc.send(stop_signal);
    delay(200);
    rc.send(close_signal);
    delay(200);
}

void beep(void)
{
    digitalWrite(buzzer, HIGH);
    delay(20);
    digitalWrite(buzzer, LOW);
}

void invalid_beep(void)
{
    digitalWrite(buzzer, HIGH);
    delay(1200);
    digitalWrite(buzzer, LOW);
}

void setup()
{
    pinMode(buzzer, OUTPUT);
    pinMode(led_red, OUTPUT);
    pinMode(led_green, OUTPUT);
    pinMode(close_button, INPUT);
    rc.enableTransmit(transmitt);
    rc.setProtocol(1);
    rc.setPulseLength(248);
    rc.setRepeatTransmit(3);    
    Serial.begin(9600);
}

void loop()
{
    char key = keypad.getKey();
    if(key != NO_KEY)
    {
        Serial.println(key);
        beep();
    }
}
