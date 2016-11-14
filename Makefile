all: server02

server02: server02.o doprocessing.o
	  gcc -o server02 server02.o doprocessing.o
clean:
	/bin/rm/ -rf server02*.o
