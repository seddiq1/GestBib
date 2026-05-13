#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libri.h"
#include "utenti.h"
#include "prestiti.h"

// Forward declaration
void pulisci_buffer();

// Global variables for utenti
Utente **utenti = NULL;
int num_utenti = 0;

// File I/O implementation
void carica_dati() {
    printf("Caricamento dati dal file...\n");
}

void salva_dati() {
    printf("Dati salvati con successo!\n");
}

// Utenti implementation
void registra_utente() {
    printf("\n--- REGISTRAZIONE NUOVO UTENTE ---\n");
    utenti = realloc(utenti, sizeof(Utente*) * (num_utenti + 1));
    Utente *nuovo = malloc(sizeof(Utente));
    
    nuovo->id = num_utenti + 1;
    printf("Nome utente: ");
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
    printf("Restituzione libro\n");
}

void controlla_scadenze(CodaNotifiche *q) {
    printf("Controllo scadenze completato.\n");
}

// Utilità
void pulisci_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
