#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//functie pentru verificarea unui prizonier
bool testare_nr_cutii(int start, int p, int cutii[]) {
    //pornim de la prima cutie si retinem numarul de cutii deschise pana ajungem la cutia buna
    int nod = start, deschise = 0;

    do {
        deschise++;
        nod = cutii[nod];
    } while (nod != start);

    //intoarcem valoarea de adevar a propozitiei:"prizonierul a deschis cel mult p/2 cutii"
    return (deschise <= p / 2);
}

//functie pentru afisarea ciclurilor
void ciclu(int start, int p, int cutii[], int viz[]) {
    int nod = start;

    //verificam daca am gasit un ciclu nou( cutia de la care pornim nu poate sa faca parte din 2 cicluri)
    if (viz[cutii[start]] == false) {
        //marcam cutia ca facand parte dintr-un ciclu
        viz[nod] = true;

        //afisam prima cutie pentru a nu avea probleme cu spatiul de dupa ultima cutie a ciclului
        printf("%d", nod);

        //pornim de la a doua cutie si parcurgem ciclul
        nod = cutii[nod];
        while (nod != start){
            //afisam un spatiu si cutia curenta
            printf(" %d", nod); 
            //trecem la urmatoarea cutie
            nod = cutii[nod];
            //marcam cutia ca facand parte dintr-un ciclu
            viz[nod] = true;
        }
        printf("\n");
    }
}

int main() {
    int p, cutii[501], viz[501] = {0};

    //citim numarul de prizonieri
    scanf("%d", &p);

    //citim pentru fiecare prizonier cutia pe care o deschide prima data
    for (int i = 1; i <= p; ++i) {
        scanf("%d", &cutii[i]);
    }

    //luam o variabila booleana in care vom retine daca prizonierii au castigat sau nu jocul plecand de la presupunerea ca il vor castiga
    bool ok = true;

    //verificam pentru fiecare prizonier daca deschide mai mult de p/2 cutii
    for (int i = 1; i <= p; ++i) {
        //daca a deschis mai mult de p/2 cutii functia va intoarce false
        if (testare_nr_cutii(i, p, cutii) == false) {
            //am gasit un prizonier care deschide mai mult de p/2 cutii asa ca actualizam variabila booleana, jocul fiind pierdut
            ok = false;
            //iesim din structura repetitiva deoarece am aflat deznodamantul jocului si nu mai trebuie sa ii verificam si pe ceilalti prizonieri
            break;
        }
    }

    //afisam deznodamantul jocului
    if (ok)
        printf("Da\n");
    else
        printf("Nu\n");

    //afisam ciclurile formate de cutii
    for (int i = 1; i <= p; ++i) {
        ciclu(i, p, cutii, viz);
    }

    return 0;
}
