// Code by LTKills
#include <stdio.h>
int
main ()
{
  float a, b, r;
  char c;
  scanf ("%f %c %f", &a, &c, &b);
  switch (c)
    {
    case '+':
      r = a + b;
      printf ("%f\n", r);
      break;
    case '-':
      r = a - b;
      printf ("%f\n", r);
      break;
    case '*':
      r = a * b;
      printf ("%f\n", r);
      break;
    case '/':
      r = a / b;
      printf ("%f\n", r);
      break;
    case '%':
      r = 100 * a / b;
      printf ("%f\n", r);
      break;
    }
  return 0;
}
