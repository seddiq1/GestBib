#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libri.h"
#include "utenti.h"
#include "prestiti.h"

#define LIBRI_FILE "include/libri.csv"

// Forward declarations
void pulisci_buffer();
void aggiungi_notifica(CodaNotifiche *q, char *msg);

// Global variables for utenti
Utente **utenti = NULL;
int num_utenti = 0;

void carica_dati() {
    FILE *fp = fopen(LIBRI_FILE, "r");
    if (fp == NULL) return;

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        char *id_str = strtok(buffer, ",");
        char *titolo = strtok(NULL, ",");
        char *autore = strtok(NULL, ",");
        char *genere = strtok(NULL, ",");
        char *copie_str = strtok(NULL, ",");

        if (!id_str || !titolo || !autore || !genere || !copie_str) continue;

        catalogo = realloc(catalogo, sizeof(Libro*) * (num_libri + 1));
        Libro *libro = malloc(sizeof(Libro));
        libro->id = atoi(id_str);
        strncpy(libro->titolo, titolo, sizeof(libro->titolo) - 1);
        strncpy(libro->autore, autore, sizeof(libro->autore) - 1);
        strncpy(libro->genere, genere, sizeof(libro->genere) - 1);
        libro->copie_disponibili = atoi(copie_str);
        libro->totale_prestiti = 0;
        catalogo[num_libri++] = libro;
    }

    fclose(fp);
}

void salva_dati() {
    FILE *fp = fopen(LIBRI_FILE, "w");
    if (fp == NULL) return;

    for (int i = 0; i < num_libri; i++) {
        fprintf(fp, "%d,%s,%s,%s,%d\n",
            catalogo[i]->id,
            catalogo[i]->titolo,
            catalogo[i]->autore,
            catalogo[i]->genere,
            catalogo[i]->copie_disponibili);
    }

    fclose(fp);
    printf("Dati salvati con successo!\n");
}

// Utenti implementation
void registra_utente() {
    printf("\n--- REGISTRAZIONE NUOVO UTENTE ---\n");
    utenti = realloc(utenti, sizeof(Utente*) * (num_utenti + 1));
    Utente *nuovo = malloc(sizeof(Utente));
    
    nuovo->id = num_utenti + 1;
    printf("Nome utente: ");
    fflush(stdout);
    scanf(" %[^\n]", nuovo->nome);
    pulisci_buffer();
    nuovo->prestiti_attivi = NULL;

    utenti[num_utenti++] = nuovo;
    printf("✓ Utente registrato con successo! (ID: %d)\n", nuovo->id);
}

Utente* cerca_utente_id(int id) {
    for(int i = 0; i < num_utenti; i++) {
        if(utenti[i]->id == id) return utenti[i];
    }
    return NULL;
}

void visualizza_utenti() {
    if(num_utenti == 0) {
        printf("Nessun utente registrato.\n");
        return;
    }
    printf("\n--- LISTA UTENTI ---\n");
    for(int i = 0; i < num_utenti; i++) {
        printf("ID: %d - Nome: %s\n", utenti[i]->id, utenti[i]->nome);
    }
}

// Prestiti implementation
void restituisci_libro() {
    if (num_utenti == 0) {
        printf("Nessun utente registrato.\n");
        return;
    }

    int id_u;
    printf("ID Utente: ");
    fflush(stdout);
    scanf("%d", &id_u);
    pulisci_buffer();

    Utente *u = cerca_utente_id(id_u);
    if (!u) {
        printf("Utente non trovato.\n");
        return;
    }

    if (!u->prestiti_attivi) {
        printf("Nessun prestito attivo.\n");
        return;
    }

    NodoPrestito *nodo = u->prestiti_attivi;
    int trovato = 0;

    while (nodo) {
        if (!nodo->dati_prestito->restituito) {
            printf("ID Libro: %d - %s\n", nodo->dati_prestito->libro->id, nodo->dati_prestito->libro->titolo);
        }
        nodo = nodo->next;
    }

    int id_l;
    printf("ID Libro da restituire: ");
    fflush(stdout);
    scanf("%d", &id_l);
    pulisci_buffer();

    nodo = u->prestiti_attivi;
    while (nodo) {
        if (nodo->dati_prestito->libro->id == id_l && !nodo->dati_prestito->restituito) {
            nodo->dati_prestito->restituito = 1;
            nodo->dati_prestito->libro->copie_disponibili++;
            printf("✓ Libro restituito con successo!\n");
            trovato = 1;
            break;
        }
        nodo = nodo->next;
    }

    if (!trovato) {
        printf("Prestito non trovato.\n");
    }
}

void controlla_scadenze(CodaNotifiche *q) {
    time_t ora = time(NULL);

    for (int i = 0; i < num_utenti; i++) {
        NodoPrestito *nodo = utenti[i]->prestiti_attivi;
        while (nodo) {
            if (!nodo->dati_prestito->restituito && nodo->dati_prestito->data_scadenza < ora) {
                char msg[256];
                snprintf(msg, sizeof(msg), "Prestito scaduto: %s (Utente: %s)",
                    nodo->dati_prestito->libro->titolo,
                    utenti[i]->nome);
                aggiungi_notifica(q, msg);
            }
            nodo = nodo->next;
        }
    }
}

// Utilità
void pulisci_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
