all: health

%.o: %.c
	gcc -c $<

health: health.o util.o
	gcc -o health health.o util.o

clean:
	rm -f health health.o util.o

.PHONY: clean all
