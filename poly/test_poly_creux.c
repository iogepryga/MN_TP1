#include <stdio.h>
#include <stdlib.h>

#include "poly_creux.h"

#include <x86intrin.h>

int main (int argc, char **argv)
{
  if (argc != 3)
  {
      fprintf (stderr, "deux paramètres (polynomes,fichiers) sont à passer \n") ;
      exit (-1) ;
  }
      
  p_polyf_creux_t p1 = lire_polynome_float (argv[1]) ;
  p_polyf_creux_t p2 = lire_polynome_float (argv[2]) ;
  p_polyf_creux_t p3;

  printf ("%s = ",argv [1]) ;
  ecrire_polynome_float (p1) ;

  printf ("%s = ",argv [2]) ;
  ecrire_polynome_float (p2) ;

  float r = puiss_float(2.0,2);
  printf("res_puiss = %f\n", r);

  r = eval_polynome(p1,1);
  printf("%s(1) = %f\n",argv[1], r);
  r = eval_polynome(p2,1);
  printf("%s(1) = %f\n",argv[2], r);

  p3 = multiplication_polynome_scalaire(p1,2.0);
  printf("\n2 * %s = ",argv[1]);
  ecrire_polynome_float (p3) ;
  detruire_polynome (p3) ;

  p3 = addition_polynome(p1,p2);
  printf("\n%s + %s = ",argv[1], argv[2]);
  ecrire_polynome_float (p3) ;
  detruire_polynome (p3) ;

  p3 = multiplication_polynomes(p1,p2);
  printf("\n%s * %s = ",argv[1],argv[2]);
  ecrire_polynome_float (p3) ;
  detruire_polynome (p3) ;

  p3 = puissance_polynome(p1,2);
  printf("\n%s^2 = ",argv[1]);
  ecrire_polynome_float (p3) ;
  detruire_polynome (p3) ;

  p3 = composition_polynome(p1,p2);
  printf("\n%s o %s = ",argv[1],argv[2]);
  ecrire_polynome_float (p3) ;
  printf("\n");
  detruire_polynome (p3) ;

  detruire_polynome (p1) ;
  detruire_polynome (p2) ;
}
