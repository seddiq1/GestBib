#ifndef LIBRI_H
#define LIBRI_H

typedef struct {
    int id;
    char titolo[100];
    char autore[100];
    char genere[50];
    int copie_disponibili;
    int totale_prestiti; // Per statistiche
} Libro;

extern Libro **catalogo;
extern int num_libri;

void aggiungi_libro();
void visualizza_libri();
Libro* cerca_libro_id(int id);
void elimina_libro();
#endif
