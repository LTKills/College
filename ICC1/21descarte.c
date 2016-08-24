#include <stdlib.h>
#include <stdio.h>

int
main (void)
{
  int i = 0, j = 1, k;
  float *vec;
  float aux, media;
  vec = malloc (sizeof (float) * 4);
  scanf ("%f %f %f %f", &vec[0], &vec[1], &vec[2], &vec[3]);

  for (k = 0; k < 3; k++)
    {
      j = 1;
      i = 0;
      while (i < 3)
	{
	  if (vec[j] < vec[i])
	    {
	      aux = vec[j];
	      vec[j] = vec[i];
	      vec[i] = aux;
	    }
	  i++;
	  j++;
	}
    }


  media = (vec[1] + vec[2] + vec[3]) / 3;


  printf ("%.4f\n", media);
  free (vec);
  return 0;
}
