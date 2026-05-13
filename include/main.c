#include <stdio.h>
#include <stdlib.h>
#include "../include/libri.h"
#include "../include/utenti.h"
#include "../include/prestiti.h"
#include "../include/file_io.h"
#include "../include/utils.h"

void menu_libri() {
    int scelta;
    do {
        printf("\n--- GESTIONE LIBRI ---\n");
        printf("1. Aggiungi Libro\n");
        printf("2. Visualizza Catalogo\n");
        printf("3. Elimina Libro\n");
        printf("4. Torna al Menu Principale\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        pulisci_buffer();

        switch(scelta) {
            case 1: aggiungi_libro(); break;
            case 2: visualizza_libri(); break;
            case 3: elimina_libro(); break;
            case 4: return;
            default: printf("Opzione non valida!\n");
        }
    } while(scelta != 4);
}

int main() {
    int scelta;
    CodaNotifiche notifiche;
    inizializza_coda(&notifiche);

    carica_dati();
    controlla_scadenze(&notifiche);

    do {
        printf("\n========== GESTBIB: MENU PRINCIPALE ==========\n");
        visualizza_notifiche(&notifiche);
        printf("1. Gestione Libri\n");
        printf("2. Gestione Utenti\n");
        printf("3. Prestiti\n");
        printf("4. Statistiche\n");
        printf("5. Salva ed Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        pulisci_buffer();

        switch(scelta) {
            case 1: menu_libri(); break;
            case 2: registra_utente(); break;
            case 3: crea_prestito(); break;
            case 4: stampa_statistiche(); break;
            case 5: salva_dati(); break;
            default: printf("Opzione non valida! Riprova.\n");
        }
    } while(scelta != 5);

    return 0;
}
