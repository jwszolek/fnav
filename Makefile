# Makefile

SHELL		= /bin/sh

prefix		= /usr/local
exec_prefix	= ${prefix}

srcdir		= .
src 		= src/
CC		= gcc
RM		= rm -f
NASM		= nasm 



LIBS		= -lcdk -lncurses  -L/lib #-static

LINK		= $(CC)

x		= 
o		= .o

NFLAGS		= -f elf 
CFLAGS		= -g -O2 
CPPFLAGS	= -DHAVE_CONFIG_H -Iinclude -D_GNU_SOURCE
LDFLAGS		= -L.. 
MOD1		= $(src)mk_f.o
MOD2		= $(src)mk_d.o
MOD3		= $(src)del_f.o
MOD4		= $(src)cp_f.o
MOD5		= $(src)rename_f.o
MOD6		= $(src)del_d.o

LIBO 		= lib.o

BINS	= libo del_d rename_f cp_f mk_f mk_d del_f fn
 
PRI_BINS = libo del_d rename_f cp_f mk_f mk_d del_f

LINKIT	= $(LINK) $(CFLAGS) $(CPPFLAGS) $? -o $@ $(LDFLAGS) $(LIBS) $(MOD1) $(MOD2) $(MOD3) $(MOD4) $(MOD5) $(MOD6) $(LIBO)

all : $(BINS)

libo: 	lib.c
	$(CC) $(CPPFLAGS) -c lib.c -o lib.o

del_d: $(src)del_d.asm
	$(NASM) $(NFLAGS) $(src)del_d.asm

rename_f: $(src)rename_f.asm
	$(NASM) $(NFLAGS) $(src)rename_f.asm

cp_f:	$(src)cp_f.asm
	$(NASM) $(NFLAGS) $(src)cp_f.asm

mk_f:	$(src)mk_f.asm
	$(NASM) $(NFLAGS) $(src)mk_f.asm

mk_d:	$(src)mk_d.asm
	$(NASM) $(NFLAGS) $(src)mk_d.asm

del_f:	$(src)del_f.asm
	$(NASM) $(NFLAGS) $(src)del_f.asm


fn :		fn.c		; $(LINKIT)

# clean

clean::
	$(RM) $(src)*.o core $(PRI_BINS)
	$(RM) *.o core $(LIBO)

distclean:: clean
	$(RM) Makefile
