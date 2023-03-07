#include <stdio.h>

#include <stdbool.h>

#include <string.h>

int somme(int n) {
    int s = 0;
    for (int i = 1; i <= n; i++)
        s += i * (i + 2);
    return s;
}

int suite(int n) {
    int u = 1;
    for (int i = 0; i < n; i++) {
        if (u % 2) u = 3 - u;
        else u = 2 * u + 1;
    }
    return u;
}

int compteneg(int n) {
    int nb = 0;
    for (int i = 0; i <= n; i++) {
        nb += suite(i) < 0; // car condition = nombre
    }
    return nb;
}

void occurences(int t[], int n, int occ[]) {
    // Nettoyage
    for (int i = 0; i < 100; i++) occ[i] = 0;
    // Lecture
    for (int i = 0; i < n; i++) occ[t[i]] += 1;
}

bool test_occ() {
    int t[] = {
        0,
        1,
        2,
        3,
        0,
        1,
        2,
        1
    };
    int occ[100];
    occurences(t, 8, occ);
    bool valide = true;
    int res[] = {
        2,
        3,
        2,
        1
    };
    for (int i = 0; i < 100; i++) {
        if (i < 4)
            valide &= occ[i] == res[i];
        else
            valide &= occ[i] == 0;
    }
    return valide;
}

void comptage(int t[], int n) {
    int occ[100];
    occurences(t, n, occ);
    int write = 0; // là où l'on va écricre
    int ind = 0; // ce qu'on va écricre
    while (write < n) {
        if (occ[ind] == 0) ind++;
        else {
            t[write] = ind;
            occ[ind]--;
            write++;
        }
    }
}

bool test_comptage() {
    int t[] = {
        0,
        1,
        2,
        3,
        0,
        1,
        2,
        1
    };
    comptage(t, 8);
    int res[] = {
        0,
        0,
        1,
        1,
        1,
        2,
        2,
        3
    };
    bool valide = true;
    for (int i = 0; i < 8; i++) {
        valide &= t[i] == res[i];
    }
    return valide;
}

int plagemin(char * s) {
    int max = 0;
    int current = 0;
    int i = 0;
    while (s[i]) {
        if (('a' <= s[i]) && (s[i] <= 'z')) current++; // car char = entier
        else {
            if (current > max) max = current;
            current = 0;
        }
        i++;
    }
    if (current > max) max = current; // si le max se situe à la fin

    return max;
}

int test_plagemin() {
    bool valide = true;
    valide &= plagemin("totoTtotou") == 5;
    valide &= plagemin("AtA") == 1;
    valide &= plagemin("AAB") == 0;
    return valide;
}

int recherche(char * s, char * motif) {
    int lenmot = strlen(motif);
    //              int car (size_t 0) - (size_t 6) > 0 
    for (int i = 0; i < (int) strlen(s) - lenmot; i++) {
        bool fits = true;
        for (int j = 0; j < lenmot; j++) {
            fits &= motif[j] == s[i + j];
        }
        if (fits) {
            return i;
        }
    }
    return -1;
}

bool test_recherche() {
    bool valide = true;
    valide &= recherche("tototatota", "tota") == 2;
    valide &= recherche("tototatota", "tata") == -1;
    valide &= recherche("toto", "tototo") == -1;
    valide &= recherche("test", "") == 0;
}

void fusion(int t1[], int n1, int t2[], int n2, int tf[]) {
    int i1 = 0;
    int i2 = 0;
    int iF = 0; // car "if" déjà pris... 
    while (i1 < n1 && i2 < n2) {
        if (t1[i1] < t2[i2]) {
            tf[iF] = t1[i1];
            i1++;
        } else {
            tf[iF] = t2[i2];
            i2++;
        }
        iF++;
    }
    // ce qu'il reste :
    while (i1 < n1) tf[iF++] = t1[i1++];
    while (i2 < n2) tf[iF++] = t2[i2++];
}

int test_fusion() {
    int t1[] = {
        0,
        1,
        4,
        6
    };
    int t2[] = {
        1,
        2,
        3,
        4,
        5
    };
    int t[9];
    fusion(t1, 4, t2, 5, t);
    int tres[] = {
        0,
        1,
        1,
        2,
        3,
        4,
        4,
        5,
        6
    };
    bool valide = true;
    for (int i = 0; i < 9; i++) {
        if (tres[i] != t[i]) {
            valide = false;
        }
    }
    return valide;
}

int main() {
    printf("Somme(10) : %d\n", somme(10));
    printf("u_10 : %d\n", suite(10));
    printf("neg avant 10 : %d\n", compteneg(10));
    printf("Est valide occ: %d\n", test_occ());
    printf("Est valide comptage: %d\n", test_comptage());
    printf("Est valide plagemin: %d\n", test_plagemin());
    printf("Est valide recherche: %d\n", test_recherche());
    printf("Est valide fusion: %d\n", test_fusion());
}
