CC=gcc
CFLAGS=-O3 -g

.PHONY: all
all: test mandel

libppm.so : ppm.c
	$(CC) $(CFLAGS) -fPIC -shared $^ -o $@

test: main.c libppm.so
	$(CC) $(CFLAGS) $(LDFLAGS) $< -lppm -L. -o $@

mandel: mandel.c libppm.so
	$(CC) $(CFLAGS) $(LDFLAGS) $< -lppm -L. -o $@

.PHONY: clean
clean:
	rm -fr $(TARGET) *.so

