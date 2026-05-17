#include <stdio.h>
#include <stdlib.h>
#include "../include/libri.h"
#include "../include/utenti.h"
#include "../include/prestiti.h"
#include "../include/file_io.h"
#include "../include/utils.h"

// Forward declaration
void pulisci_buffer();


int main() {
    int scelta = 0;
    CodaNotifiche notifiche;
    inizializza_coda(&notifiche);

    carica_dati();
    controlla_scadenze(&notifiche);

    do {
        printf("\n========== GESTBIB: MENU PRINCIPALE ==========\n");
        visualizza_notifiche(&notifiche);
        printf("1. Aggiungi Libro\n");
        printf("2. Visualizza Catalogo\n");
        printf("3. Elimina Libro\n");
        printf("4. Registra Utente\n");
        printf("5. Visualizza Utenti\n");
        printf("6. Prestiti\n");
        printf("7. Statistiche\n");
        printf("8. Salva ed Esci\n");
        printf("Scelta: ");
        fflush(stdout);
        if (scanf("%d", &scelta) != 1) {
            pulisci_buffer();
            scelta = -1;
        } else {
            pulisci_buffer();
        }

        switch(scelta) {
            case 1: aggiungi_libro(); break;
            case 2: visualizza_libri(); break;
            case 3: elimina_libro(); break;
            case 4: registra_utente(); break;
            case 5: visualizza_utenti(); break;
            case 6: crea_prestito(); break;
            case 7: stampa_statistiche(); break;
            case 8: salva_dati(); break;
            default: printf("Opzione non valida! Riprova.\n");
        }
    } while(scelta != 8);

    return 0;
}
