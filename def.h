#ifdef _DEF_H
#define 

//file operation in NASM
extern int d_del(char *dir);
extern int p_move(char *src,char *dst);
extern int p_rename(char *src,char *dst);
extern int p_copy(char *src,char *dst);
extern int p_usun(char *file);
extern int p_nowy(char *file);

#endif /* _DEF_H */

