#include <stdlib.h>
#include <stdio.h>

float *
readline (int n)
{
  int i;
  float *t;
  t = (float *) malloc (sizeof (float) * n);

  for (i = 0; i < n; i++)
    {
      scanf ("%f", &t[i]);
    }


  return t;
}



int
main ()
{
  int n, i;
  float sum = 0, media = 0;
  float *t = NULL;
  scanf ("%d", &n);
  t = readline (n);


  for (i = 0; i < n; i++)
    {
      sum += 1 / (t[i] + 1);
    }
  media = (n / sum) - 1;


  printf ("%.2f\n", media);
  return 0;
}
