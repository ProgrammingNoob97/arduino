#include <VirtualWire.h>

char morse[] = {'\0','T','E','M','N','A','I','O','G','K','D','W','R','U','S','\0','\0','Q','Z','Y','C','X','B','J','P','\0','L','\0','F','V','H'};

char letter;

char decode(char *code, int size)
{
  int pos;
  int i = 0;
  while (i < size){
      if (code[i] == '0')   // 0 <=> Dot
          pos = 2*pos + 2;
      if (code[i] == '1')   // 1 <=> Dash
          pos = 2*pos + 1;
      i++;
  }
  return morse[pos];
}

void setup()
{
  vw_set_ptt_inverted(true);
  vw_setup(1024);
  vw_set_rx_pin(8);
  vw_rx_start();
  Serial.begin(9600);
  Serial.println("-----Start-----");
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  while(vw_get_message(buf, &buflen))
  {
    Serial.println((const char*)buf);
    letter = decode((char*)buf, buflen);
    Serial.println(letter);
  }
}
