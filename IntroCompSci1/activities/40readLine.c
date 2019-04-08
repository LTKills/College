#include <stdio.h>
#include <stdlib.h>


int
main (int argc, char *argv)
{
  char c, *line = NULL;
  int j, i = 0;

  do
    {
      c = fgetc (stdin);
      line = realloc (line, sizeof (char) * (i + 1));
      line[i++] = c;
    }
  while (c != 10 && !feof (stdin));
  line = realloc (line, sizeof (char) * (i + 1));
  line[i - 1] = '\0';



  for (j = 0; line[j] != '\0'; j++)
    {
      printf ("%c\n", line[j]);
    }
	free(line);
  return 0;
}
