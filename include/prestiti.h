#ifndef PRESTITI_H
#define PRESTITI_H
#include "libri.h"
#include "utenti.h"
#include <time.h>

typedef struct Prestito {
    int id;
    Libro *libro;
    Utente *utente;
    time_t data_inizio;
    time_t data_scadenza;
    int restituito; // 0 o 1
} Prestito;

typedef struct NodoNotifica {
    char messaggio[256];
    struct NodoNotifica *next;
} NodoNotifica;

typedef struct {
    NodoNotifica *fronte;
    NodoNotifica *retro;
} CodaNotifiche;

void crea_prestito();
void restituisci_libro();
void controlla_scadenze(CodaNotifiche *q);
void inizializza_coda(CodaNotifiche *q);
void visualizza_notifiche(CodaNotifiche *q);
#endif
