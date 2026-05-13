#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/prestiti.h"
#include "../include/utils.h"

void inizializza_coda(CodaNotifiche *q) {
    q->fronte = q->retro = NULL;
}

void aggiungi_notifica(CodaNotifiche *q, char *msg) {
    NodoNotifica *nuovo = malloc(sizeof(NodoNotifica));
    strcpy(nuovo->messaggio, msg);
    nuovo->next = NULL;
    if (q->retro == NULL) {
        q->fronte = q->retro = nuovo;
    } else {
        q->retro->next = nuovo;
        q->retro = nuovo;
    }
}

void crea_prestito() {
    printf("\n--- CREAZIONE NUOVO PRESTITO ---\n");
    int id_u, id_l;
    printf("ID Utente: "); 
    scanf("%d", &id_u);
    pulisci_buffer();
    printf("ID Libro: "); 
    scanf("%d", &id_l);
    pulisci_buffer();

    Utente *u = cerca_utente_id(id_u);
    Libro *l = cerca_libro_id(id_l);

    if (u && l && l->copie_disponibili > 0) {
        Prestito *p = malloc(sizeof(Prestito));
        p->utente = u;
        p->libro = l;
        p->data_inizio = time(NULL);
        p->data_scadenza = p->data_inizio + (30 * 24 * 60 * 60); // +30 giorni
        p->restituito = 0;
        
        l->copie_disponibili--;
        l->totale_prestiti++;

        // Aggiunta alla lista collegata dell'utente
        NodoPrestito *nuovoNodo = malloc(sizeof(NodoPrestito));
        nuovoNodo->dati_prestito = p;
        nuovoNodo->next = u->prestiti_attivi;
        u->prestiti_attivi = nuovoNodo;

        printf("✓ Prestito registrato con successo!\n");
    } else {
        if (!u) printf("✗ Errore: Utente non trovato!\n");
        if (!l) printf("✗ Errore: Libro non trovato!\n");
        if (l && l->copie_disponibili <= 0) printf("✗ Errore: Copie esaurite!\n");
    }
}

void visualizza_notifiche(CodaNotifiche *q) {
    if (q->fronte == NULL) return;
    printf("\n[NOTIFICHE SCADENZE]\n");
    while (q->fronte != NULL) {
        NodoNotifica *temp = q->fronte;
        printf("⚠ %s\n", temp->messaggio);
        q->fronte = q->fronte->next;
        free(temp);
    }
    q->retro = NULL;
}
