#include <cdk.h>
#include <stdio.h>
#include <ncurses.h>
#include "def.h"


//funckje assemblerowe 
extern char new_file(char *buf);
extern char new_dir(char *buf);
extern char del_file(char *buf);
extern char copy_file(char *dst,char *src);
extern char rename_file(char *dst,char *src);
extern char move_file(char *dst,char *src);
extern char del_dir(char *buf);
//***

void entry(CDKSCREEN *cdkscreen,CDK_PARAMS params,int mode);
void list(CDKSCREEN *cdkscreen,CDKFSELECT *fSelect,char *directory,CDK_PARAMS params,CDKDIALOG *pytanie,int selected, int selection);

struct data{
  char *filename;
  char *name_f;
};

struct data d;

int main (int argc, char **argv)
{
  
  //wypisz();
  //exit(1);

  CDKSCREEN *cdkscreen = 0;
  CDKFSELECT *fSelect	= 0;
  WINDOW *cursesWin	= 0;
  
  CDKDIALOG *pytanie =0;
  char *przyc[]	= {"</B/24>Ok", "</B16>Cancel"};
  char *mes[10];
  
  char *title		= "<C></B>File </B>Navigator\n";
  char *label		= "File: ";
  char *button[5] ;
  char *vbut[] = {"</B/24>OK", "</B/24>DEL_FILE", "</B/24>RENAME_FILE","</B/24>COPY_FILE","</B/24>MOVE_FILE"};
  char vTitle[256];
  char *mesg[4];
  char temp[256];
  int selected, selection;
  int status;
  
  CDK_PARAMS params;
  //   char *filename;		
  char *directory;		
  int interp_it;		
  
   CDKparseParams(argc, argv, &params, "f:d:i" CDK_CLI_PARAMS);
   d.filename     = CDKparamString (&params, 'f');
   directory    = CDKparamString2 (&params, 'd', ".");
   interp_it	= CDKparamNumber2 (&params, 'i', FALSE);

   /* Create the viewer buttons. */
   button[0]	= "</5><OK><!5>";
   button[1]	= "</5><Cancel><!5>";

   /* Set up CDK. */
   cursesWin = initscr();
   cdkscreen = initCDKScreen (cursesWin);

   /* Start color. */
   initCDKColor();

   fSelect = newCDKFselect (cdkscreen,
			       CDKparamValue(&params, 'X', CENTER),
			       CDKparamValue(&params, 'Y', CENTER),
			       CDKparamValue(&params, 'H', 50),
			       CDKparamValue(&params, 'W', 65),
			    title,label,A_NORMAL, '_', A_REVERSE,
			       "</5>", "</48>", "</N>", "</N>",
			       CDKparamValue(&params, 'N', TRUE),
			       CDKparamValue(&params, 'S', FALSE));

  
   while(1){

   list(cdkscreen,fSelect,directory,params,pytanie,selected,selection);

   sprintf (vTitle, "<C></B/21>Filename:<!21></22>%20s<!22!B>", d.filename);
   selected = viewFile (cdkscreen, vTitle, d.filename, vbut, 5);

   switch(selected){
     /* OK */
   case 0:{
     d.filename=0;
     list(cdkscreen,fSelect,directory,params,pytanie,selected,selection);
   };break;
   /* DEL FILE */
   case 1:{
     status = p_usun(d.filename);
     if(status == 1){
       sprintf(temp,"<C></24>BLAD! PRZY USOWANIU PLIKU - %s",d.filename);
       mesg[0] = temp;
       mesg[1] = "";
       mesg[2] = "<C>Nacisnij dowolny przycisk";
       popupLabel (cdkscreen, mesg, 3);
       };
     d.filename=0;
     list(cdkscreen,fSelect,directory,params,pytanie,selected,selection);
   };break;
   /* RENAME FILE */
   case 2:{
     entry(cdkscreen,params,3);
     status = p_rename(d.filename,d.name_f);
     if(status == 1){
       sprintf(temp,"<C></24>BLAD! PRZY ZMIANIE NAZWY PLIKU - %s",d.filename);
       mesg[0] = temp;
       mesg[1] = "";
       mesg[2] = "<C>Nacisnij dowolny przycisk";
       popupLabel (cdkscreen, mesg, 3);
       };
     d.filename=0;
     list(cdkscreen,fSelect,directory,params,pytanie,selected,selection);     
   };break;
   
   /* COPY FILE */
   case 3:{
     entry(cdkscreen,params,2);
     status = p_copy(d.filename,d.name_f);
     if(status == 1){
       sprintf(temp,"<C></24>BLAD! PRZY KOPIOWANIU PLIKU - %s",d.filename);
       mesg[0] = temp;
       mesg[1] = "";
       mesg[2] = "<C>Nacisnij dowolny przycisk";
       popupLabel (cdkscreen, mesg, 3);
       };
     d.filename=0;
     list(cdkscreen,fSelect,directory,params,pytanie,selected,selection);
   };break;

   /* MOVE FILE */
   case 4:{
     entry(cdkscreen,params,4);
     status = p_move(d.filename,d.name_f);
     if(status == 1){
       sprintf(temp,"<C></24>BLAD! PRZY PRZENOSZENIU PLIKU - %s",d.filename);
       mesg[0] = temp;
       mesg[1] = "";
       mesg[2] = "<C>Nacisnij dowolny przycisk";
       popupLabel (cdkscreen, mesg, 3);
       };
     d.filename=0;
     list(cdkscreen,fSelect,directory,params,pytanie,selected,selection);
   };break;

   }};
  
   /* Destroy the file selector widget (do not need filename anymore) */
   destroyCDKFselect (fSelect);
   
   destroyCDKScreen (cdkscreen);

   
   endCDK();
   exit (EXIT_SUCCESS);
}


//fnc --
void entry(CDKSCREEN *cdkscreen,CDK_PARAMS params,int mode){
   WINDOW *cursesWin	= 0;
   CDKENTRY *directory = 0; 
   char *title=0;
   char *info=0, *mesg[10], temp[256];
   char *label=0;

   if(mode==0){
     title		= "<C>Wpisz \n<C>nazwe pliku.";
   };
   if(mode==1){
     title		= "<C>Wpisz \n<C>nazwe katalogu.";
   };
   if(mode==2){
     title = "<C>Miejsce skopiowania pliku";
   };
   if(mode==3){
     title = "<C>Podaj nowa nazwe pliku";
   };
   if(mode==4){
     title = "<C>Podaj nowa nazwe pliku po przeniesieniu";
   };

   //plik
   if(mode == 0) 
     label = "</U/5>Plik:<!U!5>";
   else label= "</U/5>Katalog:<!U!5>";
   
   bzero(temp,256);
   directory = newCDKEntry (cdkscreen,
			    CDKparamValue(&params, 'X', CENTER),
			    CDKparamValue(&params, 'Y', CENTER),
			    title, label, A_NORMAL, '.', vMIXED,
			    40, 0, 256,
			    CDKparamValue(&params, 'N', TRUE),
			    CDKparamValue(&params, 'S', FALSE));
   
   
   /* rysowanie/odswirzanie screen_sect */
   refreshCDKScreen (cdkscreen);
   
   /* Aktywacja pola do sprrowadzanai danych_. */
   info = activateCDKEntry (directory, 0);
   
   /* Spr.poprawnosci zatwierdzenia przy wpisywaniu nazwy kat. */
   if (directory->exitType == vESCAPE_HIT){
     mesg[0] = "<C>ESACPE?. Wprowadzana nazwe katalogu potwierdza Enter.";
     mesg[1] = "";
     mesg[2] = "<C>Press any key to continue.";
     destroyCDKEntry (directory);
     popupLabel (cdkscreen, mesg, 3);
   }
   else if (directory->exitType == vNORMAL) /* czy Enter */
     {
       d.name_f = copyChar(info);
       sprintf (temp, "<C>(%.*s)", (int)(sizeof(temp) - 10), info);
       destroyCDKEntry (directory);
     }
   else
     {
       destroyCDKEntry (directory);
     }
}


void list(CDKSCREEN *cdkscreen,CDKFSELECT *fSelect,char *directory,CDK_PARAMS params,CDKDIALOG *pytanie,int selected, int selection){

  char *mes[10], *mesg[10];
  char *przyc[]	= {"</B>NEW_FILE", "</B>NEW_DIR", "</B>CANCEL","</B>DEL_DIR","</B>HELP","</B>  QUIT "};
  char temp[256];
  int licz;
  char *nazwa_pliku;
  FILE *fp;
  char *katalog;
  int status;
 
 if (d.filename==0)
   {


     /* ustawiam startowy katalog - bedzie nim ten w ktrym odpalamy program */
      setCDKFselect (fSelect, directory, A_NORMAL, '.', A_REVERSE,
		     "</B></16>", "</24>", "</N>", "</N>", ObjOf(fSelect)->box);
      

      /* Wlanczam zaznaczenie pliku -> FILE SELECTOR */
      d.filename = activateCDKFselect (fSelect, 0);
      refreshCDKScreen (cdkscreen);
      katalog=getCDKFselectDirectory(fSelect);
      
      if(fSelect->exitType == vESCAPE_HIT)
	{
	  mes[0]	= "<C></U></B/32>File Navigator<!B!32> v.0.1(alpha)";
	  mes[1]	= "";
	  mes[2]	=  "<C>developer: kuba wszolek"; //"<C>Wybierz interesujaca funckje, zmiana opcji ";
	    mes[3]	= "";//"<C>za pomoca przycisku TAB ";
	    mes[4] = ""; //katalog;
	
	  
	  pytanie = newCDKDialog (cdkscreen,
				  CDKparamValue(&params, 'X', CENTER),
				  CDKparamValue(&params, 'Y', CENTER),
				  mes,5, przyc, 6,
				  COLOR_PAIR(2)|A_REVERSE,
				  TRUE,
				  CDKparamValue(&params, 'N', TRUE),
				  CDKparamValue(&params, 'S', FALSE));
	  
	  /* aktywacja dialog box--a. */
	  selection = activateCDKDialog (pytanie, 0);
	  
	  if (pytanie->exitType == vESCAPE_HIT)
	    {
	      mesg[0] = "<C>ESCAPE?!.";
	      mesg[1] = "";
	      mesg[2] = "<C>Press any key to continue.";
	      popupLabel (cdkscreen, mesg, 3);
	    }


	  /* opcje menu tworzenia plikow */
	  switch(selection){
	  case 5:{
	    /* Exit CDK. */
	    destroyCDKFselect (fSelect);
	    destroyCDKScreen (cdkscreen);
	    endCDK();
	    exit (EXIT_SUCCESS);	       
	  };break;
	  
	  /* NEW FILE */
	  case 0:{
	    d.name_f=0;
	    entry(cdkscreen,params,0);
	    status = new_file(d.name_f);
	    if(status==1){
	      sprintf(temp,"<C></24>BLAD!PRZY TWORZENIU PLIKU","!");
	      mesg[0] = temp;
	      mesg[1] = "";
	      mesg[2] = "(plik o tej nazwie prawdopodobnie istnieje)";
	      mesg[3] = "";
	      mesg[4] = "<C>Nacisnij dowolny przycisk";
	      popupLabel (cdkscreen, mesg, 5);
	    }
	    refreshCDKScreen (cdkscreen);
	  };break;
	  
	  /* NEW DIR */
	  case 1:{
	    entry(cdkscreen,params,1);
	    status = new_dir(d.name_f);
	    if(status==1){
	      sprintf(temp,"<C></24>BLAD! PRZY TWORZENIU KATALOGU","!");
	      mesg[0] = temp;
	      mesg[1] = "";
	      mesg[2] = "(katalog o tej nazwie prawdopodobnie istnieje)";
	      mesg[3] = "";
	      mesg[4] = "<C>Nacisnij dowolny przycisk";
	      popupLabel (cdkscreen, mesg, 5);
	    }
	  };break;
	  /* CANCEL */
	  case 2:{
	    //
	  };break;
	  
	  /* DEL DIR */
	  case 3:{
	    entry(cdkscreen,params,1);
	    status = d_del(d.name_f);
	    if(status==1){
	      sprintf(temp,"<C></24>BLAD! PRZY KASOWANIU KATALOGU","!");
	      mesg[0] = temp;
	      mesg[1] = "";
	      mesg[2] = "(katalog o tej nazwie prawdopodobnie nie istnieje)";
	      mesg[3] = "";
	      mesg[4] = "<C>Nacisnij dowolny przycisk";
	      popupLabel (cdkscreen, mesg, 5);
	    }
	  };break;
	  
	  /* MOV DIR */
	  
	  /* HELP */
	  case 4:{
	    //entry(cdkscreen,params,1);
	  };break;
	  };
       
	}
   }
}

//***
