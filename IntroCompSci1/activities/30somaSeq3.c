#include <stdlib.h>
#include <stdio.h>

int
main ()
{
  int i, n;
  float k, sum, l;
  scanf ("%d", &n);

  for (i = 0; i < n; i++)
    {
      k = (2 * i) + 1;
      l = n - i;
      sum += k / l;
    }

  printf ("%.4f\n", sum);
  return 0;
}
