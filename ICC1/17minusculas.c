#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int
main ()
{
  int i;
  char string[25555];
  scanf ("%s", string);

  for (i = 0; i < strlen (string); i++)
    {
      string[i] = string[i] + 32;
    }

  printf ("%s\n", string);
  return 0;
}
