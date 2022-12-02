#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define nmax 1001

void afisare(char s[], int n) {
    for(int i = 0; i < n; ++i) {
        printf("%c", s[i]);
    }
}

bool litera_mare(char ch) {
    if('A' <= ch && ch <= 'Z')
        return true;
    return false;
}

bool litera_mica(char ch) {
    if('a' <= ch && ch <= 'z')
        return true;
    return false;
}
void codificareB(char s[], int n, int nr, char alfabet[]) {
    //n e lungimea sirului
    //n - 1 - nr e pozitia ultimului element de pastrat in s
    
    char p[501];
    strcpy(p, s + n - nr);
    s[n - nr] = '\0';
    for(int i = 0; i < nr; ++i){
        if(p[i] != ' '){
            if(litera_mica(p[i]))
                p[i] = alfabet[p[i] - 'a' + nr % 52];
            else
                p[i] = alfabet[p[i] - 'A' + 26 + nr % 52];
        }
    }
    strcat(p, s);//concateneaza pana la \0
    strcpy(s, p);
    s[n] = '\0';
    printf("%s\n", s);
}


void decodificareB(char s[], int n, int nr, char alfabet[]) {
    char p[501], aux[501];

    for(int i = 0; i < nr; ++i) {
        if(s[i] != ' '){
            if(litera_mica(s[i]))
                s[i] = alfabet[s[i] - 'a'  + 52 - nr % 52];
            else
                s[i] = alfabet[s[i] - 'A'  + 78 - nr % 52];
        }
    }
    //puts(s);
    strncpy(p, s, nr);
    p[nr] = '\0';
    //puts(p);
    strcpy(aux, s + nr);
    aux[n - nr] = '\0';
    //puts(aux);
    strcpy(s, aux);
    s[n] = '\0';
    strcat(s, p);
    printf("%s\n", s);
}


void swap_char(char *x, char *y) {
    char aux = *x;
    *x = *y;
    *y = aux;
}

void swap_int(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

void swap_coloane(char a[nmax][nmax], int x, int y, int nr_linii) {
    for(int i = 0; i < nr_linii; i++) {
        swap_char(&a[i][x], &a[i][y]);
    }
}
void sortare(char a[nmax][nmax], char cheie[], int n, int nr_linii) {

    for(int i = 0; i < n - 1; ++i) {
        for(int j = i + 1; j < n; ++j) {
            if(cheie[i] > cheie[j]){
                swap_char(&cheie[i], &cheie[j]);
                //swap_int(&indici[i], &indici[j]);
                swap_coloane(a, i, j, nr_linii);
            }
        }
    }
}

void creare_matriceA(char a[nmax][nmax], int n, int lungime_cheie, char s[]) {
    int lin = 0, col = 0;

    for(int i = 0; i < n; ++i) {
        if(col == lungime_cheie){
            col = 0;
            lin++;
        }
        a[lin][col] = s[i];
        col++;
    }
}

void afisare_vector(int v[], int n) {
    for(int i = 0; i < n; ++i) {
        printf("%d ", v[i]);
    }
    printf("\n");
}


///stergem caracterul de pe pozitia poz
void stergere_caracter(char s[], int n, int poz){
    for(int i = poz; i < n; ++i)
        s[i] = s[i + 1];
    ///pui \n for safety
}
void afisare_matrice(char a[nmax][nmax], int n, int m) {
    for(int i = 0; i < n; ++i)
     {
        for(int j = 0; j < m; ++j)
            printf("%c", a[i][j]);
        printf("\n");
     }
}

void codificareA(char s[], int n, char cheie[], int lungime_cheie) {
    
    char a[nmax][nmax];
    for(int i = 0; i < 500; ++i) {
        for(int j = 0; j < 500; ++j) {
            a[i][j] = '0';
        }
    }

    int nr_linii;
    nr_linii = n / lungime_cheie;
    if(n % lungime_cheie != 0)
        nr_linii++;

    //cream matricea
    creare_matriceA(a, n, lungime_cheie, s);
    sortare(a, cheie, lungime_cheie, n);
    int k = 0;
    for(int j = 0; j < lungime_cheie; ++j){
        for(int i = 0; i < nr_linii; ++i) {
            if(a[i][j] != '0'){
                //printf("%c", a[i][j]);
                s[k] = a[i][j];
            }
            else
            {
                //printf(" ");
                s[k] = ' ';
            }
            ++k;
        }
        //printf("\n");
    }
    s[k] = '\0';
    printf("%s\n", s);
}

int main() {
    int n, nr;
    char s[581], cod[581], cheie[51];
    char alfabet[105] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //s e sirul de decodificat
    fgets(s, 501, stdin);
    n = strlen(s);
    --n;
    s[n] = '\0';
    do
    {
        scanf("%s", cod);

        // daca am ajuns la STOP
        if(strcmp(cod, "STOP") == 0)
            return 0;
        
        // daca codificarea e de tip B
        if(cod[0] == 'C' && cod[strlen(cod) - 1] == 'B'){
            scanf("%d", &nr);
            getchar(); // ala de dupa nr
            codificareB(s, n, nr, alfabet);
        }

        //daca decodificarea e de tip B
        if(cod[0] == 'D' && cod[strlen(cod) - 1] == 'B') {
            scanf("%d", &nr);
            getchar(); // ala de dupa nr
            decodificareB(s, n, nr, alfabet);
        }

        if(cod[0] == 'C' && cod[strlen(cod) - 1] == 'A') {
            getchar();//scap de spatiu de dupa codificare
            //printf("CHEIA ESTE :");
            fgets(cheie, 51, stdin);
            //puts(cheie);
            //printf("before\n");
            //puts(s);
            int lungime_cheie = strlen(cheie);
            //printf("lungime cheie = %d", lungime_cheie);
            lungime_cheie--;
            cheie[lungime_cheie] = '\0';
            codificareA(s, n, cheie, lungime_cheie);
            //printf("after\n");
        }

        //actualizam dimensiunea sirului
        n = strlen(s);
        
    }while(1);

    printf("\n");
}
