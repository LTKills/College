#include <stdlib.h>
#include <stdio.h>

int
main ()
{
  int a1, r, n, i;
  double sum, v;
  int *vec;
  scanf ("%d %d %d", &a1, &r, &n);
  vec = (int *) malloc (sizeof (int) * n);


  vec[0] = a1;
  for (i = 1; i < n; i++)
    {
      vec[i] = vec[i - 1] + r;
    }


  v = (double) vec[0] + vec[n - 1];
  sum = ((v * n) / 2);


  printf ("%d\n%.0lf\n", vec[n - 1], sum);
  free (vec);
  return 0;
}
