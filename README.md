# text-spacing

## Autore 
Andrea Donelli 

## Corso 
- Corso: Sistemi Operativi 2023/24.
- Professore: P.Z.

## Descrizione del progetto

Il progetto consiste in un programma che legge un file di input contenente un testo e lo formatta in modo da allineare le parole in colonne. 
Il programma è diviso in due versioni, una a singolo processo e una multi-processo. I file sorgenti principali che si occuperanno delle due versioni del programma sono `monoprocesso.c` e `multiprocesso.c`.

## File Inclusi

- In ./include:
1. `file_processing.h`: contiene le dichiarazioni delle funzioni per la gestione dei file.
2. `input_processing.h`: contiene le dichiarazioni delle funzioni per l'elaborazione dei parametri di input.
3. `input_converte.h`: contiene le dichiarazioni della funzione per la conversione di una stringa in un intero.
4. `string_utilities.h`:  contiene le dichiarazioni delle funzioni per la manipolazione delle stringhe.

- In ./src:
1. `monoprocesso.c`: Contiene la funzione principale `main()` che gestisce il flusso del programma nella versione a singolo processo. Legge il file di input, crea il testo incolonnato e scrive il testo nel file: `output_monoprocesso.txt`contentente il testo formattato secondo inputs.
2. `multiprocesso.c`: Contiene la funzione principale `main()` che gestisce il flusso del programma nella versione multi-processo. Il primo processo legge il file di input, il secondo processo crea il testo incolonnato e il terzo processo scrive il testo nel file: `output_multiprocesso.txt` contentente il testo formattato secondo inputs.
3. `input_converte.c`: contiene la funzione dichiarata in `input_converte.h`.
4. `string_utilities.c`: contiene le funzione dichiarate in `string_utilities.h`.

- In ./build:
I file oggetto generati in compilazione

## Makefile
Il Makefile è stato progettato per compilare i programmi "monoprocesso" e  "multiprocesso", semplificando il loro processo di compilazione ma mantenendo le dipendenze e le regole di compilazione corrette.

## Strutture dati

Il programma utilizza le seguenti strutture dati:

- `input_t`: Struttura che contiene i parametri di input del programma, come il file di input, il numero di righe per colonna, la dimensione delle colonne, ecc.
- `structure_t`: Struttura che rappresenta lo stato corrente del programma, come il numero di righe e colonne correnti, il numero massimo di righe per pagina, ecc.

## Funzionalità principali

Il programma offre le seguenti funzionalità principali:

- Lettura del testo da un file di input.
- Suddivisione del testo in paragrafi e allineamento delle parole in colonne.
- Generazione di un file di output contenente il testo formattato.

## Come compilare ed eseguire il programma

Per compilare ed eseguire il programma, esegui i seguenti passaggi:

1. Assicurati di avere un compilatore C installato sul tuo sistema.
2. Apri un terminale e posizionati nella directory del progetto.
3. Esegui il comando `make` per compilare il programma.
4. Se vuoi eseguire il programma a singolo processo:
	Esegui il comando `./monoprocesso <file_input> <numero_colonne> <numero_righe> <dimensione_colonne> <distanza_tra_colonne>` 
5. Se vuoi eseguire il programma multi-processo:
	Esegui il comando `./multiprocesso <file_input> <numero_colonne> <numero_righe> <dimensione_colonne> <distanza_tra_colonne>`

NB: Per eseguire i programmi, sostituire `<file_input>` con il percorso del file di input e `<numero_colonne>', '<numero_righe>`, `<dimensione_colonne>`, '<distanza_tra_colonne>' con i parametri di input appropriati.
 
6. Esegui il comando `make clean` per rimuovere i file oggetto e i programmi generati durante il processo di compilazione.

## Esempi di esecuzione

Sono presenti alcuni esempi di file di input per testare la correttezza dei programmi.
I file sono denominati: `input1.txt`, `input2.txt`, `input3.txt`, `input4.txt`
Ecco alcuni esempi di come eseguire il programma:

1. ./monoprocesso input1.txt 3 25 30 10
	
Questo comando legge il file `input1.txt`, formatta il testo con 3 colonne per riga e 25 righe per pagina. Ogni colonna avrà la dimensione di 30 caratteri e tra una colonna e l'altra ci saranno 10 caratteri di spazi vuoti. Il prodotto di questo comando genera il file `output_monoprocesso.txt` e scrive al suo interno il testo generato.

2. ./multiprocesso input4.txt 5 30 20 9 

Questo comando legge il file `input4.txt`, formatta il testo con 4 colonne per riga e 30 righe per pagina. Ogni colonna avrà la dimensione di 20 caratteri e tra una colonna e l'altra ci saranno 9 caratteri di spazi vuoti. Il prodotto di questo comando genera il file `output_multiprocesso.txt` e scrive al suo interno il testo generato.

