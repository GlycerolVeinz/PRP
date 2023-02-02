CC=clang
CFLAGS+= -pedantic -Wall -Werror -std=c99 -O3
CFLAGS+= -lm
HW=HW04B
ZIP=zip

$(HW): main.c 
	$(CC) $(CFLAGS) main.c -o main

zip:
	$(ZIP) $(HW).zip main.c

clean:
	$(RM) -f *.o
	$(RM) -f $(HW)
	$(RM) -f $(HW)-brute.zip
	$(RM) -f main
	$(RM) -f test

.PHONY: clean zip
