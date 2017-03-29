SHELL   = /bin/bash
CC      = gcc
MKDEP   = gcc -MM
RM      = rm -f
CFLAGS = -Wall -std=c99 -g
LIBS   =
CFILES  = main.c railwayNetwork.c trace.c util.c tas.c trajet.c moyenne.c distance.c cluster.c dijkstra.c

# Mettre ici le nom de l'executable.
EXEC    = dijkstra

# Calcul automatique de la liste des fichiers ".o" a partir de CFILES.
OBJECTS := $(CFILES:%.c=%.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $*.c

all :: $(EXEC)

$(EXEC) : $(OBJECTS)
	$(CC) -o $@ $^ $(LIBS)

clean ::
	$(RM) *.o *~ $(EXEC) depend

depend : *.c *.h
	$(MKDEP) *.c >| depend

# Inclut le fichier des dependances. 
# Le "-" devant include supprime l'erreur si le fichier est absent.
-include depend

tar :: clean
	@N=$$(pwd) ; N=$$(basename "$$N") ;\
	(cd .. && tar cvfz "$$N.tgz" "$$N" --exclude='svg*' --exclude='*.tgz' --exclude='*.zip' && \
	 echo "DONE ../$$N.tgz")
	 
zip :: clean
	@N=$$(pwd) ; N=$$(basename "$$N") ;\
	(cd .. && zip -r "$$N.zip" "$$N" --exclude='svg*' --exclude='*.tgz' --exclude='*.zip' && \
	echo "DONE ../$$N.zip")
