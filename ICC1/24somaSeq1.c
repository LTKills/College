#include <stdlib.h>
#include <stdio.h>

int
main ()
{
  int i;
  float s = 0, n;
  scanf ("%f", &n);


  for (i = 1; i <= n; i++)
    {
      s += i / (n - i + 1);
    }


  printf ("%.4f\n", s);
  return 0;
}
