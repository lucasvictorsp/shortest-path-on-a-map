# Project: shortest-path-on-a-map
# Makefile para gerar o executavel para o teste das classes
# PontoMap, main, Hash, Lista, Nodo
#Criado por Lucas Victor es71512
# Criado em 22/03/2015

all: PontoMap.o main.o main.o
	g++ -o main.exe PontoMap.o main.o

PontoMap.o: PontoMap.h PontoMap.cpp
	g++ -c PontoMap.cpp

main.o: PontoMap.o main.cpp
	g++ -c main.cpp

clean:
	rm *.o *.exe
