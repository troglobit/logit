
all: logit

logit: logit.c

clean:
	rm *.o logit

distclean: clean
	rm *~

