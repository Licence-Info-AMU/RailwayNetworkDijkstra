include .config
-include .depend

.PHONY : help all test_config clean distclean

OBJS=main.o read.o trace.o util.o dijkstra.o generate.o
EXECS=projet

install : all
	@if [ ! -d $(INSTALL_DIR) ];then \
		mkdir $(INSTALL_DIR); \
	fi
	@cp $(EXECS) $(INSTALL_DIR)
	$(MAKE) clean

all : clean test_config $(EXECS)

# help :

ifndef HAS_CONFIG
test_config:
	@echo "Erreur, il faut d'abord configurer avec configure">&2
	@false
endif

ifdef HAS_GNUMAKE
%.o : %.c 
	$(CC) $(CPATHS) $(CFLAGS) -c $*.c
else
.c.o :
	$(CC) $(CPATHS) $(CFLAGS) -c $*.c
endif

projet : main.o read.o trace.o util.o dijkstra.o generate.o

$(EXECS) :
	$(CC) $^ $(LPATHS) $(LFLAGS) -o $@

clean :
	rm -f $(EXECS) $(OBJS) *.o

distclean : clean
	configure -z

depend :
	gcc -MM -std=c99 read.c trace.c util.c dijkstra.c generate.c >| .depend
	
uninstall :
	@if [ -d $(INSTALL_DIR) ];then \
		rm -rfv $(INSTALL_DIR); \
	fi
