#include <stdlib.h>
#include <stdio.h>
int
main ()
{
  int k, i;
  float r;
  float y;
  float *x;

  scanf ("%f %f %d", &y, &r, &k);
  x = malloc (sizeof (float) * k);
  x[0] = y;

  for (i = 1; i <= k; i++)
    {
      x[i] = r * x[i - 1] * (1 - x[i - 1]);
      printf ("%d %f\n", i, x[i]);

    }
}
