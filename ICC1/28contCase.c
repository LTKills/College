#include <stdlib.h>
#include <stdio.h>

char *
readline (int n)
{
  int i = 0;
  char *c;
  c = (char *) malloc (sizeof (char) * n);
  while (i < n)
    {
      fgetc (stdin);
      c[i] = fgetc (stdin);
      i++;
    }
  return c;
}


int
main (void)
{
  int n, i, k = 0, j = 0;
  char *c = NULL;
  scanf ("%d", &n);
  c = readline (n);

  for (i = 0; i < n; i++)
    {
      if ((int) c[i] >= 65 && (int) c[i] <= 90)
	{
	  j++;			// maiuscula
	}
      else if ((int) c[i] >= 97 && (int) c[i] <= 122)
	{
	  k++;			// minuscula
	}
    }

  printf ("%d %d\n", j, k);
  free (c);
  return 0;
}
