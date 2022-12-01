#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
    
    // s[n - 1 - nr] = '\0';
    // //char ans = 
    // puts(p);
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
    strcat(p, s);
    strcpy(s, p);
    s[n] = '\0';
    puts(s);
}
int main() {
    int n, nr;
    char s[501], cod[501];
    char alfabet[100] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    fgets(s, 501, stdin);
    n = strlen(s);
     --n;
    s[n] = '\0';
    do
    {
        scanf("%s", cod);
        if(strcmp(cod, "STOP") == 0)
            return 0;
        scanf("%d", &nr);
        getchar(); // ala de dupa nr
        //printf("%d\n", n);
        //puts(s);
        //puts(cod);
        //printf("%d\n\n", nr);
        codificareB(s, n, nr, alfabet);
    }while(1);

    printf("\n");
}
