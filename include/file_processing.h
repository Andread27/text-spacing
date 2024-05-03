#include <stdbool.h>

/**
 * Struttura di dati per tenere traccia dello stato corrente durante l'elaborazione del file.
 */
typedef struct {
    int current_row;       // Indica il numero della riga corrente della pagina
    int array_row;         // Indica il numero della riga corrente di 'page'
    int max_row;           // Indica il numero dell'ultima riga di 'page'
    int current_column;    // Indica il numero della colonna corrente
    bool end_file;         // Indica se si è raggiunta la fine del file
    int end_paragraph;     // Indica se si è raggiunta la fine del paragrafo
    int nro_paragraphs;    // Indica il numero dei paragrafi
    int current_page;      // Indica il numero della pagina corrente
} structure_t;

/**
 * Crea una nuova istanza della struttura di dati.
 * @return Un puntatore alla nuova struttura creata.
 */
structure_t *newSTR() {
    structure_t *structure = malloc(sizeof(structure_t));
    structure->current_row = 0;
    structure->array_row = 0;
    structure->max_row = 0;
    structure->current_column = 1;
    structure->end_file = false;
    structure->end_paragraph = 0;
    structure->nro_paragraphs = 0;
    structure->current_page = 1;
    return structure;
}
