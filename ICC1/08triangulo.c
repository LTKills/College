#include <stdio.h>
int
main ()
{
  int a, b, c;
  scanf ("%d %d %d", &a, &b, &c);
  if ((a * a) == (b * b) + (c * c))
    {
      printf ("SIM\n");
    }
  else if ((b * b) == (a * a) + (c * c))
    {
      printf ("SIM\n");
    }
  else if ((c * c) == (a * a) + (b * b))
    {
      printf ("SIM\n");
    }
  else
    {
      printf ("NAO\n");
    }
}
