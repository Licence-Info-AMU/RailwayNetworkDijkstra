# Makefile de compilation- 02/03/2017
include .config

MKDEP   = gcc -MM
RM      = rm -f

# Si vous voulez utiliser gdb, rajouter "-g" a la fin de CFLAGS ;
# Si vous utilisez des fonctions de <math.h>, rajoutez "-lm" a la fin de LIBS.
CFLAGS  =-Wall -std=c99 -g
LIBS    = 

# Mettre ici la liste des fichiers .c separes par un espace ;
# si besoin on peut eclater la liste sur plusieurs lignes avec "\".
CFILES  = main.c railwayNetwork.c trace.c util.c dijkstra.c generate.c

# Mettre ici le nom de l'executable.
EXEC    = projet

# Calcul automatique de la liste des fichiers ".o" a partir de CFILES.
OBJECTS := $(CFILES:%.c=%.o)

ifdef HAS_GNUMAKE
%.o : %.c 
	$(CC) $(CPATHS) $(CFLAGS) -c $*.c
else
.c.o :
	$(CC) $(CPATHS) $(CFLAGS) -c $*.c
endif

all :: $(EXEC)
	@if [ ! -d $(INSTALL_DIR) ];then \
		mkdir $(INSTALL_DIR); \
	fi
	@cp $(EXEC) $(INSTALL_DIR)

$(EXEC) : $(OBJECTS)
	$(CC) -o $@ $^ $(LIBS)

clean ::
	$(RM) *.o *~ $(EXEC) depend

depend : *.c *.h
	$(MKDEP) *.c >| depend

# Inclut le fichier des dependances. 
# Le "-" devant include supprime l'erreur si le fichier est absent.
-include depend

distclean : clean
	configure -z