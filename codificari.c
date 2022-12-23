#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// lungimea maxima a sirului s initial este 500, iar pe parcurs poate sa creasca
// cu maximum lungimea maxima a cheii - 1
#define nmax 550

// numarul de litere din alfabet
#define nr_litere 26

// numarul maxim de litere ale sirului + 1
#define sir_max 501

// numarul maxim de litere ai cheii + 1
#define cheie_max 51

// numarul maxim de litere ale comenzii aplicate + 1
#define cod_max 14

// daca caracterul e litera mare
bool litera_mare(char ch) {
    if ('A' <= ch && ch <= 'Z') return true;
    return false;
}

// daca caracterul e litera mica
bool litera_mica(char ch) {
    if ('a' <= ch && ch <= 'z') return true;
    return false;
}

// functie pentru codificarea de tip B
void codificareB(char s[], int nr, char alfabet[]) {
    char p[sir_max];
    // copiem intr-un sir ultimele nr caractere ale lui s
    strcpy(p, s + strlen(s) - nr);
    s[strlen(s) - nr] = '\0';

    // transformam sirul p
    for (int i = 0; i < nr; ++i) {
        if (p[i] != ' ') {
            // spatiile raman neschimbate in sirul final(nu se inlocuiesc cu alt
            // caracter dar pozitia lor difera)
            // trebuie sa inlocuim conform formulei cu o litera din vectorul
            // alfabet
            if (litera_mica(p[i])) {
                // daca e litera mica in p
                p[i] = alfabet[p[i] - 'a' + nr % (nr_litere * 2)];
            } else {
                // daca e litera mare
                p[i] = alfabet[p[i] - 'A' + nr_litere + nr % (nr_litere * 2)];
            }
        }
    }
    // concatenam sirul s la sirul p
    strcat(p, s);
    // p contine acum sirul conform codificariiB
    // copiem in s sirul p pentru a putea lucra cu el la urmatoarele criptari
    strcpy(s, p);
    printf("%s\n", s);
}

// functie pentru decodificarea de tip B
// printr-o decodificare de tip B sirul s isi pastreaza dimensiunea
void decodificareB(char s[], int nr, char alfabet[]) {
    char p[sir_max], aux[sir_max];

    // procedam analog ca la codificareB dorind sa inversam pasii facuti in
    // vectorul alfabet
    ///int pozitie = 0;
    for (int i = 0; i < nr; ++i) {
        if (s[i] != ' ') {
            if (litera_mica(s[i])){
                s[i] =
                    alfabet[s[i] - 'a' + nr_litere * 2 - nr % (nr_litere * 2)];
            }      
            else
                s[i] =
                    alfabet[s[i] - 'A' + nr_litere * 3 - nr % (nr_litere * 2)];
        }
    }

    // copiem in p primele nr caractere din s
    strncpy(p, s, nr);
    p[nr] = '\0';

    // copeim in aux caractere din s exceptand primele nr
    strcpy(aux, s + nr);
    aux[strlen(s) - nr] = '\0';

    // copiem in s caracterele din aux
    strcpy(s, aux);

    // concatenam cele nr caractere modificate la sirul s
    strcat(s, p);

    // afisam sirul decodificat
    printf("%s\n", s);
}

// functie pentru interschimbarea a doua charuri
void swap_char(char *x, char *y) {
    char aux = *x;
    *x = *y;
    *y = aux;
}

// functie pentru interschimbarea a doua coloane
void swap_coloane(char a[][nmax], int x, int y, int nr_linii) {
    for (int i = 0; i < nr_linii; i++) {
        // interschimbam caracterele corespunzatoare aceleiasi linii de pe cele
        // doua coloane
        swap_char(&a[i][x], &a[i][y]);
    }
}

// aplicam selection sort pentru a sorta coloanele matricei in functie de cheie
void sortare(char a[][nmax], char cheie[], int nr_linii) {
    for (int i = 0; i < strlen(cheie) - 1; ++i) {
        for (int j = i + 1; j < strlen(cheie); ++j) {
            if (cheie[i] > cheie[j]) {
                // interschimbam caracterele din cheie
                swap_char(&cheie[i], &cheie[j]);
                // interschimbam coloanele matricei
                swap_coloane(a, i, j, nr_linii);
            }
        }
    }
}

// functie pentru punerea sirului initial intr-o matrice
void creare_matriceA(char a[][nmax], int lungime_cheie, char s[]) {
    int lin = 0, col = 0;

    // punem sirul s in matrice
    for (int i = 0; i < strlen(s); ++i) {
        // verificam daca am terminat linia din matrice(am ajuns pe ultima
        // coloana a ei)
        if (col == lungime_cheie) {
            col = 0;
            lin++;
        }
        a[lin][col] = s[i];
        col++;
    }
}

// functie pentru codificarea sirului de tip A
void codificareA(char s[], char cheie[]) {
    // a va fi matricea conform careia va avea loc codificarea
    char a[nmax][nmax];

    // initializam matricea cu spatii
    for (int i = 0; i < nmax; ++i) {
        for (int j = 0; j < nmax; ++j) {
            a[i][j] = ' ';
        }
    }

    // numarul de linii ale matricei variaza in functie de lungimea cheii
    int nr_linii;
    nr_linii = strlen(s) / strlen(cheie);
    if (strlen(s) % strlen(cheie) != 0) nr_linii++;

    // punem sirul s in matrice
    creare_matriceA(a, strlen(cheie), s);

    // sortam coloanele matricei conform cheii
    sortare(a, cheie, nr_linii);

    // punem in s sirul codificat
    int k = 0;
    for (int j = 0; j < strlen(cheie); ++j) {
        for (int i = 0; i < nr_linii; ++i) {
            s[k] = a[i][j];
            ++k;
        }
    }
    s[k] = '\0';

    // afisam sirul codificat
    printf("%s\n", s);
}

// functie pentru interschimbarea a doua variabile intregi
void swap_int(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

// functie pentru aflarea modului in care s-au interschimbat coloanele conform
// codificariiA cu aceeasi cheie
void reverse_sort(char a[][nmax], char cheie[], int nr_linii) {
    int indici[51];
    // retinem in ind pozitia initiala a literelor din cheie
    for (int i = 0; i < strlen(cheie); ++i) indici[i] = i;

    // sortam lexicografic cu selection sort caracterele din cheie si mutam
    // indicii literelor conform mutarilor
    for (int i = 0; i < strlen(cheie); ++i) {
        for (int j = i + 1; j < strlen(cheie); ++j) {
            if (cheie[i] > cheie[j]) {
                swap_char(&cheie[i], &cheie[j]);
                swap_int(&indici[i], &indici[j]);
            }
        }
    }

    // sortam inapoi vectorul de indici pentru a decodifica matricea
    // deplasarile indicilor sunt exact deplasarile coloanelor din matrice
    for (int i = 0; i < strlen(cheie); ++i) {
        for (int j = i + 1; j < strlen(cheie); ++j) {
            if (indici[i] > indici[j]) {
                swap_int(&indici[i], &indici[j]);
                swap_coloane(a, i, j, nr_linii);
            }
        }
    }
}

// cream matricea sirului(nedecodificat)
void creare_matrice_decod_A(char a[][nmax], int lungime_cheie, char s[],
                            int nr_linii) {
    int k = 0;
    for (int j = 0; j < lungime_cheie; ++j) {
        for (int i = 0; i < nr_linii; ++i) {
            if (k < strlen(s)) {
                a[i][j] = s[k];
                ++k;
            }
        }
    }
}

// functie pentru decodificarea sirului
void decodificareA(char s[], char cheie[]) {
    int nr_linii;
    // a va fi matricea conform careia va avea loc decodificarea
    char a[nmax][nmax];

    // initializam matricea cu spatii
    for (int i = 0; i < nmax; ++i) {
        for (int j = 0; j < nmax; ++j) {
            a[i][j] = ' ';
        }
    }

    // numarul de linii ale matricei variaza in functie de lungimea cheii
    nr_linii = strlen(s) / strlen(cheie);
    if (strlen(s) % strlen(cheie) != 0) nr_linii++;

    // cream matricea decodificatoare
    creare_matrice_decod_A(a, strlen(cheie), s, nr_linii);

    // aflam pozitia pe care s-au deplasat indicii coloanelor conform sortarii
    // cheii si realizam decodificarea matricii
    reverse_sort(a, cheie, nr_linii);

    // punem in s sirul decodificat
    int k = 0;
    for (int i = 0; i < nr_linii; ++i) {
        for (int j = 0; j < strlen(cheie); ++j) {
            s[k] = a[i][j];
            ++k;
        }
    }

    s[k] = '\0';
    printf("%s\n", s);
}

int main() {
    int lungime_sir, nr;
    char s[nmax], cod[cod_max], cheie[cheie_max];
    char alfabet[105] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqr"
        "stuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // s e sirul de decodificat
    fgets(s, sir_max, stdin);

    // scapam de enterul de la finalul sirului
    lungime_sir = strlen(s);
    --lungime_sir;
    s[lungime_sir] = '\0';

    do {
        // citim tipul de codificare
        scanf("%s", cod);

        // daca am ajuns la STOP
        if (strcmp(cod, "STOP") == 0) return 0;

        // daca codificarea e de tip A
        if (cod[0] == 'C' && cod[strlen(cod) - 1] == 'A') {
            // scap de spatiu de dupa codificare
            getchar();

            // citim cheia;
            fgets(cheie, cheie_max, stdin);

            // scapam de enterul de la final
            int lungime_cheie = strlen(cheie);
            lungime_cheie--;
            cheie[lungime_cheie] = '\0';

            // apelam functia de codificare pentru tipul A
            codificareA(s, cheie);
        }

        if (cod[0] == 'D' && cod[strlen(cod) - 1] == 'A') {
            // scap de spatiu de dupa codificare
            getchar();

            // citim cheia
            fgets(cheie, cheie_max, stdin);

            // scapam de enterul de la final
            int lungime_cheie = strlen(cheie);
            lungime_cheie--;
            cheie[lungime_cheie] = '\0';

            // apelam functia de decodificare pentru tipul A
            decodificareA(s, cheie);
        }

        // daca codificarea e de tip B
        if (cod[0] == 'C' && cod[strlen(cod) - 1] == 'B') {
            // citim numarul cu care lucreaza codificareaB
            scanf("%d", &nr);

            // scapam de spatiu
            getchar();

            // apelam functia de codificare pentru tipul B
            codificareB(s, nr, alfabet);
        }

        // daca decodificarea e de tip B
        if (cod[0] == 'D' && cod[strlen(cod) - 1] == 'B') {
            // citim numarul cu care lucreaza decodificareaB
            scanf("%d", &nr);

            // scapam de spatiu
            getchar();

            // apelam functia de decodificare pentru tipul B
            decodificareB(s, nr, alfabet);
        }

        // actualizam dimensiunea sirului
        lungime_sir = strlen(s);

    } while (1);

    printf("\n");
    return 0;
}
