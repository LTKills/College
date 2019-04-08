#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int
main (int argc, char *argv[])
{
  int a, b, c, d, num, num1, num2, n;

  for (n = 1000; n < 10000; n++)
    {
      num = n;
      a = num / 1000;
      num -= a * 1000;
      b = num / 100;
      num -= b * 100;
      c = num / 10;
      num -= c * 10;
      d = num / 1;
      num1 = 10 * a + b;
      num2 = 10 * c + d;
      if (sqrt (n) == num1 + num2)
	{
	  printf ("%d\n", n);
	}
    }
  return 0;
}
