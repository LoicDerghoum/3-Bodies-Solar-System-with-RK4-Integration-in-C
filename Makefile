# Makefile générique (sysol)
# --------------------- Zone modifiable --------------------------

IDG = 05

# Source C destiné à fournir l'exécutable sysol##
MAINSRCS= $(wildcard main*.c)

# Ci-dessous, tous les fichiers *.c à l'exception du ou des précédents, sont 
# des librairies avec entêtes *.h
LIBSRCS= $(filter-out $(MAINSRCS), $(wildcard *.c))

# CPPFLAGS : options propres au préprocesseur
# CFLAGS : options propres au compilateur C
# LDFLAGS : options propres à l'éditeur de liens
# LDLIBS : librairies à intégrer à l'édition de liens

CPPFLAGS= -DDEBUG
CFLAGS=
LDFLAGS= 
LDLIBS= -lm

# --------------------- Zone non modifiable --------------------------

EXECS = sysol$(IDG)

MAINOBJS=$(patsubst %.c,%.o,$(MAINSRCS))

LIBHS=$(LIBSRCS:.c=.h)
LIBOBJS=$(LIBSRCS:.c=.o)

# Règles

.PHONY: clean
	
all: $(EXECS)

$(MAINOBJS) : %.o :%.c $(LIBHS) $(COMMONHS) $(MAINHS)
	$(CC) -c -o $@ $(CFLAGS) $(CPPFLAGS) $<

$(LIBOBJS) : %.o :%.c %.h $(COMMONHS)
	$(CC) -c -o $@ $(CFLAGS) $(CPPFLAGS) $<
	
$(EXECS) : % : $(MAINOBJS) $(LIBOBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean: 
	rm -f $(EXECS) *.o
