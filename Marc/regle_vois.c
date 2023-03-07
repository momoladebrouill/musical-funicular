#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void vers_binaire(unsigned int x, unsigned char b[]){
  int ind=0;
  int v;
  while(x > 0) {
    v = (x & (1<<ind)) != 0;
    b[ind] = v; 
    x -= v<<ind;
    ind++;
  }
}

bool test_vers_binaire()
{
    bool valide = true;
    unsigned char b[32];
    unsigned char out[] = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 
        1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    vers_binaire(123457, b);
    for(int i =0; i < 32; i++)
    {
        if (b[i] != out[i])
        {
            printf("[Test 1] Erreur en %d : %d != %d\n", i, b[i], out[i]);
            valide = false;
        }
    }
    vers_binaire(4294967295, b);
    for(int i =0; i < 32; i++)
    {
        if (b[i] != 1)
        {
            printf("[Test 2] Erreur en %d : %d != 1\n", i, b[i]);
            valide = false;
        }
    }

    return valide;
}


unsigned int depuis_binaire(unsigned char b[])
{
    int res=0;
    int p2=1;
    for(int i=0;i<32;i++){
      res+=b[i]*p2;
      p2*=2;
    }
    return res;
}

bool test_depuis_binaire()
{
    unsigned char b[] = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    if (depuis_binaire(b) != 123457) return false;
    unsigned char c[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    if (depuis_binaire(c) != 4294967295) return false;

    return true;
}

int regle_vois(int g, int c, int d)
{
    int e=(g<<2)+(c<<1)+d;
    switch(e){
      case 0b100:
      case 0b011:
      case 0b010:
      case 0b001:
        return 1;
      default:
        return 0;
    }
    return 42;
}

bool test_regle_vois()
{
    if (regle_vois(0,0,0) != 0) return false;
    if (regle_vois(0,0,1) != 1) return false;
    if (regle_vois(0,1,0) != 1) return false;
    if (regle_vois(0,1,1) != 1) return false;
    if (regle_vois(1,0,0) != 1) return false;
    if (regle_vois(1,0,1) != 0) return false;
    if (regle_vois(1,1,0) != 0) return false;
    if (regle_vois(1,1,1) != 0) return false;
    return true;
}

int regle(int config)
{
    switch(config){
      case 0b100:
      case 0b011:
      case 0b010:
      case 0b001:
        return 1;
      default:
        return 0;
    }
    return 42;
}

bool test_regle()
{
    if (regle(0) != 0) return false;
    if (regle(1) != 1) return false;
    if (regle(2) != 1) return false;
    if (regle(3) != 1) return false;
    if (regle(4) != 1) return false;
    if (regle(5) != 0) return false;
    if (regle(6) != 0) return false;
    if (regle(7) != 0) return false;
    return true;
}

void suivant(char in[], char out[])
{
  int i=1;
  while(in[i]){
    out[i]=
      regle_vois(in[i-1]=='#',in[i]=='#',in[i+1]=='#') ?
      '#' : ' ';
    i++;
  }
  out[0]=regle_vois(0,in[0]=='#',in[1]=='#') ? '#' : ' ';
}

bool test_suivant()
{
    char in[] =  "    ##   ## ##     #  # # #";
    char out[] = "                           "; // de meme longueur
    suivant(in, out);
    if(strcmp(out, "   ## # ##  # #   ##### # #") != 0) return false;
    return true;
}


void copie_chaine(char tgt[], char src[])
{
  int i=0;
  while(src[i]){
    tgt[i]=src[i];
    i++;
  }
}

bool test_copie_chaine()
{
    char src[] = "toto";
    char tgt[] = "abcd";
    copie_chaine(tgt, src);
    if (strcmp(src, tgt) != 0) return false;
    return true;
}

void itere_regle(char depart[], char temp[], char sortie[], int iterations)
{
  copie_chaine(temp,depart);
  for(int i=0;i<iterations;i++){
    suivant(temp,sortie);
    copie_chaine(temp,sortie);
  }
}

bool test_itere_regle()
{
    char init[81];
    for(int i = 0; i < 80; i++)
    {
        init[i] = ' ';
    }
    init[80] = '\0';
    char temp[81], sortie[81];
    temp[80] = '\0';
    sortie[80] = '\0';
    strcpy(temp, init);
    strcpy(sortie, init);
    init[40] = '#';
    itere_regle(init, temp, sortie, 30);
    if(strcmp(sortie, "          ##  #    # ###  # ## # #  ##### #  ######  #   # ##   #  #  #         ") != 0)
        return false;
    return true;
}


int regle_gen(int gen, int config)
{
    char b[8];
    vers_binaire(gen,b);
    return b[config];
}

bool test_regle_gen()
{
    if (regle_gen(30, 2) != 1) return false;
    if (regle_gen(188, 6) != 0) return false;
    if (regle_gen(188, 7) != 1) return false;
    if (regle_gen(188, 2) != 1) return false;
    if (regle_gen(188, 3) != 1) return false;
    return true;
}

int s(char sp[],int i){
    return sp[i]=='#';
}

void suivant_gen(int gen, char in[], char out[])
{
  int i=1;
  while(in[i]){
    out[i]=
      regle_gen(gen,4*s(in,i-1)+2*s(in,i)+s(in,i+1)) ?
      '#' : ' ';
    i++;
  }
  out[0]=regle_gen(gen,2*s(in,0)+s(in,1)) ? '#' : ' ';
}



bool test_suivant_gen()
{
    char in[] =  "    ##   ## ##     #  # # #";
    char out[] = "                           "; // de meme longueur
    suivant_gen(30, in, out);
    if(strcmp(out, "   ## # ##  # #   ##### # #") != 0) return false;
    suivant_gen(188, in, out);
    if(strcmp(out, "    # #  # ## #    ## #####") != 0) return false;
    return true;
}

void itere_regle_gen(int gen, char depart[], char temp[], char sortie[], int iterations)
{

  copie_chaine(temp,depart);
  for(int i=0;i<iterations;i++){
    suivant_gen(gen,temp,sortie);
    copie_chaine(temp,sortie);
  }
}


bool test_itere_regle_gen()
{
    char init[81];
    for(int i = 0; i < 80; i++)
    {
        init[i] = ' ';
    }
    init[80] = '\0';
    char temp[81], sortie[81];
    temp[80] = '\0';
    sortie[80] = '\0';
    strcpy(temp, init);
    strcpy(sortie, init);
    init[40] = '#';
    itere_regle_gen(30, init, temp, sortie, 30);
    if(strcmp(sortie, "          ##  #    # ###  # ## # #  ##### #  ######  #   # ##   #  #  #         ") != 0)
        return false;
    itere_regle_gen(188, init, temp, sortie, 30);
    if(strcmp(sortie, "                                        # ### ### ### ### ### ### ### #         ") != 0)
        return false;
    return true;
}


void test(bool b, const char s[])
{
    printf("Test %s : %s\n", s,
            b ? "OK" : "INVALIDE");
}


void see(int regle){
  char init[81];
  for(int i = 0; i < 80; i++)
  {
      init[i] = ' ';
  }
  init[80] = '\0';

  for(int i = 0; i < 30; i++)
  {
      char temp[81], sortie[81];
      temp[80] = '\0';
      sortie[80] = '\0';
      strcpy(temp, init);
      strcpy(sortie, init);
      init[40] = '#';
      itere_regle_gen(regle,init, temp, sortie, i);
      printf("%s\n", sortie);
  }
}

int main(void)
{
    test(test_vers_binaire(), "vers_binaire");
    test(test_depuis_binaire(), "depuis_binaire");
    test(test_regle_vois(), "regle_vois");
    test(test_regle(), "regle");
    test(test_suivant(), "suivant");
    test(test_copie_chaine(), "copie_chaine");
    test(test_itere_regle(), "itere_regle");
    test(test_regle_gen(), "regle_gen");
    test(test_suivant_gen(), "suivant_gen");
    test(test_itere_regle_gen(), "itere_regle_gen");
    for(int i=0;i<256;i++){
      printf("Règle %i:\n",i);
      see(i);
    }
}
