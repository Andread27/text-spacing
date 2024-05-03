
/**
 * Controlla se il carattere ha 1 e 0 come bit più significativi
 *
 * @param c Il carattere da controllare.
 * @return true se il carattere ha 1 e 0 come bit più significativi, altrimenti false.
 */
bool control(char c);

/**
 * Restituisce la lunghezza effettiva di una stringa,
 * escludendo i caratteri speciali di UTF-8 (coloro che hanno 
 * 1 e 0 come bit più significativi)
 *
 * @param word La stringa di cui calcolare la lunghezza effettiva.
 * @return La lunghezza effettiva della stringa.
 */
int lenString(char *word);

/**
 * Restituisce una stringa contenente un numero specificato di spazi.
 *
 * @param n Il numero di spazi da generare.
 * @return La stringa contenente gli spazi.
 */
char *repeatSpace(int n);

/**
 * Reimposta il contenuto di una stringa a caratteri null ('\0').
 *
 * @param stringa La stringa da resettare.
 * @param len La lunghezza della stringa.
 */
void resetString(char *stringa, int len);

