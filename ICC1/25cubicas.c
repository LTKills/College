#include <stdlib.h>
#include <stdio.h>

void
imprime (int l, int j)
{
  int i;
  for (i = 0; i < l; i++)
    {
      printf ("%d ", ((2 * j) - 1));
      j++;
    }

  printf ("\n");
}


int
main ()
{
  int n, i, j = 1;
  scanf ("%d", &n);

  for (i = 1; i <= n; i++)
    {
      imprime (i, j);
      j += i;
    }
  return 0;
}
