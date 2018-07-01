#include <Keypad.h>
#include <RCSwitch.h>

bool is_change= false;
bool is_check = false;
//Initialize buzzer pin
const int buzzer = 12;

//Initialize transmitting pins
const int transmitt = 13;

//Initialize RBG LED pins
const int led_red   = 9;
const int led_green = 10;

//Initialize read index;
int read_index;
//Initialize password buffers
char *password = (char*)malloc(sizeof(char) * 255);
char *password_buffer = (char*)malloc(sizeof(char) * 255);

//Initialize keypad
const byte rows = 4;
const byte cols = 3;

char keys[rows][cols] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*'. '0', '#'}
}

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

void key_beeping(void)
{
    tone()
}

void valid_beeping(void)
{
    tone()
}

void invalid_beeping(void)
{
    tone()
}
void reset_password(void)
{
    memset(password, '\0', 255);
    strcpy(password, "17061997");
}

void set_password(void)
{
    memset(password, '\0', 255);
    strcpy(password, password_buffer);
    memset(password_buffer, '\0', 255); 
}

void input_password(char key)
{
    password_buffer[read_index++] = key;
}

bool authenticate(void)
{
    if(strcmp(password, password_buffer) == 0)
    {
        memset(password, '\0', 255);
        return true;
    }
    memset(password, '\0', 255);
    return false;
}

void setup()
{
    pinMode(buzzer, OUTPUT);
    pinMode(led_red, OUTPUT);
    rc.enableTransmit(transmitt);
    rc.setProtocol(1);
    rc.setPulseLength(248);
    rc.setRepeatTransmit(3);    
    reset_password();
}

void loop()
{
    char key = keypad.getKey();  
    if(key != NO_KEY)
    {
        if(!is_change && !is_check)
        {
            if(key == '#')
            {
                read_index = 0;
                is_check = true;
            }
            else if(key == '*')
            {
                read_index = 0;
                is_change = true;
            }
            else if(key == '0')
            {
                reset_password();
            }
        }
        else
        {
            if(key == '#')
            {
                if(is_check == true)
                {
                    if(authenticate())
                    {
                        open_garage();
                        valid_beeping();
                        digitalWrite(led_red, LOW);
                        digitalWrite(led_green, HIGH);
                    }
                    else
                    {
                        invalid_beeping();
                        digitalWrite(led_green, LOW);
                        digitalWrite(led_red, HIGH);
                    }
                    is_check = false;
                }
                else if(is_change == true)
                {
                    set_password();
                    valid_beeping();
                    is_change = false;
                }
            }
            else if(key != '*')
            {
                input_password(key);
                key_beeping();
            }
        }
    }
}
