all: full

full: tiny.o nave.o tc3.o
	g++ nave.o tc3.o tinyxml2.o -lGL -lGLU -lglut -lm -o trabalhocg

tc3.o:
	g++ -g -c tc3.cpp -o tc3.o

nave.o:
	g++ -g -c nave.cpp -o nave.o

tiny.o:
	g++ -c tinyxml2.cpp

clean:
	rm -f *.o trabalhocg
