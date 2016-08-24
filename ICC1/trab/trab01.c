#include <stdlib.h>		// Funcao malloc
#include <stdio.h>		// Funcoes printf e scanf
#include <string.h>		// Funcao strlen


/*  Funcao que le a entrada padrao (stdin = teclado) e guarda esses
    valores na string m
*/
void
readLine (char *msg)
{
  char keyboard;
  int i = 0;
  keyboard = fgetc (stdin);
  do
    {
      msg[i++] = keyboard;
      keyboard = fgetc (stdin);
    }
  while (keyboard != 10);
  msg[i] = '\0';
}

/*
    Funcao que, a partir dos parametros key e m, criptografa a mensagem contida
    em m de acordo com a tecnologia de cesar
*/
char *
cesar (char *m, int key)
{
  int i;
  for (i = 0; i < strlen (m); i++)
    {
      if (m[i] > 90 | m[i] < 65)
	{
	  m[i] += 0;
	}
      else
	{
	  m[i] += key;
	}
      if (m[i] > 90)
	{
	  m[i] -= 26;
	}
    }
  return m;
}


/*
    Funcao que, a partir dos parametros c, m e s, criptografa a mensagem contida
    em m de acordo com a tecnologia de vigenere
*/
char *
vigenere (char *m, char *c, int s)
{
  int i, j = 0;
  for (i = 0; i < strlen (m); i++)
    {
      if (m[i] > 90 | m[i] < 65)
	{
	  m[i] += 0;
	}
      else
	{
	  if (j >= s)
	    {
	      m[i] += (int) (c[j % s] - 65);
	    }
	  else
	    {
	      m[i] += (int) (c[j] - 65);
	    }
	  j++;
	}
      if (m[i] > 90)
	{			// volta ao inicio do alfabeto
	  m[i] -= 26;
	}
    }
  return m;
}


int
main (void)
{
  int n;			// Quantidade de caracteres na mensagem
  int op;			// Operacao a ser feita (1 = cesar, 2 = vigenere)
  char *m = NULL;		// Mensagem

  scanf ("%d%*c", &n);		// Le a quantidade de caracteres
  m = (char *) malloc (sizeof (char) * (n + 1));	// Aloca para a mensagem
  readLine (m);			// Le a mensagem

  scanf ("%d", &op);		// Le a operacao a ser feita

  if (op == 1)
    {				//          Se Cesar

      int key;			// Chave para Cesar
      scanf ("%d", &key);	// Le a chave de Cesar

      cesar (m, key);		// Criptografa Cesar
      printf ("%s\n", m);	// Imprime Cesar

    }
  else
    {				//                Se Vigenere

      int s;			// Quantidade de caracteres na chave
      char *c = NULL;		// Chave de Vigenere

      scanf ("%d%*c", &s);	// Le a quantidade de caracteres na chave
      c = (char *) malloc (sizeof (char) * (s + 1));	// Aloca para a chave Vigenere
      readLine (c);		// Le a chave de Vigenere

      vigenere (m, c, s);	// Criptografa Vigenere
      printf ("%s\n", m);	// Imprime Vigenere

      free (c);
    }

  free (m);
  return 0;
}
