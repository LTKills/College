// Code by LTKills
#include <stdio.h>
#include <math.h>
int
main ()
{
  float num, fracionaria, inteira;
  scanf ("%f", &num);
  fracionaria = modff (num, &inteira);
  printf ("%.0f\n%.4f\n%.0f\n", inteira, fracionaria, num);
  return 0;
}
