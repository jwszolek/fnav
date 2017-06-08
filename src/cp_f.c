#include <stdio.h>
#include <string.h>

extern char rename_file(char *dst,char *src);
char a[25];
char b[25];

main(){
  int status,dl;

  bzero(a,sizeof(a));
  fgets(a,sizeof(a),stdin);
  dl=strlen(a);
  strncpy(b,a,(dl-1));
  status = rename_file("one","test3");
  //printf("check -- %i\n",new_file(a));
  printf("status -- %i",status);
  printf("koniec -%i\n",dl);
}
