#include <stdio.h>
#define true 1
#define false 0


int multiplie (int a,int b){return a*b;}

int suivant(int u){
  return u&1 ? 3*u+1:u/2; 
}

int sup_log2(int n){
  int a=1;
  int p=0;
  while(a<=n){
    a<<=1;
    p++;
  }
  return p;
}

void print_matrix(int t[],int width,int height){
  for(int a=0;a<height;a++){
    for(int b=0;b<width;b++){
      printf("%i ",t[a*width+b]);
          //t[(height-a)*width+(width-b)]);
    }
    printf("\n");
  }
}
char swich(char c){
  if(c<'a' || c>'Z'){
    return c;
  }else{
    if(c<'A'){
      return 'A'+c-'a';
    }else{
      return c-'A';
    }
  }
}

int est_minuscule(char s[]){
    for(int i=0;s[i];i++){
      if('a'<s[i] || s[i]<'z'){
       return false;
      } 
    }
    return true;
}

void capitalise(char s[]){
  for(int i=0;s[i];i++){
      if(!('a' > s[i] || s[i] > 'z')){//si c'est une min
        s[i]+='A'-'a';
    }
  }

}


int main(){
  int t[]={ 1, 2, 3, 4, 5, 6 };
  print_matrix(t,3,2);
  printf("suivant %i\n",suivant(2));
  printf("sup log 16 %i\n",sup_log2(16));
  char s[]="CaCa";
  capitalise(s);
  printf("%s\n",s);
}
