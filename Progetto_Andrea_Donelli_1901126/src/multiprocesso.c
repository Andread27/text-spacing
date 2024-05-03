#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

#include <sys/wait.h>
#include <unistd.h>

#include "file_processing.h"
#include "input_processing.h"
#include "string_utilities.h"

#define ROW_SIZE 1800
#define LEN_TEXT 2048
#define LEN_WORD 40
#define NR_WORD 15
#define NR_PAGE 500
#define NR_PERCENTAGE 8

/**
 * 
 * Progetto: Homework  
 *
 * Autore: Andrea Donelli 1901126
 *
 * Corso: Sistemi Operativi II 2022-23
 *
 * Docente: Paolo Ziliani
 *
 * Versione: A singolo processo
 *
*/


// struttura contenente i parametri di input
input_t *in;

// struttura contenente lo stato corrente del programma
structure_t *str;

/**
 * Scrive una riga nel file di output.
 * 
 * @param file il file di output
 * @param row la riga da scrivere
 * @param end_text flag che indica se la riga è l'ultima del testo
 */
void process_writing(FILE *file, char *row, bool end_text) {
    if (row != NULL) {
        if (end_text){
            fprintf(file, "%s", row);
        }
        else {
            fprintf(file, "%s\n", row);
        }
    }    
}

/**
 * Stampa il contenuto dell'array `page` nel file di output.
 *
 * @param outputFile Il file di output.
 * @param page L'array di righe che compongono la pagina.
 */
void printFile(FILE *outputFile,char **page) {
    int row = 0;
    int n_page = 1;
    
    for (int p = 0; p < str-> max_row; p++) {
        if (row == in->n_row ) {
            n_page++;
            row = -1;
        }

        if (p == str-> max_row -1) {
            process_writing(outputFile, page[p], true); 
            
        } else {
            process_writing(outputFile, page[p], false);
        }
        row++;
    }
}


/**
 * Aggiunge una nuova pagina all'array `page`.
 *
 * @param page L'array di righe che compongono la pagina.
 */
void new_page(char **page) {
    char *percentage = (char *)malloc(NR_PERCENTAGE * sizeof(char));;
    strcpy(percentage, "\n ");
    char p[2];
    p[0] = '%';
    p[1] = '\0';
    for (int i = 0; i < 3; i++) {
        strcat(percentage, p);
    }
    strcat(percentage, " \n");
    strcpy(page[str->array_row], percentage);
    str->array_row++;
    str->max_row++;
    str->current_page++;
}


/**
 * Processa una pagina, scrivendo le righe nel file di output.
 *
 * @param page L'array di righe che compongono la pagina.
 * @param line La riga corrente da processare.
 */
void process_page(char **page, char *line) { 

    if (str->current_row == in->n_row) {
        if (str->current_column == in->n_col) {
        	// una volta raggiunte le righe e colonne max di una pagina
        	// inizializza una nuova pagina di 'page'
                new_page(page);
                str->current_column = 1;
        }
        else{
            str->current_column++;
            str-> max_row = str->array_row;
            str->array_row -= str->current_row;
        }
        str->current_row = 0;
        
    }
    if (str->current_row < in->n_row) {
        if (str->current_column == 1) {
            strcpy(page[str->array_row], line);
            str-> max_row++;
        }
    
        else {
            char *sp = repeatSpace(in->col_dist);
            strcat(page[str->array_row], sp);
            strcat(page[str->array_row], line);
        }
        str->current_row++;
        str->array_row++;
        
        
    }
}

/**
 * * Processa l'allineamento delle parole dell'ultima riga di ogni paragrafo
 *
 * @param wordList L'array di parole salvate.
 * @param line La riga da modificare.
 * @param currentWord Il numero di parole salvate.
 */
void align_end_paragraph(char **wordList, char *line, int currentWord) {
    for (int c = 0; c < currentWord; c++) {
        if (c == 0) {
            strcpy(line, wordList[c]);
        }
        else{
            strcat(line, " ");
            strcat(line, wordList[c]);
        }
    }
    if ( lenString(line) < in -> col_size -1) {
        int sp = in -> col_size - lenString(line) -1 ;
        char *space = repeatSpace(sp);
        strcat(line, space);       
    }
    
}
/**
 * Inizializza la modifica dell'allineamento delle parole dell'ultima riga di ogni paragrafo
 *
 * @param line La riga da modificare
 */
void initialize_align_end_paragraph(char *line) {
    char *word = (char *)malloc(LEN_WORD * sizeof(char));
    char **wordList = (char **)malloc(NR_WORD * sizeof(char *));
    for (int i = 0; i < NR_WORD; i++) {
        wordList[i] = (char *)malloc(in->col_size * sizeof(char));
    }
    int position_word;
    
    int current_word = 0;

    while (sscanf(line, "%s%n", word, &position_word) == 1) {
        line += position_word;
        strcpy(wordList[current_word], word);
        current_word++;
    }
    align_end_paragraph(wordList, line, current_word);

}

/**
 * Modifica dell'allineamento delle parole dell'ultima riga di ogni paragrafo
 *
 * @param row La riga da allineare.
 */
void modify_end_paragraph(char *row) {
    char *line1 = (char *)malloc(strlen(row) * sizeof(char));
    char *line2 = (char *)malloc(strlen(row) * sizeof(char));
    if (str ->current_column != 1) {
        // corrisponde al numero di caratteri presenti nella riga da non modificare 
        int position_column = (in -> col_size - 1 + in -> col_dist) * (str -> current_column - 1);
        
        
        for (int i = 0; i < strlen(row) +1; i++) {
            
            if ( i < position_column) {
                line1[i] = row[i];
            }
            else if ( i == position_column) {
                line1[i] = '\0';
                line2[i - position_column] = row[i];
            }
            else {
                line2[i - position_column] = row[i];
            }
            if (control(row[i])) {
                position_column++;
            }

        }
        line2[strlen(row)] = '\0';

        initialize_align_end_paragraph(line2);
        strcat(line1,line2);
        strcpy(row, line1);
        
    }
    else {
        initialize_align_end_paragraph(row);
    }
    free(line1);
}

/**
 * Processa una riga per l'allineamento delle parole.
 *
 * @param wordList L'array di parole salvate.
 * @param line La riga da allineare.
 * @param currentWord Il numero di parole salvate.
 * @param totalLength La lunghezza totale delle parole salvate.
 */
void align_words(char **wordList, char *line, int currentWord, int totalLength) {
    for (int c = 0; c < currentWord; c++) {
        if (c == 0) {
            strcpy(line, wordList[c]);
        }
        else {
            // Aggiunge spazi per allineare correttamente il testo
            int sp = ( in -> col_size - totalLength - 1) / (currentWord - c);
            totalLength += sp;
            char *space = repeatSpace(sp);
            strcat(line, space);
            strcat(line, wordList[c]);
        }
    }
    if (lenString(line) < in -> col_size -1) {
        int sp = in -> col_size - lenString(line) -1 ;
        char *space = repeatSpace(sp);
        strcat(line, space);       
    }
}

/**
 * Processa la fine di un paragrafo, aggiungendo una riga vuota.
 *
 * @param page L'array di righe che compongono la pagina.
 */
void end_paragraph(char **page){
    int sp = in->col_size -1;
    char *space = repeatSpace(sp);
    process_page(page, space);
}

/**
 * Processa una riga di testo, suddividendola in parole e allineandole.
 *
 * @param paragraph La riga di testo da processare.
 * @param page L'array di righe che compongono la pagina.
 */
void process_line(char *paragraph, char **page) {
    char *line = (char *)malloc((in->col_size + 1) * sizeof(char));
    char *word = (char *)malloc(LEN_WORD * sizeof(char));
    char **wordList = (char **)malloc(NR_WORD * sizeof(char *));
    for (int i = 0; i < NR_WORD; i++) {
        wordList[i] = (char *)malloc(in->col_size * sizeof(char));
    }
    
    int position_word;
    int size = 0;
    int current_word = 0;
    
    while (sscanf(paragraph, "%s%n", word, &position_word) == 1) {
        paragraph += position_word;
        if (lenString(word) >= in->col_size) {
            perror("MAX SIZE ERROR:");
            printf("la parola '%s' (di %d caratteri) supera il numero massimo di caratteri presenti in una colonna (%d)\n", word, lenString(word), in->col_size - 1);
            exit(1);
        }
        size += lenString(word);
        if (size + current_word < in->col_size) {
            strcpy(wordList[current_word], word);
            current_word++;
        }
        else {
            // se size supera la grandezza massima della colonna
            size -= lenString(word);
            align_words(wordList, line, current_word, size);
            process_page(page, line);

            for (int i = 0; i < current_word; i++) {
                resetString(wordList[i], strlen(wordList[i]));               
            }
            strcpy(wordList[0], word);
            size = lenString(word);
            current_word = 1;
            resetString(line, strlen(line));
        }
    }
    
    resetString(line, strlen(line));
    // Se ci sono ancora parole non inserite nella 'page'
    if (size != 0) {
        align_end_paragraph(wordList, line, current_word);
        process_page(page, line);
    } else {
        modify_end_paragraph(page[str-> array_row -1]);
        
    }

    free(wordList);
    free(line);
    free(word);

}


/**
 * Legge il testo dal file di input e restituisce un array di righe.
 *
 * @param inputFile Il file di input.
 * @return L'array di righe del testo.
 */
char** read_text(FILE *input_file) {
    char *paragraph = (char *)malloc(LEN_TEXT * sizeof(char));
    char **page = (char **)malloc(NR_PAGE * sizeof(char *));
    for (int i = 0; i < NR_PAGE; i++) {
        page[i] = (char *)malloc((LEN_TEXT*10) * sizeof(char));
    }
    
    while (fgets(paragraph, LEN_TEXT, input_file) != NULL) {
        paragraph[strcspn(paragraph, "\r\n")] = '\0';
        char *token = strtok(paragraph, "\n");
        if (token == NULL){
            str ->end_paragraph--;
            if (str ->end_paragraph == 0) {
                str -> nro_paragraphs++;
            }
        }
        
        while (token != NULL) {
            if (str ->end_paragraph == 1) {
                strcat(page[str -> nro_paragraphs], "\n");
                strcat(page[str -> nro_paragraphs], token);
            }
            else {
                strcpy(page[str -> nro_paragraphs], token);
            }
            
            token = strtok(NULL, "\n");
            str ->end_paragraph = 1;
        }
    }
    return page;

}


/**
 * Processa il testo del file di input, suddividendolo in paragrafi e allineando le parole.
 *
 * Crea tre processi: Lettura del file di input; Allineamento delle colonne; Scrittura su file di output.
 * I tre processi si scambiano le informazioni più importanti tramite l'utilizzo di pipe.
 * 
 *
 * @param inputFile Il file di input.
 * @param outputFile Il file di output.
 */
void process_text(FILE *inputFile, FILE *outputFile) {

    int pipe1[2];
    if (pipe(pipe1) == -1) {
        perror("Errore nella creazione della pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();

    if (pid1 == -1) {
        perror("Errore nella apertura della fork");
        exit(EXIT_FAILURE);
    }else if (pid1 == 0) {
        close(pipe1[1]);
        int pipe2[2];
        if (pipe(pipe2) == -1) {
            perror("Errore nella creazione della pipe");
            exit(EXIT_FAILURE);
        }
        pid_t pid2 = fork();
        if (pid2 == -1) {
            perror("Errore nella apertura della fork");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            //Processo 3: SCRITTURA SU OUTPUT
            close(pipe2[1]);
            read(pipe2[0], str, sizeof(structure_t));
            char **buffer2 = (char **)malloc((str->max_row) * sizeof(char *));
	    for (int i = 0; i < str->max_row; i++) {
	        buffer2[i] = (char *)malloc(ROW_SIZE *2 * sizeof(char));
	        read(pipe2[0], buffer2[i], ROW_SIZE *2 * sizeof(char));
	   
	        
	    }

            printFile(outputFile,buffer2);
            close(pipe2[0]);
            free(buffer2);
            exit(EXIT_SUCCESS);
        }
        else {
            //Processo 2: ALLINEAMENTO COLONNE
            close(pipe1[1]);
            read(pipe1[0], str, sizeof(structure_t));
            
            char **buffer = (char **)malloc((str->nro_paragraphs) * sizeof(char *));
	    for (int i = 0; i <= str->nro_paragraphs; i++) {
		 buffer[i] = (char *)malloc(LEN_TEXT * sizeof(char));
		 read(pipe1[0], buffer[i], LEN_TEXT * sizeof(char));
	    }


            char **page = (char **)malloc((ROW_SIZE *2) * sizeof(char *));
            for (int i = 0; i < (ROW_SIZE * 2); i++) {
                page[i] = (char *)malloc(ROW_SIZE * sizeof(char));
            }
            for (int i = 0; i <= str -> nro_paragraphs; i++) {
                process_line(buffer[i], page);
                if (i != str -> nro_paragraphs) {
                    end_paragraph(page);
                }
            }
	    
            write(pipe2[1], str, sizeof(structure_t));
	    for (int i = 0; i < str->max_row; i++) {
	    	
		write(pipe2[1], page[i], ROW_SIZE * 2 * sizeof(char));
	    }

            close(pipe2[1]);
            close(pipe1[0]);
            wait(NULL);
            free(page);
            free(buffer);
            exit(EXIT_SUCCESS);
        }
        
    } else {
        //Processo 1: LETTURA TESTO
        close(pipe1[0]);
        
        char **text = read_text(inputFile);
        write(pipe1[1], str, sizeof(structure_t));

        for (int i = 0; i <= str -> nro_paragraphs; i++) {
            
            write(pipe1[1], text[i], LEN_TEXT * sizeof(char));
        }
        
        close(pipe1[1]);
        wait(NULL);
        free(text);
        exit(EXIT_SUCCESS);
    }

}


/**
 * Processa i parametri di input, apre il file di input e genera il file di output.
 */
void process_file() {
    FILE *fin;
    FILE *fout;
    str =  newSTR();
    fin = fopen(in -> file, "r");
    if (fin == NULL) {
        perror("ERRORE: Impossibile aprire il file di input");
        exit(EXIT_FAILURE);
    }

    fout = fopen("output_multiprocesso.txt", "w");
    if (fout == NULL) {
        perror("ERRORE: Impossibile creare il file di output");
        exit(EXIT_FAILURE);
    }

    process_text(fin, fout);

    fclose(fin);
    fclose(fout);
}

/**
 * Funzione principale del programma.
 *
 * @param argc Il numero di argomenti della linea di comando.
 * @param argv L'array di stringhe degli argomenti della linea di comando.
 * @return Il codice di uscita del programma.
 */
int main(int argc, char **argv) {
    
    if (argc == 6) {
        in = newIN(argv[1], argv[2], argv[3], argv[4], argv[5]);
    }
    else {
        perror("INPUT ERROR:");
        printf("Errore nei parametri in input!\n");
        exit(1);
    }
    
    process_file();
    free(in);
    free(str);
    return 0;
}
