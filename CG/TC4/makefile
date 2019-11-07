all: full

full: tiny.o nave.o tc4.o proj.o
	g++ proj.o nave.o tc4.o tinyxml2.o -lGL -lGLU -lglut -lm -o trabalhocg

tc4.o:
	g++ -g -c tc4.cpp -o tc4.o

proj.o:
	g++ -g -c proj.cpp -o proj.o

nave.o:
	g++ -g -c nave.cpp -o nave.o

tiny.o:
	g++ -c tinyxml2.cpp

clean:
	rm -f *.o trabalhocg
