#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define l_max 20

void cerinta_unu(char **brand, char **numar, char **combustibil, double *consum, int *km, int n, int frecv[4]) {
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

    
    // for(int i = 0; i < n; ++i){
    //     realloc(combustibil[i], strlen(combustibil[i]) * sizeof(char));
    //     realloc(brand[i], strlen(brand[i]) * sizeof(char));
    //     realloc(numar[i], strlen(numar[i]) * sizeof(char));
    // }
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
        int frecv[4] = {0};
        cerinta_unu(brand, numar, combustibil, consum, km, n, frecv);
        printf("benzina - %d\n", frecv[0]);
        printf("motorina - %d\n", frecv[1]);
        printf("hibrid - %d\n", frecv[2]);
        printf("electric - %d\n", frecv[3]);
    }
    return 0;
}
