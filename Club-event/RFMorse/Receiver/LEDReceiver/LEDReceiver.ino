#include <VirtualWire.h>

uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;

void dot()
{
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
}

void dash()
{
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}
void setup()
{
  vw_set_ptt_inverted(true);
  vw_set_rx_pin(8);
  vw_setup(1024);
  vw_rx_start();
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if(vw_get_message(buf, &buflen)
  {
    switch(buf){
      case '0':
      Serial.print("Receive: ");
      Serial.println("0");
      dot();
      break;
      case '1':
      Serial.print("Receive: ");
      Serial.println("1");
      dash();
      break;
      default:
      break;
    }
  }
