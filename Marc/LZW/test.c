#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void){
    char **t = malloc(sizeof(char*)*10);
    for(int i=0;i<10;i++){
        t[i] = malloc(sizeof(char)*2);
        char s[] = "r";
        s[0] = 'a'+i;
        strcpy(t[i],s);
    }
    for(int i=0;i<10;i++)
        printf("%c\n",*t[i]);
    return 0;
}
