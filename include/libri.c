#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libri.h"
#include "../include/utils.h"

Libro **catalogo = NULL;
int num_libri = 0;

void aggiungi_libro() {
    printf("\n--- AGGIUNTA NUOVO LIBRO ---\n");
    catalogo = realloc(catalogo, sizeof(Libro*) * (num_libri + 1));
    Libro *nuovo = malloc(sizeof(Libro));
    
    nuovo->id = num_libri + 1;
    printf("Titolo: "); 
    fflush(stdout);
    scanf(" %[^\n]", nuovo->titolo);
    printf("Autore: "); 
    fflush(stdout);
    scanf(" %[^\n]", nuovo->autore);
    printf("Genere: "); 
    fflush(stdout);
    scanf(" %[^\n]", nuovo->genere);
    do {
        printf("Numero di copie: "); 
        fflush(stdout);
        if (scanf("%d", &nuovo->copie_disponibili) != 1) {
            pulisci_buffer();
            printf("✗ Inserisci un numero valido.\n");
            nuovo->copie_disponibili = -1;
            continue;
        }
        pulisci_buffer();
        if (nuovo->copie_disponibili < 0) {
            printf("✗ Il numero di copie non può essere negativo.\n");
        }
    } while (nuovo->copie_disponibili < 0);

    nuovo->totale_prestiti = 0;

    catalogo[num_libri++] = nuovo;
    printf("✓ Libro aggiunto con successo! (ID: %d)\n", nuovo->id);
}

void visualizza_libri() {
    if(num_libri == 0) {
        printf("\n--- CATALOGO ---\nIl catalogo è vuoto.\n");
        return;
    }
    
    printf("\n--- CATALOGO (Total: %d) ---\n", num_libri);
    printf("%-5s | %-25s | %-20s | %-15s | %-8s\n", "ID", "Titolo", "Autore", "Genere", "Copie");
    printf("------|---------------------------|----------------------|-----------------|----------\n");
    
    for(int i=0; i<num_libri; i++) {
        printf("%-5d | %-25s | %-20s | %-15s | %-8d\n", 
            catalogo[i]->id,
            catalogo[i]->titolo,
            catalogo[i]->autore,
            catalogo[i]->genere,
            catalogo[i]->copie_disponibili);
    }
}

Libro* cerca_libro_id(int id) {
    for(int i=0; i<num_libri; i++) {
        if(catalogo[i]->id == id) return catalogo[i];
    }
    return NULL;
}

void elimina_libro() {
    if(num_libri == 0) {
        printf("Il catalogo è vuoto.\n");
        return;
    }
    
    visualizza_libri();
    printf("\nInserisci l'ID del libro da eliminare: ");
    fflush(stdout);
    int id;
    scanf("%d", &id);
    pulisci_buffer();
    
    for(int i=0; i<num_libri; i++) {
        if(catalogo[i]->id == id) {
            printf("Elimino libro: %s\n", catalogo[i]->titolo);
            free(catalogo[i]);
            
            // Sposta i libri successivi
            for(int j=i; j<num_libri-1; j++) {
                catalogo[j] = catalogo[j+1];
            }
            num_libri--;
            catalogo = realloc(catalogo, sizeof(Libro*) * num_libri);
            printf("✓ Libro eliminato con successo!\n");
            return;
        }
    }
    printf("✗ Libro non trovato!\n");
}
