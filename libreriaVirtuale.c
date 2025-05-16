// #INCLUDE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Dichiarazione Struct secondarie
typedef struct _nomeAutori
{
    char nomeAutore[50];
}nomeAutori;

typedef struct _tipoLibro
{
    char genere[20];
}tipoLibro;

// Dichiarazione Struct principale
typedef struct _datiLibro
{
    char titoloLibro[50];
    nomeAutori autoriLibro[4];
    tipoLibro genereLibro[2];
    char editore[50];
    int  numPagine;
    int  numCapitoli;
    int  annoPubblicazione;
    char isbn[13];
}datiLibro;

// Dichiarazione messaggi
#define FILE_NULL "Errore file!"


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


// FUNZIONI PROTOTIPO
void checkFile();
void inserisciTitolo();
void inserisciAutori();
void inserisciGenere();
void inserisciEditore();
void inserisciExtra();
void scriviFile();
void visualizzaDati();


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


// MAIN
int main()
{
    datiLibro libro;

    checkFile();

    inserisciTitolo(&libro);

    inserisciAutori(&libro);

    inserisciGenere(&libro);

    inserisciEditore(&libro);

    inserisciExtra(&libro);

    visualizzaDati(libro);

    scriviFile(libro);

    return 0;
}



// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


void checkFile()
{
    FILE *f;

    f = fopen("./libri.txt", "r");

    //NULL check
    if(f == NULL)
    {
        printf("%s\n", FILE_NULL);
        fclose(f);
        exit(1);
    }
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


void inserisciTitolo(datiLibro *libro)
{
    printf("Dati Libro\n- - - - - - - - - - - - - - - -");

    printf("\nTitolo: ");
    scanf(" %50[^\n]", &libro->titoloLibro);
}



void inserisciAutori(datiLibro *libro)
{
    char userChoice;

    for(int i = 0;i < 4;i++)
    {
        printf("\nAutore: ");
        scanf(" %50[^\n]", &libro->autoriLibro[i]);

        printf("\nInserire altro autore? (Premere S per Si, N per no)");
        scanf(" %c", &userChoice);

        userChoice = toupper(userChoice);
        if(userChoice != 'S')
        {
            //Se userChoice != 'S' riempi le rimanenti posizioni di autoriLibro[] con '/'
            for(int i = 1; i < 4; i++)
            {
                memset(&libro->autoriLibro[i], '\0',sizeof(char) /*(i * sizeof(libro->autoriLibro[0]))*/ );
            }
            break;
        }

    }
}



void inserisciGenere(datiLibro *libro)
{
    for(int i = 0; i < 2; i++)
    {
        int nGenere = i + 1;
        printf("\nGenere %d: ", nGenere);
        scanf(" %50[^\n]", &libro->genereLibro[i]);
    }
}



void inserisciEditore(datiLibro *libro)
{
    printf("\nEditore: ");
    scanf(" %50[^\n]", &libro->editore);
}



void inserisciExtra(datiLibro *libro)
{
    printf("\nN° pagine: ");
    scanf("%d", &libro->numPagine);

    printf("\nN° capitoli: ");
    scanf("%d", &libro->numCapitoli);

    printf("\nAnno pubblicazione: ");
    scanf("%d", &libro->annoPubblicazione);

    printf("\nISBN: ");
    scanf(" %50[^\n]", &libro->isbn);
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


void visualizzaDati(datiLibro libro)
{
    printf("\n\nDATI LIBRO");
    printf("\nTitolo             : %s", libro.titoloLibro);

    for(int i = 0; i < 4; i++)
    {
        printf("\nAutore             : %s", libro.autoriLibro[i]);
    }

    for(int i = 0; i < 2; i++)
    {
        printf("\nGenere             : %s", libro.genereLibro[i]);
    }

    printf("\nEditore            : %s", libro.editore);

    printf("\nN° pagine          : %d", libro.numPagine);

    printf("\nN° capitoli        : %d", libro.numCapitoli);

    printf("\nAnno pubblicazione : %d", libro.annoPubblicazione);

    printf("\nISBN               : %s", libro.isbn);
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


void scriviFile(datiLibro libro)
{
    FILE *f;

     f = fopen("./libri.txt", "r");

    //porta il cursore alla fine del file
    fseek(f, 0, SEEK_END);
    //acquisisce la posizione del cursore
    int posizioneCursore = ftell(f);

    fclose(f);


    //Direttive condizionali di apertura
    if(posizioneCursore == 0)
    {
        f = fopen("./libri.txt", "w+");
        //return *f;
    }
    else if(posizioneCursore != 0)
    {
        //fclose(f);
        f = fopen("./libri.txt", "a+");
        //return *f;
    }


    //STAMPA SU FILE

    fprintf(f,"Titolo             : %s",libro.titoloLibro);

    //stampa autori
    for(int i = 0; i < 4; i++)
    {
        fprintf(f,"\nAutore             : %s", libro.autoriLibro[i]);
    }

    //stampa genere
    for(int i = 0; i < 2; i++)
    {
        fprintf(f,"\nGenere             : %s", libro.genereLibro[i]);
    }

    fprintf(f,"\nEditore            : %s", libro.editore);

    fprintf(f,"\nN° pagine          : %d", libro.numPagine);

    fprintf(f,"\nN° capitoli        : %d", libro.numCapitoli);

    fprintf(f,"\nAnno pubblicazione : %d", libro.annoPubblicazione);

    fprintf(f,"\nISBN               : %s", libro.isbn);

    fprintf(f, "\n");

    //CHIUDI FILE
    fclose(f);
}