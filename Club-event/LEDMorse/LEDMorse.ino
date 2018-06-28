char buff;

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
void space()
{
  digitalWrite(13, LOW);
  delay(1000);
}
void letter_a()
{
  dot();
  dash();
}
void letter_b()
{
  dash();
  dot();
  dot();
  dot();
}
void letter_c()
{
  dash();
  dot();
  dash();
  dot();
}

void letter_d()
{
  dash();
  dot();
  dot();
}
void letter_e()
{
  dot();
}

void letter_f()
{
  dot();
  dot();
  dash();
  dot();
}

void letter_g()
{
  dash();
  dash();
  dot();
}

void letter_h()
{
  dot();
  dot();
  dot();
  dot();
}

void letter_i()
{
  dot();
  dot();
}

void letter_j()
{
  dot();
  dash();
  dash();
  dash();
}

void letter_k()
{
  dash();
  dot();
  dash();
}

void letter_l()
{
  dot();
  dash();
  dot();
  dot();
}

void letter_m()
{
  dash();
  dash();
}

void letter_n()
{
  dash();
  dot();
}

void letter_o()
{
  dash();
  dash();
  dash();
}

void letter_p()
{
  dot();
  dash();
  dash();
  dot();
}

void letter_q()
{
  dash();
  dash();
  dot();
  dash();
}

void letter_r()
{
  dot();
  dash();
  dot();
}

void letter_s()
{
  dot();
  dot();
  dot();
}

void letter_t()
{
  dash();
}

void letter_u()
{
  dot();
  dot();
  dash();
}

void letter_v()
{
  dot();
  dot();
  dot();
  dash();
}

void letter_w()
{
  dot();
  dash();
  dash();
}

void letter_x()
{
  dash();
  dot();
  dot();
  dash();
}

void letter_y()
{
  dash();
  dot();
  dash();
  dash();
}

void letter_z()
{
  dash();
  dash();
  dot();
  dot();
}

void num0()
{
  dash();
  dash();
  dash();
  dash();
  dash();
}
void num1()
{
  dot();
  dash();
  dash();
  dash();
  dash();
}

void num2()
{
  dot();
  dot();
  dash();
  dash();
  dash();
}

void num3()
{
  dot();
  dot();
  dot();
  dash();
  dash();
}

void num4()
{
  dot();
  dot();
  dot();
  dot();
  dash();
}
void num5()
{
  dot();
  dot();
  dot();
  dot();
  dot();
}

void num6()
{
  dash();
  dot();
  dot();
  dot();
  dot();
}

void num7()
{
  dash();
  dash();
  dot();
  dot();
  dot();
}

void num8()
{
  dash();
  dash();
  dash();
  dot();
  dot();
}

void num9()
{
  dash();
  dash();
  dash();
  dash();
  dot();
}

void (*alpha[26])() = {
  letter_a, letter_b, letter_c, letter_d, letter_e, letter_f, letter_g,
  letter_h, letter_i, letter_j, letter_k, letter_l, letter_m, letter_n,
  letter_o, letter_p, letter_q, letter_r, letter_s, letter_t, letter_u,
  letter_v, letter_w, letter_x, letter_z
  };
void (*num[10])() = {num0, num1, num2, num3, num4, num5, num6, num7, num8, num9};

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available() > 0)
  {
    buff = Serial.read();

    Serial.print("Got:");
    Serial.println(buff);
    if(buff >= 'a' && buff <= 'z')
    {
      alpha[buff - 'a']();
    }
    if(buff >= '0' && buff <= '9')
    {
      num[buff - '0']();
    }
    if(buff == ' ')
    {
      space();
    }
  }
}
