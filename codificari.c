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
    for(int i = 0; i < nr; ++i){
        if(p[i] != ' '){
            if(litera_mica(p[i]))
                p[i] = alfabet[p[i] - 'a' + nr % 52];
            else
                p[i] = alfabet[p[i] - 'A' + 26 + nr % 52];
        }
    }
    s[n - nr + 1] = '\0';
    strcat(p, s);//concateneaza pana la \0
    strcpy(s, p);
    s[n] = '\0';
    puts(s);
}


//netestat
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
    //puts(p);
    strcpy(aux, s + nr);
    //puts(aux);
    strcpy(s, aux);
    s[n] = '\n';
    strcat(s, p);
    puts(s);
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
            getchar();
            //printf("CHEIA ESTE :");
            fgets(cheie, 51, stdin);
            //puts(cheie);
            //printf("before\n");
            //puts(s);
            codificareA(s, n, cheie);
            //printf("after\n");
        }
        
    }while(1);

    printf("\n");
}
