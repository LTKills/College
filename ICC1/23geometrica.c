#include <stdlib.h>
#include <stdio.h>

int
main ()
{
  int i, n;
  double a1, q, sum;
  double *vec;
  scanf ("%lf %lf %d", &a1, &q, &n);
  vec = (double *) malloc (sizeof (double) * n);

  vec[0] = a1;
  sum = vec[0];
  for (i = 1; i < n; i++)
    {
      vec[i] = vec[i - 1] * q;
      sum += vec[i];
    }

  printf ("%.2lf\n%.2lf\n", vec[n - 1], sum);
  free (vec);
  return 0;
}
