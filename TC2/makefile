all: full

full: tiny.o tc2.o
	g++ tc2.o tinyxml2.o -lGL -lGLU -lglut -lm -o trabalhocg

tc2.o:
	g++ -g -c tc2.cpp -o tc2.o

tiny.o:
	g++ -c tinyxml2.cpp

clean:
	rm -f *.o trabalhocg
