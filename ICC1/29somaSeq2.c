#include <stdlib.h>
#include <stdio.h>

int
main ()
{
  int i, n;
  float sum = 0, k;
  scanf ("%d", &n);


  for (i = 1; i <= n; i++)
    {
      k = i;
      if (i % 2 != 0)
	{
	  sum += (1 / k);
	}
      else
	{
	  sum -= (1 / k);
	}
    }


  printf ("%.4f\n", sum);
  return 0;
}
