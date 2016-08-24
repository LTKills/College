#include <stdio.h>
#include <math.h>
int
main ()
{
  float a, b;
  scanf ("%f %f", &a, &b);
  printf ("%.4f\n", pow (a, b));
  return 0;
}
