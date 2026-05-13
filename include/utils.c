#include <stdio.h>
#include "../include/utils.h"
#include "../include/libri.h"

void stampa_statistiche() {
    printf("\n--- STATISTICHE POPOLARITA' ---\n");
    for(int i=0; i<num_libri; i++) {
        printf("%-20s ", catalogo[i]->titolo);
        for(int j=0; j < catalogo[i]->totale_prestiti; j++) {
            printf("|");
        }
        printf(" (%d)\n", catalogo[i]->totale_prestiti);
    }
}
