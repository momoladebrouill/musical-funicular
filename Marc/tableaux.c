#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define PRINT(X) printf("%i %i %i %i\n",X[0],X[1],X[2],X[3])
#define iseven(x) x%2==0
#define isodd(x) x%2

// Question 1
/* Écrire une fonction swap qui prend en entrée, dans cet ordre, un tableau d'entiers,
   deux indices i et j et permutent les valeurs du tableau situées à ces indices. */
void swap(int tab[], int i, int j)
{
    tab[i]=tab[i]^tab[j];
    tab[j]=tab[i]^tab[j];
    tab[i]=tab[i]^tab[j];
}

bool test_swap()
{
    int t1[] = { 1, 2, 3 };
    swap(t1, 1, 2);
    if(t1[0] != 1 || t1[1] != 3 || t1[2] != 2 )
        return false;
    return true;
}

// Question 2
/* Écrire une fonction renverse qui prend en entrée, dans cet ordre, un tableau d'entiers,
   puis un entier indiquant le nombre d'éléments de ce tableau, et permute ses éléments de
   manière à renverser le tableau 1,2,3 -> 3,2,1 */
void renverse(int tab[], int nb)
{
    for(int i=0;i<nb/2;i++){
        swap(tab,i,nb-i-1);
    }
}

bool test_renverse()
{
    int t1[] = { 1, 2, 3 };
    renverse(t1, 3);
    if(t1[0] != 3 || t1[1] != 2 || t1[2] != 1 )
        return false;
    int t2[] = { 1, 2, 3, 4, 5, 6 };
    renverse(t2, 6);
    for (int i = 0; i < 6; i++)
        if(t2[i] != 6-i)
            return false;
    return true;
}

// Question 3
// Prouver la correction de renverse

// Question 4
/* Écrire une fonction qui étant donné un tableau d'entiers et sa taille,
   effectue un traitement en place sur le tableau en sorte que le
   tableau commence par les nombres pairs et termine par les impairs en respectant l'ordre
   dans lequel ils étaient dans le tableau initialement.

Exemples : 
1, 2, 3, 4 -> 2, 4, 1, 3
1, 3 -> 1, 3
5, 4, 1, 2, 3 -> 4, 2, 5, 1, 3

On pourra commencer par écrire deux fonctions : cherche_pair qui cherche l'indice du premier
nombre pair a partir d'un indice i (et -1 s'il nyen a pas), 
et décale qui prend deux indices i et j et effectue les affectations dans le tableau ainsi
j-1 -> j, j-2 -> j-1, ..., i+1 -> i+2, i -> i+1 pour pouvoir placer un element en i
 */

int cherche_pair(int tab[],int deb, int nb){
    for(int i=deb;i<nb;i++){
        if(tab[i]%2==0)return i;
    }
    return -1;
}

int decale(int tab[],int i,int j){
    for(int k=j;k<i;k--){
        tab[k]=tab[k-1];
    }
}
/*
   void pairs_devant(int tab[], int nb)
   {    
   int i=0;
   int p=cherche_pair(tab,i,nb);
   int pair;

   while(p!=-1){
   pair=tab[p];
   decale(tab,i,p);
   tab[i]=pair;
   i++;
   p=cherche_pair(tab,i,nb);
   PRINT(tab);
   }
   }
 */


int is_good(int tab[],int nb){
    for(int i=0;i<nb;i++){
        if(isodd(tab[i])){
            int good=1;
            for(int a=0;a<i;a++){
                good=good&&(iseven(tab[a]));
            }
            for(int a=i;a<nb;a++){
                good=good&&(isodd(tab[a]));
            }
            return good;
        }
    }
    return 1;
}

void pairs_devant(int tab[], int nb){
    while(!is_good(tab,nb)){
        for(int i=0;i<nb-1;i++){
            if(iseven(tab[i+1]) && isodd(tab[i])){
                swap(tab,i+1,i);
            }
        }
    }
}

bool test_pairs_devant()
{
    int t[] = { 1, 2, 3, 4 };
    pairs_devant(t, 4);
    if(t[0] != 2 || t[1] != 4 || t[2] != 1 || t[3] != 3)
        return false;

    int t2[] = { 5, 4, 1, 2, 3 };
    pairs_devant(t2, 5);
    if(t2[0] != 4 || t2[1] != 2 
            || t2[2] != 5 || t2[3] != 1 || t2[4] != 3)
        return false;

    return true;
}

/*
   Le chiffre Playfair est une technique manuelle de chiffrement symétrique
   et a été historiqueemnt la première technique de chiffremenet par
   substitution de digraphe.

   Ce chiffre utilise une table de 5 par 5 contenant chaque lettre de 
   l'alphabet anglais exactement une fois hormis la lettre Q. 
   La table constitue la clé de chiffrement.

   Par exemple, on peut considérer la table suivante :

   --- --- --- --- ---
   P   L   A   Y   F
   I   R   E   X   M
   B   C   D   G   H
   J   K   N   O   S
   T   U   V   W   Z
   --- --- --- --- ---

   Pour chiffrer un message, on retire tous les espaces et on coupe le
   message en digraphes (groupes de deux lettres) telle que, par exemple,
   `Hello World` devienne `HE LL OW OR LD`. Ensuite on applique les règles
   suivantes pour chaque digraphe afin de produire le message chiffré.

   -   Si les lettres sont les mêmes (ou qu\'il n\'y a plus qu\'une lettre
   comme à la fin d\'un message de longueur impaire), on ajoute un `X`
   après la première lettre et on chiffre le digraphe obtenu.
   -   Si les lettres sont sur la même rangée de la table, on les chiffres
   avec les lettres obtenus immédiatement à droite (si on sort de la
   rangée ainsi, on retourne à la première lettre de celle-ci). Avec la
   table au dessus `CH` devient `DB`.
   -   Si les lettres sont sur la même colonne, on les chiffres par les
   lettres obtenus imédiatement en bas dans la table, en revenant
   aussis à la première en cas de dépassement. Ainsi `VA` deviuent
   `AE`.
   -   Si les lettres ne sont pas sur la même rangée ou la même colonne,
   elles sont les sommets d\'une rectangle dans la table, on les
   chiffre alors avec les autres sommets du rectangle. Comme l\'ordre
   importe, on choisit de chiffrer une lettre par le sommet qui est sur
   la même rangée. ainsi `KM` devient `SR`.

   La table précédente pourra être stockée sous la forme de la chaine
   `"PLAYFAIREXMBCDGHJKNOSTUVWZ"`.

   On ne considère ici que des messages en majuscule sans espace et sans la
   lettre Q. De plus, on va suposer qu\'on n\'a jamais deux `X` consécutifs
   ni un `X` en dernière position, car cela ferait boucler la première
   règle.
 */

// Question 5
int car_vers_row(char cle[], char c)
{
    int i;
    for(i=0;cle[i]-c;i++); 
    // prend un caractère c présent dans la clé et renvoie
    // son numéro de rangée dans row 
    return i/5;
}

int car_vers_col(char cle[], char c)
{
    int i;
    for(i=0;cle[i]-c;i++); 
    // prend un caractère c présent dans la clé et renvoie
    // son numéro de rangée dans row 
    return i%5;
}

bool test_q5()
{
    char cle[] = "PLAYFIREXMBCDGHJKNOSTUVWZ";
    int r = car_vers_row(cle, 'K');
    int c = car_vers_col(cle, 'K');
    if(r != 3 || c != 1) return false;
    r = car_vers_row(cle, 'E');
    c = car_vers_col(cle, 'E');
    if(r != 1 || c != 2) return false;
    return true;
}
// Question 6
char position_vers_car(char cle[], int row, int col)
{
    // renvoie le caractère dans la table cle sur la rangée row et
    // la colonne col

    return cle[col+row*5];
}


bool test_q6()
{
    char cle[] = "PLAYFIREXMBCDGHJKNOSTUVWZ";
    if(position_vers_car(cle, 1, 2) != 'E')
        return false;
    return true;
}

// Question 7
/* Réalise le chiffrement de s avec la cle sous forme d'une chaine comme ci-dessus.
   La chaine de sortie contient assez de place pour stocker le chiffre. Vous devrez bien
   rajouter un '\0' à la fin */
void chiffre(char cle[], char s[], char sortie[])
{
    char a,b;
    int xa,ya,xb,yb;
    int i=0;
    while(s[i]){
        if(a==b){
            b='X';
        }
        if(car_vers_row(cle,a)==car_vers_row(cle,b)){
            xa=(car_vers_col(cle,a)+1)%5;
            xb=(car_vers_col(cle,b)+1)%5;
            ya=yb=car_vers_row(cle,a);
        }
        if(car_vers_col(cle,a)==car_vers_col(cle,b)){
            ya=(car_vers_row(cle,a)+1)%5;
            yb=(car_vers_row(cle,b)+1)%5;
            xa=xb=car_vers_col(cle,a);
        }
        sortie[i]=position_vers_car(cle,xa,ya)
            sortie[i+1]=position_vers_car(cle,xb,yb)

    }

    bool test_chiffre()
    {
        char cle[] = "PLAYFIREXMBCDGHJKNOSTUVWZ";
        char s[] = "HIDETHEGOLDINTHETREEESTUMP";
        char o[30];
        chiffre(cle, s, o);
        if(strcmp(o, "BMNDZBXDKYBEJVDMUIXMMNUVIF") != 0)
            return false;
        char cle2[] = "THEMAGICKYBDFJLNOPRSUVWXZ";
        char s2[] = "ILOVEPROGRAMMINGCOMPETITION";
        chiffre(cle2, s2, o);
        if(strcmp(o, "YDVHCWSPKNTAHKUBIPERMHGHDVRU") != 0)
            return false;
        return true;
    }

    void resultat(int q, bool r)
    {
        printf("Test question %d : %s\n",
                q, r ? "VALIDE" : "INVALIDE");
    }

    int main(void)
    {
        resultat(1, test_swap());
        resultat(2, test_renverse());
        resultat(4, test_pairs_devant());
        resultat(5, test_q5());
        resultat(6, test_q6());
        resultat(7, test_chiffre());
    }
