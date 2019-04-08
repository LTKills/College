#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
int
main ()
{
  int n, i, min, max;
  int *vetor;

  scanf ("%d", &n);

  vetor = (int *) malloc (sizeof (int) * n);

  for (i = 0; i < n; i++)
    {
      scanf ("%d", &vetor[i]);
    }

  min = INT_MAX;
  max = INT_MIN;

  for (i = 0; i < n; i++)
    {
      if (vetor[i] > max)
	{
	  max = vetor[i];
	}

      if (vetor[i] < min)
	{
	  min = vetor[i];
	}
    }
  printf ("max: %d\nmin: %d\n", max, min);

  free (vetor);

  return 0;
}
