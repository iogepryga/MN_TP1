/*
  polyf_t   : structure polynome
  p_polyf_t : pointeur sur un polynome
*/

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

typedef struct {
  int nbMonome ;
  float *coeff;
  int *degre;
} polyf_creux_t, *p_polyf_creux_t;

p_polyf_creux_t creer_polynome (int degre) ;

void init_polynome (p_polyf_creux_t p, float x) ;

void detruire_polynome (p_polyf_creux_t p) ;

p_polyf_creux_t lire_polynome_float (char *nom_fichier) ;

void ecrire_polynome_float (p_polyf_creux_t p) ;

int egalite_polynome (p_polyf_creux_t p1, p_polyf_creux_t p2) ;

p_polyf_creux_t addition_polynome (p_polyf_creux_t p1, p_polyf_creux_t p2) ;

p_polyf_creux_t multiplication_polynome_scalaire (p_polyf_creux_t p, float alpha) ;

float eval_polynome (p_polyf_creux_t p, float x) ;

p_polyf_creux_t multiplication_polynomes (p_polyf_creux_t p1, p_polyf_creux_t p2) ;

p_polyf_creux_t puissance_polynome (p_polyf_creux_t p, int n) ;

p_polyf_creux_t composition_polynome (p_polyf_creux_t p, p_polyf_creux_t q) ;





float puiss_float(float x, int deg ) ;

int contient_int(int nb, int* tab, int len);
