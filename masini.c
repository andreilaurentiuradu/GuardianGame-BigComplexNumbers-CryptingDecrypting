#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define l_max 20
#define pret_benzina 8.02
#define pret_motorina 9.29

void cerinta_unu(char **combustibil, int n, int frecv[4]) {
    for(int i = 0; i < n; ++i) {
        if(strcmp(combustibil[i], "benzina") == 0)
            frecv[0]++;
        if(strcmp(combustibil[i], "motorina") == 0)
            frecv[1]++;
        if(strcmp(combustibil[i], "hibrid") == 0)
            frecv[2]++;
        if(strcmp(combustibil[i], "electric") == 0)
            frecv[3]++;
    }
}

float consum_per_masina(double consum, int km) {
    return consum * km / 100;
}

void grupez_branduri(char **brand, float *litri, double *lei,  int n, bool *viz){
    float litri_total;
    double lei_total;
    for(int i = 0; i < n; ++i) {
        if(!viz[i]){
            litri_total = litri[i];
            lei_total = lei[i];
            for(int j = i + 1; j < n; ++j) {
                if(strcmp(brand[i], brand[j]) == 0){
                    //daca sunt acelasi brand
                    litri_total += litri[j];
                    lei_total += lei[j];
                    viz[j] = true;
                }
            }
            //printf("litri : %f      lei : %lf\n", litri_total, lei_total);
            litri[i] = litri_total;
            lei[i] = lei_total;
        }
    }
}

//urmeaza sa le separi in functie de brand parcurgand vectorul de branduri si marcand brandurile folosite
void cerinta_doi(char **brand, char **combustibil, double *consum, int n, int *km, float *litri, double *lei, bool *viz) {
    //cream pentru fiecare masina consumul_total si pretul
    for(int i = 0; i < n; ++i) {
        litri[i] = consum_per_masina(consum[i], km[i]);
        //printf("i = %d => %f ", i, litri[i]);
        if(strcmp(combustibil[i], "motorina") == 0)
            lei[i] = (double) pret_motorina * litri[i];
        else
            lei[i] = (double) pret_benzina * litri[i];
    }
    grupez_branduri(brand, litri, lei, n, viz);
}


bool litera_mare(char ch){
    return ('A' <= ch && ch <='Z');
}

bool cifra(char ch){
    return ('0' <= ch && ch <= '9');
}

bool numar_corect(char **numar, int i) {
    int lungime_numar = strlen(numar[i]);
    if(lungime_numar < 6 && lungime_numar > 8)
        return false;
    
    //A11AAA
    if(lungime_numar == 6 && litera_mare(numar[i][0]) && cifra(numar[i][1]) && cifra(numar[i][2]) && litera_mare(numar[i][3]) && litera_mare(numar[i][4]) && litera_mare(numar[i][5]))
        return true;
    
    //A111AAA
    if(lungime_numar == 7 && litera_mare(numar[i][0]) && cifra(numar[i][1]) && cifra(numar[i][2]) && cifra(numar[i][3]) && litera_mare(numar[i][4]) && litera_mare(numar[i][5]) && litera_mare(numar[i][6]))
        return true;

    //AA11AAA
    if(lungime_numar == 7 && litera_mare(numar[i][0]) && litera_mare(numar[i][1]) && cifra(numar[i][2]) && cifra(numar[i][3]) && litera_mare(numar[i][4]) && litera_mare(numar[i][5]) && litera_mare(numar[i][6]))
        return true;
    
    //AA111AAA
    if(lungime_numar == 8 && litera_mare(numar[i][0]) && litera_mare(numar[i][1]) && cifra(numar[i][2]) && cifra(numar[i][3]) && cifra(numar[i][4]) && litera_mare(numar[i][5]) && litera_mare(numar[i][6]) && litera_mare(numar[i][7]))
        return true;

    return false;
}
void cerinta_trei(char **numar, int n, bool valid[]) {
    
    for(int i = 0; i < n; ++i) {
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
    scanf("%d", &n);

    brand = malloc(n * sizeof(char *));
    for(int i = 0; i < n; ++i) 
        brand[i] = calloc(l_max, sizeof(char));

    // scanf("%s", brand[0]);
    // printf("%s\n", brand[0]);

    numar = malloc(n * sizeof(char *));
    for(int i = 0; i < n; ++i) 
        numar[i] = calloc(l_max, sizeof(char));

    combustibil = malloc(n * sizeof(char *));
    for(int i = 0; i < n; ++i)
        combustibil[i] = calloc(l_max, sizeof(char));
    
    consum = malloc(n * sizeof(double));
    km = malloc(n * sizeof(int));

    bool merge = 0;
    for(int i = 0; i < n; ++i){
        scanf("%s", brand[i]);
        merge = realloc(brand[i], strlen(brand[i]) * sizeof(char));
        // if(merge)
        //     printf("da\n");
        scanf("%s", numar[i]);
        merge = realloc(numar[i], strlen(numar[i]) * sizeof(char));
        // if(merge)
        //     printf("da\n");
        scanf("%s", combustibil[i]);
        merge = realloc(combustibil[i], strlen(combustibil[i]) * sizeof(char));
        // if(merge)
        //     printf("da\n");
        scanf("%lf", &consum[i]);
        scanf("%d", &km[i]);
    }
    if(!merge)
        printf("ceva buseste\n");

    getchar();//pt enter
    scanf("%c", &cerinta);

    /*for(int i = 0; i < n; ++i)
        printf("%s ", brand[i]);
    printf("\n");

    for(int i = 0; i < n; ++i)
        printf("%s ", numar[i]);
    printf("\n");

    for(int i = 0; i < n; ++i)
        printf("%s", combustibil[i]);
    printf("\n");

    for(int i = 0; i < n; ++i)
        printf("%lf ", consum[i]);
    printf("\n");

    for(int i = 0; i < n; ++i)
        printf("%d ", km[i]);
    printf("\n");*/
    

    if(cerinta == 'a'){
        //avem 4 tipuri de combustibil
        int frecv[4] = {0};
        cerinta_unu(combustibil, n, frecv);
        printf("benzina - %d\n", frecv[0]);
        printf("motorina - %d\n", frecv[1]);
        printf("hibrid - %d\n", frecv[2]);
        printf("electric - %d\n", frecv[3]);
    }

    if(cerinta == 'b'){
        float *litri = calloc(n, sizeof(float));
        double *lei = calloc(n, sizeof(double));
        bool *viz = calloc(n, sizeof(bool));
        cerinta_doi(brand, combustibil, consum, n, km, litri, lei, viz);
        for(int i = 0; i < n; ++i) {
            if(!viz[i]){
                printf("%s a consumat %.2f - %.2lf lei\n", brand[i], litri[i], lei[i]);
            }
        }
        free(litri);
        free(lei);
        free(viz);
    }
    if(cerinta == 'c'){
        bool *valid;
        valid = calloc(n, sizeof(bool));
        cerinta_trei(numar, n, valid);
        // for(int i = 0; i < n; ++i)
        //     printf("%d ", valid[i]);
        // printf("\n");

        bool ok = true;
        for(int i = 0; i < n; ++i) {
            if(!valid[i]){
                printf("%s cu numarul %s: numar invalid\n", brand[i], numar[i]);
                ok = false;
            }
        }

        if(ok)
            printf("Numere corecte!\n");
        
        free(valid);
    }
    
    //eliberam memoria 
    for(int i = 0; i < n; ++i){
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
