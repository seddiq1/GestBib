#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libri.h"

Libro **catalogo = NULL;
int num_libri = 0;

void aggiungi_libro() {
    catalogo = realloc(catalogo, sizeof(Libro*) * (num_libri + 1));
    Libro *nuovo = malloc(sizeof(Libro));
    
    nuovo->id = num_libri + 1;
    printf("Titolo: "); scanf(" %[^\n]", nuovo->titolo);
    printf("Autore: "); scanf(" %[^\n]", nuovo->autore);
    printf("Genere: "); scanf(" %[^\n]", nuovo->genere);
    printf("Copie: "); scanf("%d", &nuovo->copie_disponibili);
    nuovo->totale_prestiti = 0;

    catalogo[num_libri++] = nuovo;
}

Libro* cerca_libro_id(int id) {
    for(int i=0; i<num_libri; i++) {
        if(catalogo[i]->id == id) return catalogo[i];
    }
    return NULL;
}
