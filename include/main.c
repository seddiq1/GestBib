#include <stdio.h>
#include <stdlib.h>
#include "../include/libri.h"
#include "../include/utenti.h"
#include "../include/prestiti.h"
#include "../include/file_io.h"
#include "../include/utils.h"

int main() {
    int scelta;
    CodaNotifiche notifiche;
    inizializza_coda(&notifiche);

    carica_dati();
    controlla_scadenze(&notifiche);

    do {
        printf("\n--- GESTBIB: MENU PRINCIPALE ---\n");
        visualizza_notifiche(&notifiche);
        printf("1. Gestione Libri\n2. Gestione Utenti\n3. Prestiti\n4. Statistiche\n5. Salva ed Esci\nScelta: ");
        scanf("%d", &scelta);

        switch(scelta) {
            case 1: aggiungi_libro(); break;
            case 2: registra_utente(); break;
            case 3: crea_prestito(); break;
            case 4: stampa_statistiche(); break;
            case 5: salva_dati(); break;
        }
    } while(scelta != 5);

    return 0;
}
