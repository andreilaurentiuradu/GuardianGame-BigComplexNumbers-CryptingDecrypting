#include <stdio.h>
#include <stdlib.h>

int compari(char a[1001], char b[1001], int start, int stop) {
    for(int i = start; i <= stop; ++i) {
        if(a[i] < b[i])
            return -1;
        else if(a[i] > b[i])
            return 1;
    }
    return 0;
}

///aduni partile intregi si pastrezi semnul
///pare ca merge
void adunare_real(char a[1001], char b[1001], int n){
    ///adunam partea reala;

    ///if(a[0] == b[0])
    int tin_minte = 0, aux;
    for(int i = (n - 1) / 2 - 1; i >= 1; --i) {
        aux = a[i] - '0' + b[i] - '0' + tin_minte;
        a[i] = aux % 10 + '0';
        tin_minte = aux / 10;
    }
}

void adunare_imaginar(char a[1001], char b[1001], int n) {
   /// if(a[(n - 1) / 2] == b[(n - 1) / 2])
    int tin_minte = 0, aux;
    for(int i = n - 2; i >= (n - 1) /2 + 1; --i) {
        aux = a[i] - '0' + b[i] - '0' + tin_minte;
        a[i] = aux % 10 + '0';
        tin_minte = aux / 10;
    }
}

///interschimbarea a doua charuri
void swap(char *x, char *y) {
    char aux = *x;
    *x = *y;
    *y = aux;
}

///interschimbarea a doua siruri de caractere cu indici
void interschimbare(char a[1001], char b[1001], int start, int stop)
{
    for(int i = start; i <= stop; ++i)
        swap(&a[i], &b[i]);
}

void scadere_real(char a[1001], char b[1001], int n) {

    if(compari(a, b, 1, (n - 1) / 2 - 1) < 0) ///raspunsu are semnul lui b asa ca le interschimb
        interschimbare(a, b, 0, (n - 1) / 2 - 1);
    ///if(compari(a, b, 1, (n - 1) / 2 - 1) >= 0)///raspunsu are semnu lui a
    int imprumut = 0, i, aux = 0;
    for(i = (n - 1) / 2 - 1; i >= 1 ; --i)
    {
        aux = (int)(a[i] - '0') - (int)(b[i] - '0') - imprumut;
        if(aux < 0)
        {
            imprumut = 1;
            a[i] = aux + '0' + 10;
        }
        else
        {
            imprumut = 0;
            a[i] = aux + '0';
        }
    }
}

void scadere_imaginar(char a[1001], char b[1001], int n) {
    if(compari(a, b, (n - 1) / 2 + 1, n - 2) < 0) ///raspunsu are semnul lui b asa ca le interschimb
    {
        ///pastrezi semnul lui b
        interschimbare(a, b, (n - 1) / 2, n - 2);
    }
    ///if(compari(a, b, 1, (n - 1) / 2 - 1) >= 0)///raspunsu are semnu lui a
    int imprumut = 0, i, aux = 0;
    for(i = n - 2; i >= (n - 1) / 2 + 1; --i)
    {
        aux = (int)(a[i] - '0') - (int)(b[i] - '0') - imprumut;
        if(aux < 0)
        {
            imprumut = 1;
            a[i] = aux + '0' + 10;
        }
        else
        {
            imprumut = 0;
            a[i] = aux + '0';
        }
    }
}

///ai grija ca citesti si enterul
void afisare(char s[1001], int n) {
    for(int i = 0; i < n; ++i)
        printf("%c", s[i]);
    printf("\n");
}


void schimbare_de_semn(char b[1001], int n) {
///daca e minus schimbi semnul partilor urmatorului nr complex lung
    if(b[0] == '0')
        b[0] = '1';
    else
        b[0] = '0';
    if(b[(n - 1) / 2] == '0' )
        b[(n - 1) / 2] = '1';
    else
        b[(n - 1) / 2] = '0';
}

void faci_operatia(char a[1001], char b[1001], int n) {
    if(a[0] == b[0]) {
        adunare_real(a, b, n);
    }
    else
        scadere_real(a, b, n);

    if(a[(n - 1) / 2] == b[(n - 1) / 2])
        adunare_imaginar(a, b, n);
    else
        scadere_imaginar(a, b, n);
}
int main()
{
    int n;
    char spatiu, operatie;
    char a[1001], b[1001];
    scanf("%d", &n);
    scanf("%c", &spatiu);

    ///citim primul sir
    fgets(a, 1001, stdin);

    ///citim operatia
    scanf("%c", &operatie);

    while(operatie != '0') {
        ///citim spatiul de dupa operatie
        scanf("%c", &spatiu);

        ///citim urmatorul sir
        fgets(b, 1001, stdin);

        ///facem schimbarea de semn daca avem scadere
        if(operatie == '-')
            schimbare_de_semn(b, n);

        ///realizam operatia
        faci_operatia(a, b, n);

        ///afisam rezultatul
        afisare(a, n - 1);

        ///citim urmatoarea operatie
        scanf("%c", &operatie);
    }
    return 0;
}
