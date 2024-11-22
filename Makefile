CC = gcc
CFLAGS = -O3 -g -fPIC
LDFLAGS = -L. -lppm

.PHONY: all clean

# Cible par défaut pour construire tout
all: test mandel

# Construire la bibliothèque partagée
libppm.so: ppm.c
	$(CC) $(CFLAGS) -shared $^ -o $@

# Construire le programme test
test: main.c libppm.so
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Construire le programme mandel
mandel: mandel.c libppm.so
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Nettoyage des fichiers générés
clean:
	rm -f test mandel libppm.so *.ppm
