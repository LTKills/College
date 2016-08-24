#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int
main ()
{
  int i = 0, j = 0;
  // i para numeros, j para chars
  char c;
  do
    {
      c = fgetc (stdin);
      if (isalpha (c) != 0)
	{
	  i++;
	}
      else if (isdigit (c) != 0)
	{
	  j++;
	}
    }
  while (c != 10);



  printf ("%d\n%d\n", i, j);

  return 0;
}
