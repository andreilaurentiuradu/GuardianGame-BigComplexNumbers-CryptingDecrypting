#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define l_max 20  // lungimea maxima a fiecarui sir de caractere citit
#define pret_benzina 8.02
#define pret_motorina 9.29
#define nr_tipuri 4

// retinem intr-un vector de frecventa numarul de masini care functioneaza cu
// fiecare tip de combustibil
void cerinta_unu(char **combustibil, int n, int frecv[]) {
    for (int i = 0; i < n; ++i) {
        if (strcmp(combustibil[i], "benzina") == 0) frecv[0]++;
        if (strcmp(combustibil[i], "motorina") == 0) frecv[1]++;
        if (strcmp(combustibil[i], "hibrid") == 0) frecv[2]++;
        if (strcmp(combustibil[i], "electric") == 0) frecv[3]++;
    }
}

// consumul unei masini
double consum_per_masina(double consum, int km) { return consum * km / 100; }

// determinam prima aparitie a unui brand nou si retinem in acea pozitie
// consumul total al brandului si suma totala
void grupez_branduri(char **brand, double *litri, double *lei, int n,
                     bool *viz) {
    double litri_total;
    double lei_total;
    for (int i = 0; i < n; ++i) {
        // daca am gasit un brand nou
        if (!viz[i]) {
            litri_total = litri[i];
            lei_total = lei[i];

            // cautam celelate masini din acelasi brand
            for (int j = i + 1; j < n; ++j) {
                if (strcmp(brand[i], brand[j]) == 0) {
                    // daca sunt acelasi brand actualizam consumul si costul
                    // total si marcam masina
                    litri_total += litri[j];
                    lei_total += lei[j];
                    viz[j] = true;
                }
            }

            // actualizam in vectori in prima aparitie a brandului
            litri[i] = litri_total;
            lei[i] = lei_total;
        }
    }
}

void cerinta_doi(char **brand, char **combustibil, double *consum, int n,
                 int *km, double *litri, double *lei, bool *viz) {
    // retinem pentru fiecare masina consumul_total si pretul
    for (int i = 0; i < n; ++i) {
        litri[i] = consum_per_masina(consum[i], km[i]);

        // pretul variaza in functie de tipul de combustibil
        if (strcmp(combustibil[i], "motorina") == 0)
            lei[i] = (double)pret_motorina * litri[i];
        else
            lei[i] = (double)pret_benzina * litri[i];
    }

    grupez_branduri(brand, litri, lei, n, viz);
}

// daca este litera mare
bool litera_mare(char ch) { return ('A' <= ch && ch <= 'Z'); }

// daca este cifra
bool cifra(char ch) { return ('0' <= ch && ch <= '9'); }

// daca numarul unei masini este valid
bool numar_corect(char **numar, int i) {
    // retinem numarul de caractere al numarului
    int lungime_numar = strlen(numar[i]);

    // daca nu are 6, 7 sau 8 cifre numarul va fi sigur invalid
    if (lungime_numar < 6 && lungime_numar > 8) return false;

    // avem 3 tipuri de numar valid
    // (A reprezinta caracter si 1 reprezinta cifra)

    // A11AAA
    if (lungime_numar == 6 && litera_mare(numar[i][0]) && cifra(numar[i][1]) &&
        cifra(numar[i][2]) && litera_mare(numar[i][3]) &&
        litera_mare(numar[i][4]) && litera_mare(numar[i][5]))
        return true;

    // A111AAA
    if (lungime_numar == 7 && litera_mare(numar[i][0]) && cifra(numar[i][1]) &&
        cifra(numar[i][2]) && cifra(numar[i][3]) && litera_mare(numar[i][4]) &&
        litera_mare(numar[i][5]) && litera_mare(numar[i][6]))
        return true;

    // AA11AAA
    if (lungime_numar == 7 && litera_mare(numar[i][0]) &&
        litera_mare(numar[i][1]) && cifra(numar[i][2]) && cifra(numar[i][3]) &&
        litera_mare(numar[i][4]) && litera_mare(numar[i][5]) &&
        litera_mare(numar[i][6]))
        return true;

    // AA111AAA
    if (lungime_numar == 8 && litera_mare(numar[i][0]) &&
        litera_mare(numar[i][1]) && cifra(numar[i][2]) && cifra(numar[i][3]) &&
        cifra(numar[i][4]) && litera_mare(numar[i][5]) &&
        litera_mare(numar[i][6]) && litera_mare(numar[i][7]))
        return true;

    // daca nu se incadreaza in niciun tip atunci numarul este invalid
    return false;
}

// retinem in valid daca numarul de inmatriculare al ficarei masini este valid
void cerinta_trei(char **numar, int n, bool valid[]) {
    for (int i = 0; i < n; ++i) {
        valid[i] = numar_corect(numar, i);
    }
}

int main() {
    char **brand;
    char **numar;
    char **combustibil;
    double *consum;
    int *km;
    int n;
    char cerinta;
    // citim numarul de masini
    scanf("%d", &n);

    // cream matrici alocate dinamic in care vom retine brandurile, numerele de
    // inmatriculare si combustibilul
    brand = malloc(n * sizeof(char *));
    numar = malloc(n * sizeof(char *));
    combustibil = malloc(n * sizeof(char *));

    // consumul si km ii retinem in vectori alocati dinamic
    consum = malloc(n * sizeof(double));
    km = malloc(n * sizeof(int));

    // retinem datele fiecarei masini
    for (int i = 0; i < n; ++i) {
        brand[i] = calloc(l_max, sizeof(char));
        scanf("%s", brand[i]);
        brand[i] = (char *)realloc(brand[i], (strlen(brand[i]) + 1) * sizeof(char));

        numar[i] = calloc(l_max, sizeof(char));
        scanf("%s", numar[i]);
        numar[i] = (char *)realloc(numar[i], (strlen(numar[i]) + 1) * sizeof(char));

        combustibil[i] = calloc(l_max, sizeof(char));
        scanf("%s", combustibil[i]);

        combustibil[i] = (char *)realloc(combustibil[i],
                        (strlen(combustibil[i]) + 1) * sizeof(char));

        scanf("%lf", &consum[i]);
        scanf("%d", &km[i]);
    }

    // scapam de enter
    getchar();

    scanf("%c", &cerinta);

    // pentru cerinta a
    if (cerinta == 'a') {
        // avem 4 tipuri de combustibil
        int frecv[nr_tipuri] = {0};
        cerinta_unu(combustibil, n, frecv);
        printf("benzina - %d\n", frecv[0]);
        printf("motorina - %d\n", frecv[1]);
        printf("hibrid - %d\n", frecv[2]);
        printf("electric - %d\n", frecv[3]);
    }

    if (cerinta == 'b') {
        // vom retine in 3 vectori alocati dinamic
        // 3 tipuri de informatii despre masini

        // numarul de litrii consumati de fiecare masina
        double *litri = calloc(n, sizeof(double));
        // pretul platit de fiecare masina pentru km parcursi
        double *lei = calloc(n, sizeof(double));
        // daca masina a fost luata in calcul pentru realizarea costului total
        // si al combustibilului total consumat
        bool *viz = calloc(n, sizeof(bool));

        cerinta_doi(brand, combustibil, consum, n, km, litri, lei, viz);

        // in vectorul viz va ramane nemarcata prima aparitie a fiecarui brand
        for (int i = 0; i < n; ++i) {
            if (!viz[i]) {
                printf("%s a consumat %.2lf - %.2lf lei\n", brand[i], litri[i],
                       lei[i]);
            }
        }

        // eliberam memoria
        free(litri);
        free(lei);
        free(viz);
    }

    if (cerinta == 'c') {
        // retinem intr-un vector alocat dinamic daca numarul de inmatriculare
        // al fiecarei masini este valid
        bool *valid;
        valid = calloc(n, sizeof(bool));

        cerinta_trei(numar, n, valid);

        // retinem intr-o variabila booleana daca toate masinile au numere de
        // inmatriculare valide
        bool ok = true;
        for (int i = 0; i < n; ++i)
            // verificam daca masina are numarul de inmatriculare valid
            if (!valid[i]) {
                // daca nu, afisam brandul, numarul si mesajul numar invalid
                printf("%s cu numarul %s", brand[i], numar[i]);
                printf(": numar invalid\n");
                // gasind o masina cu numarul invalid inseamna ca nu toate
                // masinile au numarul valid
                ok = false;
            }

        // daca toate masinile au numarul de inmatriculare valid
        if (ok) printf("Numere corecte!\n");

        // eliberam memoria
        free(valid);
    }

    // eliberam memoria
    for (int i = 0; i < n; ++i) {
        free(brand[i]);
        free(numar[i]);
        free(combustibil[i]);
    }
    free(brand);
    free(numar);
    free(combustibil);
    free(consum);
    free(km);
    return 0;
}
