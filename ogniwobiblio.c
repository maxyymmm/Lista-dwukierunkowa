#include "lista.dwukierunkowa.h"
#include<stdio.h>
// #include<stdlib.h>

void main()
{
    ogniwo *o = dodaj(NULL, (samolot) {.nazwa="Concord", .liczba_miejsc=60, .rok_produkcji = 1985});  
    dodaj(o, (samolot) {.nazwa="Boeing737", .liczba_miejsc=180, .rok_produkcji = 1997});  
    dodaj(o, (samolot) {.nazwa="Antonov", .liczba_miejsc=30, .rok_produkcji = 2001});
    dodaj(o, (samolot) {.nazwa="Airbus", .liczba_miejsc=500, .rok_produkcji = 2001});  
    wydrukuj(o);

    printf("\nUsuniete\n");
    ogniwo *w = usun(o,2);
    wydrukuj(w);

    printf("\nWstaw element PO indeksie\n");
    ogniwo *f = wstaw_po(w, 3,(samolot) {.nazwa="AntonovPO", .liczba_miejsc=200, .rok_produkcji = 2001});
    wydrukuj(f);

    printf("\nWstaw element PRZED indeksem\n");
    ogniwo *r = wstaw_przed(f, 2,(samolot) {.nazwa="AntonovPrzed", .liczba_miejsc=200, .rok_produkcji = 2001});
    wydrukuj(r);

    printf("\nprzed zmiana: \n");
    wydrukuj(r);
    zamien(r, 2, 5);

    printf("\npo zmiana: \n");
    wydrukuj(r);

    printf("\nPosortowane\n");
    
    QuickSort(r, znajdz_ost(r));
    wydrukuj(r);


// ZAPIS I ODCZYT
    zapisz_do_pliku(r);
    zniszcz(r);

    printf("\nPO ODCZYTANIU Z PLIKU: \n");
    ogniwo *or = odczytaj_z_pliku();

    // printf("wydrukuj po odcz")
    wydrukuj(or);

    printf("\nUsuniete\n");
    ogniwo *wr = usun(or,2);
    wydrukuj(wr);

    printf("\nWstaw element PO indeksie\n");
    ogniwo *fr = wstaw_po(wr, 3,(samolot) {.nazwa="AntonovPO_po_odcz", .liczba_miejsc=200, .rok_produkcji = 2001});
    wydrukuj(fr);

    printf("\nWstaw element PRZED indeksem\n");
    ogniwo *rr = wstaw_przed(fr, 2,(samolot) {.nazwa="AntonovPrzed_po_odcz", .liczba_miejsc=200, .rok_produkcji = 2001});
    wydrukuj(rr);

    printf("\nprzed zmiana: \n");
    wydrukuj(rr);
    zamien(rr, 2, 5);

    printf("\npo zmiana: \n");
    wydrukuj(rr);

    printf("\nPosortowane\n");
    
    QuickSort(rr, znajdz_ost(rr));
    wydrukuj(rr);

    zniszcz(rr);
   
}