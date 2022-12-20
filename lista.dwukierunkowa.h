#ifndef LISTA_2_KIERUNKOWA
#define LISTA_2_KIERUNKOWA
#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
    char nazwa[20];
    int liczba_miejsc,rok_produkcji;

} samolot;

typedef struct ogniwo
{
    samolot dane;
    struct ogniwo *nastepny, *poprzedni;

} ogniwo;

ogniwo *dodaj(ogniwo *glowa, samolot dane)
{
    if (glowa == NULL)
    {
        ogniwo *nowe_ogniwo = malloc(sizeof(ogniwo));
        glowa = nowe_ogniwo;
        glowa->dane = dane;
        glowa->poprzedni = NULL;
        glowa->nastepny = NULL;
    }
    else 
    {
        ogniwo *obecny=glowa;
        while (obecny->nastepny != NULL)
        {
            obecny = obecny->nastepny;  
        }

        obecny->nastepny = malloc(sizeof(ogniwo));
        obecny->nastepny->dane = dane;
        obecny->nastepny->poprzedni=obecny;
        obecny->nastepny->nastepny = NULL;
    }
   
    return glowa;
}

void wydrukuj(ogniwo *glowa)
{  
    ogniwo *obecne_ogniwo = glowa;
   
    if(obecne_ogniwo == NULL)
    {
        printf("Lista jest pusta");
    }
    else
    {
        while (obecne_ogniwo != NULL)
        {
            printf("%s %d %d\n", obecne_ogniwo->dane.nazwa, obecne_ogniwo->dane.liczba_miejsc, obecne_ogniwo->dane.rok_produkcji);
            obecne_ogniwo = obecne_ogniwo->nastepny;
        }
    }
}

int dlugosc(ogniwo *glowa)
{  
    int licznik = 0;
   
    if(glowa == NULL)
    {
        printf("Lista jest pusta");
    }
    else
    {
        ogniwo *obecne_ogniwo = glowa;
        while (obecne_ogniwo != NULL)
        {
            licznik++;
            obecne_ogniwo = obecne_ogniwo->nastepny;
        }
    }
    return licznik;
}

ogniwo *usun_pierwszy(ogniwo *glowa)
{
    ogniwo *temp = glowa;
    glowa = glowa->nastepny;
    free(temp);
    temp = NULL;

    glowa->poprzedni=NULL;

    return glowa;
}
ogniwo *usun_ostatni(ogniwo *glowa)
{
    ogniwo *temp = glowa;
    ogniwo *temp2;
    while (temp->nastepny != NULL)
    {
        temp = temp->nastepny;
    }
    temp2 = temp -> poprzedni;
    temp2->nastepny = NULL;
    free(temp);    
    return glowa;
}

ogniwo *usun(ogniwo *glowa, int indeks)
{  
    ogniwo *temp = glowa;
    ogniwo *temp2;

    if(indeks==1)
    {
        glowa = usun_pierwszy(glowa);
        return glowa;
    }
    while (indeks >1)
    {
        temp = temp->nastepny;
        indeks--;
    }
    if(temp->nastepny==NULL)
        {
            glowa = usun_ostatni(glowa);
        }
    else
    {
        temp2 = temp -> poprzedni;
        temp2-> nastepny = temp->nastepny;
        temp->nastepny->poprzedni=temp2;
        free(temp);
        temp = NULL;
    }
    return glowa;
}

ogniwo *wstaw_po(ogniwo *glowa, int indeks, samolot dane)
{
    ogniwo *temp = glowa;
    ogniwo *temp2;
    ogniwo *nowe_ogniwo = dodaj(NULL, dane);
   
    while(indeks != 1)
    {
        temp = temp -> nastepny;
        indeks--;
    }
    if(temp->nastepny == NULL)
    {
        temp->nastepny=nowe_ogniwo;
        nowe_ogniwo->poprzedni=temp;
    }
    else
    {
        temp2 = temp -> nastepny;
        temp->nastepny = nowe_ogniwo;
        temp2->poprzedni = nowe_ogniwo;
        nowe_ogniwo->nastepny = temp2;
        nowe_ogniwo->poprzedni = temp;
    }
    return glowa;
}

ogniwo *znajdz_ost(ogniwo *glowa)
{
    ogniwo *temp = glowa;

    while(temp->nastepny != NULL)
    {
        temp = temp -> nastepny;
    }
    glowa = temp;
}

ogniwo *wstaw_przed(ogniwo *glowa, int indeks, samolot dane)
{
    ogniwo *temp = glowa;
    ogniwo *temp2;
    ogniwo *nowe_ogniwo = dodaj(NULL, dane);

    int kopia_indeks = indeks;
   
    while(kopia_indeks > 2)
    {
        temp = temp -> nastepny;
        kopia_indeks--;
    }
    if(indeks==1)
    {
        nowe_ogniwo->nastepny=temp;
        temp->poprzedni=nowe_ogniwo;
        glowa = nowe_ogniwo;
    }
    else
    {
        temp2 = temp -> nastepny;
        temp->nastepny = nowe_ogniwo;
        temp2->poprzedni = nowe_ogniwo;
        nowe_ogniwo->nastepny = temp2;
        nowe_ogniwo->poprzedni = temp;
    }
    return glowa;
}
void zniszcz(ogniwo *glowa)
{
    while (glowa->nastepny != NULL)
    {
        glowa=glowa->nastepny;
        free(glowa->poprzedni);
    }
}

void zamien(ogniwo *glowa, int indeks_1, int indeks_2)
{  
    ogniwo *temp = glowa;
    ogniwo *temp2 = glowa;
    ogniwo *temp3 = malloc(sizeof(ogniwo)); // do przechowania danych

    while (indeks_1 > 1)
    {
        temp = temp -> nastepny;
        indeks_1--;
    }
    while (indeks_2 > 1)
    {
        temp2 = temp2 -> nastepny;
        indeks_2--;
    }
    temp3->dane = temp->dane;
    temp->dane = temp2->dane;
    temp2->dane = temp3->dane;
    free(temp3);
}

ogniwo *partycja(ogniwo *lewo, ogniwo *prawo)
{
    ogniwo *pivot = prawo;
    ogniwo *i = lewo->poprzedni;
    ogniwo *ptr = lewo;
    for (ptr; ptr != prawo; ptr = ptr->nastepny)
    {
        if (ptr->dane.liczba_miejsc <= pivot->dane.liczba_miejsc)
        {
            if (i == NULL)
            {
                i = lewo;
            }
            else
            {
                i = i-> nastepny;
            }
            int temp = i->dane.liczba_miejsc;
            i->dane.liczba_miejsc = ptr->dane.liczba_miejsc;
            ptr->dane.liczba_miejsc = temp;
        }
    }
    if (i == NULL)
    {
        i = lewo;
    }
    else
    {
        i = i-> nastepny;
    }
    int temp = i->dane.liczba_miejsc;
    i->dane.liczba_miejsc = pivot->dane.liczba_miejsc;
    pivot->dane.liczba_miejsc = temp;
    return i;
}
void QuickSort(ogniwo *lewo, ogniwo *prawo)
{
    if (prawo != NULL && lewo != prawo && lewo != prawo->nastepny)
    {
        ogniwo *p = partycja(lewo, prawo);
        QuickSort(lewo, p->poprzedni);
        QuickSort(p->nastepny, prawo);
    }
}
void zapisz_do_pliku(ogniwo *glowa)
{  
    ogniwo *obecne_ogniwo = glowa;
   
    if(obecne_ogniwo == NULL)
    {
        printf("Lista jest pusta");
    }
    else
    {
        FILE *fPtr;
        fPtr = fopen("zapis.txt", "w");

        while (obecne_ogniwo != NULL)
        {
            fwrite(&obecne_ogniwo->dane, sizeof(samolot), 1, fPtr);
            // fprintf(fPtr, "%s %d %d\n", obecne_ogniwo->dane.nazwa, obecne_ogniwo->dane.liczba_miejsc, obecne_ogniwo->dane.rok_produkcji);
            obecne_ogniwo = obecne_ogniwo -> nastepny;
        }
        fclose(fPtr);
    }
}

ogniwo *odczytaj_z_pliku()
{  
    samolot s_odczyt;
    FILE *fPtr;
    ogniwo *glowa = NULL;
    fPtr = fopen("zapis.txt", "r");
    while(fread(&s_odczyt, sizeof(s_odczyt), 1, fPtr))
    {
        // printf ("%s %d %d\n", s_odczyt.nazwa, s_odczyt.liczba_miejsc, s_odczyt.rok_produkcji);
        glowa = dodaj(glowa, s_odczyt);
    }
    return glowa;
}

#endif