all: full

full: tiny.o tc1.o
	g++ tc1.o tinyxml2.o -lGL -lGLU -lglut -lm -o trabalhocg

tc1.o:
	g++ -g -c tc1.cpp -o tc1.o

tiny.o:
	g++ -c tinyxml2.cpp

clean:
	rm -f *.o trabalhocg
