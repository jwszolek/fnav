#include "def.h"


//functions use in program 
int d_del(char *dir){
  char tab[255];
  int status=0;
  bzero(tab,255);
  strcpy(tab,dir);
  status=del_dir(tab);
  return status;
};

int p_move(char *src,char *dst){
  char f_src[255];
  char f_dst[255];
  int status;
  strcpy(f_src,src);
  strcpy(f_dst,dst); 
  status=rename_file(f_dst,f_src);
  return status;
};

int p_rename(char *src,char *dst){
  char f_src[255];
  char f_dst[255];
  int status;
  strcpy(f_src,src);
  strcpy(f_dst,dst); 
  status=rename_file(f_dst,f_src);
  return status;
};

int p_copy(char *src,char *dst){
  char f_src[255];
  char f_dst[255];
  int status;
  strcpy(f_src,src);
  strcpy(f_dst,dst);
  status=copy_file(f_dst,f_src);
  return status;
};

int p_usun(char *file){
  char tab[255];
  int status;
  strcpy(tab,file);
  status=del_file(tab);
  return status; 
}

int p_nowy(char *file){
  char tab[255];
  int status=0;
  bzero(tab,255);
  strcpy(tab,file);
  status=new_file(tab);
  return status;
}


