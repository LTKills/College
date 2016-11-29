#include <stdlib.h>
#include <stdio.h>

int **hashAlloc (int n, int k, int *sizes) {
  int i, j, atual;
  int **hash = NULL;

  hash = (int **) malloc (sizeof (int *) * k);	// aloca para hash

  for (i = 0; i < n; i++)
    {				// lendo n numeros e gudardando-os
      scanf ("%d", &atual);
      j = atual % k;
      hash[j] = realloc (hash[j], sizeof (int) * (sizes[j] + 1));	// realoca o tamanho de uma linha
      sizes[j]++;
      hash[j][sizes[j] - 1] = atual;
    }

  return hash;
}



int main (int argc, char *argv[]) {
  int **hash = NULL;
  int *sizes = NULL;
  int i, j, k, n;		// k -> chave   n -> quantidade de elementos
  scanf ("%d %d", &k, &n);
  sizes = calloc (k, sizeof (int));


  hash = hashAlloc (n, k, sizes);	// criar, alocar e guardar em hash table


  for (i = 0; i < k; i++)
    {				// imprimindo hash
      printf ("%d: ", i);
      for (j = 0; j < sizes[i]; j++)
	{
	  if (sizes[i] != 0)
	    printf ("%d ", hash[i][j]);
	}
      printf ("\n");
    }


  for (i = 0; i < k; i++)	// liberando tutô
    free (hash[i]);

  free (hash);
  free (sizes);
  return 0;
}
