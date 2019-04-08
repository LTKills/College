#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int
main ()
{
  int n, i;
  float d = 0;
  float *abss;
  float *ord;
  float *dist;

  scanf ("%d", &n);

  abss = (float *) malloc (sizeof (float) * n);
  ord = (float *) malloc (sizeof (float) * n);
  dist = (float *) malloc (sizeof (float) * (n - 1));

  for (i = 0; i < n; i++)
    {
      scanf ("%f %f", &abss[i], &ord[i]);
    }

  for (i = 0; i < n - 1; i++)
    {
      dist[i] =
	sqrt (pow (abss[i] - abss[i + 1], 2) + pow (ord[i] - ord[i + 1], 2));
    }

  for (i = 0; i < n - 1; i++)
    {
      d = d + dist[i];
    }
  printf ("%.4f\n", d);

  free (abss);
  free (ord);
  return 0;
}
