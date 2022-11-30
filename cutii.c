#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool testare_nr_cutii(int start, int n, int p[]) {
    int nod = start, ans = 0;
    do {
        ans++;
        nod = p[nod];
    } while (nod != start);
    return (ans <= n / 2);
}

void afisare(int start, int p[]) {
    int nod = start;
    printf("%d", nod);
    nod = p[nod];
    while (nod != start){
        printf(" %d", nod);
        nod = p[nod];
    }
    printf("\n");
}

void ciclu(int start, int n, int p[], int viz[]) {
    int nod = start, ans = 0;
    // neviz = 0;
    if (viz[p[start]] == false) {
        do {
            viz[nod] = true;
            nod = p[nod];
            ans++;
        } while (nod != start);

        // if(neviz == ans)
        afisare(start, p);
    }
    // return ans;
}

int main() {
    int n, p[505], viz[505] = {0};
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &p[i]);
    }
    int ok = 1;
    for (int i = 1; i <= n; ++i) {
        if (testare_nr_cutii(i, n, p) == false) {
            ok = 0;
            break;
        }
    }

    if (ok == 1)
        printf("Da\n");
    else
        printf("Nu\n");

    for (int i = 1; i <= n; ++i) {
        // printf("%d\n", ciclu(i));
        ciclu(i, n, p, viz);
        // afisare(i);
    }

    return 0;
}
