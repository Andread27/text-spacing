#include <string.h>
#include "input_converte.h"


#define LEN_FN 50


/**
 * Struttura per il salvataggio dei dati di input.
 *
 * @param file Il nome del file di input.
 * @param n_col Il numero di colonne nella pagina.
 * @param n_row Il numero di righe nella pagina.
 * @param col_size La dimensione di ogni colonna.
 * @param col_dist La distanza tra le colonne.
 */
typedef struct {
    char file[LEN_FN];  // Nome del file di input
    int n_col;          // Numero di colonne nella pagina
    int n_row;          // Numero di righe nella pagina
    int col_size;       // Dimensione di ogni colonna
    int col_dist;       // Distanza tra le colonne
} input_t;

/**
 * Crea una nuova struttura input_t con i valori forniti.
 *
 * @param input_file Il nome del file di input.
 * @param c Il numero di colonne nella pagina.
 * @param r Il numero di righe nella pagina.
 * @param cs La dimensione di ogni colonna.
 * @param cd La distanza tra le colonne.
 * @return Un puntatore a una nuova struttura di input.
 */
input_t *newIN(char *input_file, char *c, char *r,  char *cs, char *cd) {
    input_t *pIN = (input_t *) malloc(sizeof(input_t));
    strncpy(pIN->file, input_file, LEN_FN);
    pIN->n_col = converte(c);
    pIN->n_row = converte(r);
    pIN->col_size = converte(cs) + 1;
    pIN->col_dist = converte(cd);
    return pIN;
}
