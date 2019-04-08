#include <stdio.h>
int
main ()
{
  int n, i;
  scanf ("%d", &n);

  for (i = 1; i < (2 * n);)
    {
      printf ("%d\n", i);
      i = i + 2;
    }
  return 0;
}
