#include <stdlib.h>
#include <stdio.h>



int
main (int argc, char *argv[])
{
  int n, m, j, i = 0, k;
  scanf ("%d %d %d", &n, &m, &j);

  for (k = 0; k < n; i++)
    {
      if (i % j == m % j)
	{
	  printf ("%d\n", i);
	  k++;
	}
    }

  return 0;
}
