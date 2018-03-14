MKDIR_P = mkdir -p

all: lib example

lib:
	test -d lib || $(MKDIR_P) lib
	$(CC) -c -o lib/libCFTest.o CFTest.c
	ar rcs lib/libCFTest.a lib/libCFTest.o

	$(CC) -c -fPIC -o lib/libCFTest.o CFTest.c
	$(CC) -framework Foundation -shared lib/libCFTest.o -o lib/libCFTest.so
	rm -f lib/libCFTest.o

output:
	test -d example
	$(CC) -Wall -c -o example/libExample.o example/libExample.c
	ar rcs example/libExample.a example/libExample.o
	$(CC) -Wall -o test_example example/test_example.c example/libExample.a lib/libCFTest.a -framework Foundation
	rm -f example/libExample.o example/libExample.a

example: output

clean:
	rm -f test_example 
	rm -rf lib/