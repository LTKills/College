#include<stdio.h>
#include<stdlib.h>
int ano;
int
bissexto ()
{
  if (ano % 4 != 0)
    {
      printf ("NAO\n");
      return 0;
    }
  else
    {
      if (ano % 100 != 0)
	{
	  printf ("SIM\n");
	  return 0;
	}
      else
	{
	  if (ano % 400 != 0)
	    {
	      printf ("NAO\n");
	      return 0;
	    }
	  else
	    {
	      printf ("SIM\n");
	      return 0;
	    }
	}
    }
  return 0;
}


int
main ()
{
  scanf ("%d", &ano);

  bissexto ();
  return 0;
}
