#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
  int n, i, j, k, a = 0;
  int *vec;
  scanf ("%d %d %d", &n, &i, &j);

  vec = malloc (sizeof (int) * n);
  for (k = 0; a < n; k++)
    {
      if (k % i == 0 | k % j == 0)
	{
	  vec[a] = k;
	  a++;
	}
    }

  for (k = 0; k < n; k++)
    {
      printf ("%d\n", vec[k]);
    }


  free (vec);
  return 0;
}
