#include <stdio.h>

#include "poly_creux.h"


int main(int argc, char *argv[]) {
	p_polyf_creux_t p1 = lire_polynome_float("p1"),
					p2 = lire_polynome_float("p2");

	printf("p1 = ");
	ecrire_polynome_float(p1);
	printf("p2 = ");
	ecrire_polynome_float(p2);



	printf("\n");



	printf("p1(1) = %f\n", eval_polynome(p1, -2));
	printf("p2(0) = %f\n", eval_polynome(p2, -1));



	printf("\n");



	p_polyf_creux_t p3 = creer_polynome(4);
	init_polynome(p3, 0.0);
	p3->coeff[1] = -3.0;
	p3->coeff[2] = 1.0;

	printf("p3 = ");
	ecrire_polynome_float(p3);

	reduire_polynome(p3);

	printf("p3 = ");
	ecrire_polynome_float(p3);



	printf("\n");



	p_polyf_creux_t p4 = addition_polynome(p1, p2);
	printf("p1 + p2 = ");
	ecrire_polynome_float(p4);



	printf("\n");



	p_polyf_creux_t p5 = multiplication_polynomes(p1, p2);
	printf("p1 * p2 = ");
	ecrire_polynome_float(p5);



	printf("\n");



	p_polyf_creux_t p6 = puissance_polynome(p1, 3);
	printf("p1 ^ 3 = ");
	ecrire_polynome_float(p6);



	printf("\n");



	detruire_polynome(p1);
	detruire_polynome(p2);
	detruire_polynome(p3);
	detruire_polynome(p4);
	detruire_polynome(p5);
	detruire_polynome(p6);


	return 0;
}