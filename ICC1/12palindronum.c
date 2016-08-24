// Sim, exatamente a mesma merda do 11....... By LT

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void
readShit ()
{
  int n, i = 0, j = 0, k = 0;
  char input;
  char *string = NULL;

  do
    {
      input = fgetc (stdin);
      string = (char *) realloc (string, sizeof (char) * (i + 1));
      string[i++] = input;
    }
  while (input != 10);

  i = i - 2;

  n = i;


  while (i >= n / 2)
    {

      if (string[i] == string[j])
	{
	}

      else
	{
	  k++;
	}

      i--, j++;
    }

  if (k == 0)
    {
      printf ("SIM\n");
    }

  else
    {
      printf ("NAO\n");
    }

}



int
main ()
{
  readShit ();
  return 0;
}
