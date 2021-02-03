#include <stdio.h>
#include <stdlib.h>

#include "poly_creux.h"

#include <x86intrin.h>

p_polyf_creux_t creer_polynome (int degre) {
	p_polyf_creux_t p;
	p = (p_polyf_creux_t) malloc(sizeof(polyf_creux_t));
	
	p->taille = 1;

	p->degre = (int*) malloc(sizeof(int));
	p->degre[0] = degre;

	p->coeff = (float*) malloc(sizeof(float));
	p->coeff[0] = 0.0;

	return p;
}

void detruire_polynome (p_polyf_creux_t p) {
	free(p->degre);
	free(p->coeff);
	free(p);

	return;
}

void init_polynome (p_polyf_creux_t p, float x) {
	register unsigned int i;

	if (p->taille != p->degre[p->taille - 1] + 1) {
		p->taille = p->degre[p->taille - 1] + 1;
		free(p->degre);
		free(p->coeff);
		p->degre = (int*) malloc(p->taille * sizeof(int));
		p->coeff = (float*) malloc(p->taille * sizeof(float));
	}

	for (i = 0; i <= p->taille; i++) {
		p->degre[i] = i;
		p->coeff[i] = x;
	}

	return;
}

p_polyf_creux_t copier_polynome (p_polyf_creux_t p) {
	p_polyf_creux_t res = (p_polyf_creux_t) malloc(sizeof(polyf_creux_t));

	res->taille = p->taille;

	res->degre = (int*) malloc(p->taille * sizeof(int));
	res->coeff = (float*) malloc(p->taille * sizeof(float));
	
	for (int i = 0; i < p->taille; i++) {
		res->degre[i] = p->degre[i];
		res->coeff[i] = p->coeff[i];
	}

	return res;
}


void reduire_polynome(p_polyf_creux_t p) {
	int taille = 0;

	for (int i = 0; i < p->taille; i++) {
		if (p->coeff[i] != 0.0)
			taille++;
	}

	if (taille == p->degre[p->taille - 1] + 1)
		return;

	int *degre = (int*) malloc(taille * sizeof(int));
	float *coeff = (float*) malloc(taille * sizeof(float));

	int difference = 0;
	for (int i = 0; i < p->taille; i++) {
		if (p->coeff[i] == 0.0)
			difference++;
		else {
			degre[i - difference] = i;
			coeff[i - difference] = p->coeff[i];
		}
	}

	free(p->degre);
	free(p->coeff); // Invalid pointer

	p->taille = taille;
	p->degre = degre;
	p->coeff = coeff;
}


p_polyf_creux_t lire_polynome_float (char *nom_fichier) {
	FILE *f;
	p_polyf_creux_t p;

	int degre;
	int cr;

	f = fopen (nom_fichier, "r");

	if (f == NULL) {
		fprintf (stderr, "erreur ouverture %s \n", nom_fichier);
		exit (-1);
	}

	cr = fscanf (f, "%d", &degre);
	if (cr != 1) {
		fprintf (stderr, "erreur lecture du degre\n");
		exit (-1);
	}

	float *coeff = (float*) malloc((degre + 1) * sizeof(float));
	int taille = 0;
	
	for (int i = 0; i <= degre; i++) {
		cr = fscanf (f, "%f", &(coeff[i]));

		if (cr != 1) {
			fprintf (stderr, "erreur lecture coefficient %d\n", i);
			exit (-1);
		}

		if (coeff[i] != 0.0)
			taille++;

	}

	fclose (f);


	p = (p_polyf_creux_t) malloc(sizeof (polyf_creux_t));

	p->taille = taille;
	p->degre = (int*) malloc(taille * sizeof(int));
	p->coeff = (float*) malloc(taille * sizeof(float));

	int difference = 0;
	for (int i = 0; i <= degre; i++) {
		if (coeff[i] == 0.0)
			difference++;
		else {
			p->degre[i - difference] = i;
			p->coeff[i - difference] = coeff[i];
		}
	}

	free(coeff);

	return p;
}

void ecrire_polynome_float (p_polyf_creux_t p) {
	for (int i = 0; i < p->taille; i++) {
		if (p->degre[i] == 0)
			printf("%f", p->coeff[i]);
		else if (p->degre[i] == 1)
			printf(
				"%s%f*X",
				i == 0 ? "" : " + ",
				p->coeff[i]
			);
		else
			printf(
				"%s%f*X^%d",
				i == 0 ? "" : " + ",
				p->coeff[i],
				p->degre[i]
			);
	}

	printf("\n");

	return;
}


int egalite_polynome (p_polyf_creux_t p1, p_polyf_creux_t p2) {
	if (p1->taille != p2->taille)
		return 0;

	for (int i = 0; i < p1->taille; i++) {
		if (p1->degre[i] != p2->degre[i] || p1->coeff[i] != p2->coeff[i])
			return 0;
	}
	
	return 1;
}


p_polyf_creux_t addition_polynome (p_polyf_creux_t p1, p_polyf_creux_t p2) {
	p_polyf_creux_t res = creer_polynome(max(p1->degre[p1->taille - 1], p2->degre[p2->taille - 1]) + 1);
	init_polynome(res, 0.0);

	for (int i = 0; i < res->taille; i++) {
		if (i < p1->taille)
			res->coeff[p1->degre[i]] += p1->coeff[i];
		if (i < p2->taille)
			res->coeff[p2->degre[i]] += p2->coeff[i];
	}

	reduire_polynome(res);

	return res;
}


p_polyf_creux_t multiplication_polynome_scalaire (p_polyf_creux_t p, float alpha) {
	p_polyf_creux_t p_result = copier_polynome(p);

	for (int i = 0; i < p->taille; i++)
		p_result->coeff[i] = p->coeff[i] * alpha;

	return p_result;
}


float puiss_float (float x, int deg) {
	float result = 1.0;

	for (int i = 0; i < deg; i++)
		result *= x;

	return result;
}


float eval_polynome (p_polyf_creux_t p, float x) {
	float result = 0.0;

	for (int i = 0; i < p->taille; i++) {
		result += p->coeff[i] * puiss_float(x, p->degre[i]);
	}

	return result;
}


p_polyf_creux_t multiplication_polynomes (p_polyf_creux_t p1, p_polyf_creux_t p2) {
	p_polyf_creux_t p_result = creer_polynome(p1->degre[p1->taille - 1] + p2->degre[p2->taille - 1] + 1);
	init_polynome(p_result, 0.0);
	
	for (int i = 0; i < p1->taille; i++) {
		int degre_p1 = p1->degre[i];
		for (int j = 0; j < p2->taille; j++)
			p_result->coeff[degre_p1 + p2->degre[j]] += p1->coeff[i] * p2->coeff[j];
	}

	reduire_polynome(p_result);
	// p1 * p2
	return p_result;
}


p_polyf_creux_t puissance_polynome (p_polyf_creux_t p, int n) {
	p_polyf_creux_t p_result = creer_polynome(0);
	p_result->coeff[0] = 1.0;
	
    for (int i = 0; i < n; i++) {
		p_polyf_creux_t tmp = p_result;
		p_result = multiplication_polynomes(p_result, p);
		detruire_polynome(tmp);
	}
	// p^n
	return p_result;
}

/*

p_polyf_creux_t composition_polynome (p_polyf_creux_t p, p_polyf_creux_t q) {
    p_polyf_creux_t p_result = creer_polynome(0);
    p_result->coeff[0] = p->coeff[0];

    for (int i = 1; i <= p->degre; i++) {
        p_polyf_creux_t tmp = p_result;
        p_polyf_creux_t tmp2 = puissance_polynome(q, i);
        p_polyf_creux_t tmp3 = multiplication_polynome_scalaire(tmp2, p->coeff[i]);
        p_result = addition_polynome(p_result, tmp3);
        detruire_polynome(tmp);
        detruire_polynome(tmp2);
        detruire_polynome(tmp3);
    }
    
    // p O q
    return p_result;
}



*/