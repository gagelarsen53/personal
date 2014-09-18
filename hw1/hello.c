#include <stdio.h>

int main(void)
{
  int MAXLENGTH = 100;
  char name[MAXLENGTH];

  printf("Gage Larsen\n");
  printf("10645288\n\n");

  printf("What is your name? ");
  scanf("%s", name);

  printf("Hello %s\n", name);

  return 0;
}
