CC= g++ -Wall -std=c++11 # compilateur + options
CCO= $(CC) -c $<
OBJECTS= main.o Graph.o Arete.o Sommet.o # liste des objets intermédiaires

all : $(OBJECTS)
	$(CC) -o go $(OBJECTS)
	./go

Sommet.o : Sommet.cpp Sommet.hpp
	$(CCO)

Arete.o : Arete.cpp	Arete.hpp
	$(CCO)

Graph.o : Graph.cpp	Graph.hpp 
	$(CCO) 

main.o : main.cpp 
	$(CCO) 

clean :
	rm -f *.o go
