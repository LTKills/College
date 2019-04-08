#include <stdlib.h>
#include <stdio.h>

int *
readVec (int n, int *vec)
{
  int i = 0;
  do
    {
      scanf ("%d", &vec[i++]);
    }
  while (i < n);

  return vec;
}

int *
invert (int n, int *vec)
{
  int i, aux, j = n - 1;
  for (i = 0; i < (n / 2); i++)
    {
      aux = vec[i];
      vec[i] = vec[j - i];
      vec[j - i] = aux;
    }
  return vec;
}

void
print (int n, int *vec)
{
  int i = 0, j = i + 1;

  for (i = 0; i < n; i++)
    {
      printf ("%d\n", vec[i]);
    }
}


int
main (int argc, char *argv[])
{
  int *vec;
  int n;

  scanf ("%d", &n);
  vec = malloc (sizeof (int) * n);

  vec = invert (n, readVec (n, vec));
  print (n, vec);

  return 0;
}
