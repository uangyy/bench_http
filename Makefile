CC ?= gcc
CFLAGS ?= -O0 -Wall -g
LIBS := -lpthread
objects := ae.o bench_http.o http_parser.o units.o

bench_http : $(objects)
	$(CC) $(CFLAGS) $^ -o $@

ae.o : ae.c
	$(CC) $(CFLAGS) -c $^ -o $@

http_parser.o : http_parser.c
	$(CC) $(CFLAGS) -c $^ -o $@

bench_http.o : bench_http.c
	$(CC) $(CFLAGS) $(LIBS) -c $^ -o $@

units.o : units.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	-rm -rf $(objects) bench_http

.PYHONY:clean
