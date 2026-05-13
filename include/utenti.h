#ifndef UTENTI_H
#define UTENTI_H

typedef struct NodoPrestito {
    struct Prestito *dati_prestito;
    struct NodoPrestito *next;
} NodoPrestito;

typedef struct {
    int id;
    char nome[100];
    NodoPrestito *prestiti_attivi;
} Utente;

extern Utente **utenti;
extern int num_utenti;

void registra_utente();
Utente* cerca_utente_id(int id);
void visualizza_utenti();
#endif
