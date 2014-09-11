#include <stdio.h>

int main(void)
{
  int MAXLENGTH = 100;
  char name[MAXLENGTH];

  printf("\nGage Larsen\n");
  printf("10645288\n\n");

  printf("What is your name? ");
  scanf("%s", name);

  printf("Hello, %s\n\n", name);

  return 0;
}
