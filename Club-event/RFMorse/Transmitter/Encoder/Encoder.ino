#include <VirtualWire.h>

char morse[] = {'\0','T','E','M','N','A','I','O','G','K','D','W','R','U','S','\0','\0','Q','Z','Y','C','X','B','J','P','\0','L','\0','F','V','H'};
int tree_size = sizeof(morse)/sizeof(char);

char letter;
char *code;

struct Stack
{
    char *data;
    int top;
    int capacity;
};

struct Stack *createStack(int size)
{
  struct Stack *n = (struct Stack*)(malloc(sizeof(struct Stack)));
  n->top = -1;
  n->capacity = size;
  n->data = (char*)(malloc(sizeof(char) * size));
  return n;
}

int isStackEmpty(struct Stack *stack)
{
  return stack->top == -1;
}

int isStackFull(struct Stack *stack)
{
  return (stack->top == stack->capacity - 1);
}

void push(struct Stack *stack, char data)
{
	if(isStackFull(stack))
	{
		return;
	}
  stack->data[++stack->top] = data;
}

char pop(struct Stack *stack)
{
  if(isStackEmpty(stack))
  {
    return '\0';
  }
  return stack->data[stack->top--];
}

int process(struct Stack *stack, int pos, char letter)
{
  int fd;
  if(pos > tree_size-1)
  {
    return 0;
  }
  else
  {
    if(morse[pos] == letter)
    {
      return 1;
    }
    else
    {
      push(stack, '1');
      fd = process(stack, pos*2 + 1, letter);

      if(fd == 1)
      {
        return 1;
      }
      else
      {
        pop(stack);
        push(stack, '0');
        fd = process(stack, pos*2 + 2, letter);
        if(fd == 1)
        {
          return 1;
        }
        else
        {
          pop(stack);
          return 0;
        }
      }
    }
  }
}
char *encode(char letter)
{
  int end;
  char *code = (char*)(malloc(sizeof(char) * 5));
  struct Stack *stack = createStack(5);

  process(stack, 0, letter);
  end = stack->top+1;

  while(!isStackEmpty(stack))
  {
    code[stack->top] = pop(stack);
  }
  code[end] = '\0';
  return code;
}

void setup()
{
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(8);
  vw_setup(1024);
  Serial.begin(9600);
  Serial.println("---Start---");
}

void loop()
{
  if(Serial.available())
  {
    letter = Serial.read();
    code = encode(letter);
    Serial.println("---Sending---");
    Serial.print("Code:");
    for(int i = 0; code[i] != '\0'; i++)
    {
      Serial.print(code[i]);
      vw_send((uint8_t*)(&code[i]), 1);
      vw_wait_tx();
      delay(200);
    }
    Serial.println();
  }
}
