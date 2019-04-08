#include <stdio.h>
#include <math.h>
int
main ()
{
  float a, b, c, r1, r2, delta;
  scanf ("%f %f %f", &a, &b, &c);
  delta = ((b * b) - 4 * (a * c));

  if (delta < 0)
    {
      delta = -delta;
      r1 = -b / (2 * a);
      r2 = sqrt (delta) / (2 * a);
      printf ("COMPLEXAS\n");
      printf ("R %f\nI %f\n", r1, r2);
    }


  else if (delta == 0)
    {
      r1 = -b / 2 * a;
      printf ("DUPLA\n");
      printf ("RD %f\n", r1);
    }

  else
    {
      r1 = (sqrt (delta) - b) / 2 * a;
      r2 = (-b - sqrt (delta)) / 2 * a;
      printf ("REAIS\n");
      printf ("R1 %lf\nR2 %lf\n", r1, r2);
    }
  return 0;
}
