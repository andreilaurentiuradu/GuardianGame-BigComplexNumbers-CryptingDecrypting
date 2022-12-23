#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// numarul maxim de caractere ale sirului + 1
#define nmax 1002

// comparam 2 vectori (functia returneaza -1 pentru primul mai mare,
// 1 pentru al
// doilea si 0 pentru egale)
int compari(char a[], char b[], int start, int stop) {
    for (int i = start; i <= stop; ++i) {
        if (a[i] < b[i])
            return -1;
        else if (a[i] > b[i])
            return 1;
    }
    return 0;
}

// adunam partea reala si pastram semnul
// if(a[0] == b[0])
void adunare_real(char a[], char b[], int n) {
    // variabila tin_minte va retine valoarea pe care trebuie sa o adaugam pa
    // urmatoarea cifra a numarului in caz ca suma a doua cifre depaseste 9
    int tin_minte = 0, aux;

    // facem suma partilor reale pornind de la ultima cifra a numerelor
    // facem conversia deoarece avem un vector de charuri
    for (int i = (n - 1) / 2 - 1; i >= 1; --i) {
        aux = (a[i] - '0') + (b[i] - '0') + tin_minte;
        a[i] = aux % 10 + '0';
        tin_minte = aux / 10;
    }
}

// procedam in acelasi mod pentru partea imaginara
//  if(a[(n - 1) / 2] == b[(n - 1) / 2])
void adunare_imaginar(char a[], char b[], int n) {
    int tin_minte = 0, aux;
    for (int i = n - 2; i >= (n - 1) / 2 + 1; --i) {
        // retinem suma cifrelor impreuna cu valoarea pe care o tinem minte
        aux = a[i] - '0' + b[i] - '0' + tin_minte;
        // pastram in vector doar ultima cifra, cealalta devine numarul pe care
        // trebuie sa il tinem minte pentru urmatoarea cifra
        a[i] = aux % 10 + '0';
        tin_minte = aux / 10;
    }
}

// interschimbarea a doua charuri
void swap(char *x, char *y) {
    char aux = *x;
    *x = *y;
    *y = aux;
}

// interschimbarea caracterelor cuprinse intre 2 indici
void interschimbare(char a[], char b[], int start, int stop) {
    for (int i = start; i <= stop; ++i) swap(&a[i], &b[i]);
}

// functie pentru operatia de scadere a partii reale
void scadere_real(char a[], char b[], int n) {
    // retinem intr-o variabila care numar este mai mare(in modul)
    int cine_e_mai_mare = compari(a, b, 1, (n - 1) / 2 - 1);

    // daca al doilea numar este mai mare(in modul)
    if (cine_e_mai_mare < 0) {
        // interschimbam cei doi vectori pentru a putea face scaderea(numarul
        // mai mare - numarul mai mic) pastram semnul numarului mai mare(in
        // modul)
        interschimbare(a, b, 0, (n - 1) / 2 - 1);
    }

    // retinem in variabila imprumut daca a fost nevoie sa ne imprumutam la o
    // cifra mai semnificativa pentru a realiza scaderea
    int imprumut = 0, i, dif = 0;
    for (i = (n - 1) / 2 - 1; i >= 1; --i) {
        // retinem diferenta cifrelor
        dif = (int)(a[i] - '0') - (int)(b[i] - '0') - imprumut;

        // verificam semnul diferentei
        if (dif < 0) {
            // daca este negativa este nevoie de un imprumut
            imprumut = 1;
            // punem diferenta in vector adunand un 10(pentru ca ne imprumutam
            // la o cifra mai semnificativa)
            a[i] = dif + '0' + 10;
        } else {
            // nu este nevoie de imprumut
            imprumut = 0;
            // cifra din vector este fix diferenta cifrelor
            a[i] = dif + '0';
        }
    }
}

// procedam analog pentru partea imaginara
void scadere_imaginar(char a[], char b[], int n) {
    int cine_e_mai_mare = compari(a, b, (n - 1) / 2 + 1, n - 2);

    if (cine_e_mai_mare < 0) {
        interschimbare(a, b, (n - 1) / 2, n - 2);
    }

    int imprumut = 0, i, dif = 0;
    for (i = n - 2; i >= (n - 1) / 2 + 1; --i) {
        dif = (int)(a[i] - '0') - (int)(b[i] - '0') - imprumut;
        if (dif < 0) {
            imprumut = 1;
            a[i] = dif + '0' + 10;
        } else {
            imprumut = 0;
            a[i] = dif + '0';
        }
    }
}

// daca semnul e minus schimbi semnul partilor urmatorului nr complex lung
void schimbare_de_semn(char b[], int n) {
    if (b[0] == '0')
        b[0] = '1';
    else
        b[0] = '0';
    if (b[(n - 1) / 2] == '0')
        b[(n - 1) / 2] = '1';
    else
        b[(n - 1) / 2] = '0';
}

// functie pentru realizarea fiecarei operatii
void faci_operatia(char a[], char b[], int n) {
    if (a[0] == b[0])
        adunare_real(a, b, n);
    else
        scadere_real(a, b, n);

    if (a[(n - 1) / 2] == b[(n - 1) / 2])
        adunare_imaginar(a, b, n);
    else
        scadere_imaginar(a, b, n);
}

int main() {
    int n;
    char operatie;
    char a[nmax], b[nmax];
    scanf("%d", &n);
    // scapam de spatiul de dupa n
    getchar();

    // citim primul sir
    fgets(a, 1002, stdin);

    // citim operatia
    scanf("%c", &operatie);

    // verificam daca nu am terminat operatiile(am citit '0')
    while (operatie != '0') {
        // scapam de spatiul de dupa operatie
        getchar();

        // citim urmatorul sir
        fgets(b, 1002, stdin);

        // facem schimbarea de semn daca avem scadere
        if (operatie == '-') schimbare_de_semn(b, n);

        // realizam operatia
        faci_operatia(a, b, n);

        // afisam rezultatul
        printf("%s", a);

        // citim urmatoarea operatie
        scanf("%c", &operatie);
    }
    return 0;
}
