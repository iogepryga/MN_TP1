#include <stdio.h>
#include <stdlib.h>

#include "poly.h"


int main (int argc, char **argv)
{
  p_polyf_t p1, p2 ;
  
  if (argc != 3)
    {
      fprintf (stderr, "deux paramètres (polynomes,fichiers) sont à passer \n") ;
      exit (-1) ;
    }
      
  p1 = lire_polynome_float (argv[1]) ;
  p2 = lire_polynome_float (argv[2]) ;

  ecrire_polynome_float (p1) ;
  ecrire_polynome_float (p2) ;

  /*
    ajouter du code pour tester les fonctions
    sur les polynomes
  */

  float r = puiss_float(2.0,2);
  printf("res_puiss = %f\n", r);

  r = eval_polynome(p1,1);
  printf("%s(1) = %f\n",argv[1], r);

  p_polyf_t p = multiplication_polynome_scalaire(p1,2.0);
  printf("\n2* %s = ",argv[1]);
  ecrire_polynome_float (p);
  detruire_polynome(p);

  p = multiplication_polynomes(p1,p2);
  printf("\n%s * %s = ",argv[1],argv[2]);
  ecrire_polynome_float (p) ;
  detruire_polynome(p);

  p = puissance_polynome(p1,2);
  printf("\n%s^2 = ",argv[1]);
  ecrire_polynome_float (p) ;
  detruire_polynome(p);

  p = composition_polynome(p1,p2);
  printf("\n%s o %s = ",argv[1],argv[2]);
  ecrire_polynome_float (p) ;
  detruire_polynome(p);

  printf("\n");
}
