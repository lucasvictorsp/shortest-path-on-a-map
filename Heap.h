/*
+--------------------- File: Heap.h ---------------------+
|  Declaração e implementação de uma fila de prioridades |
|  genérica usando um Heap (máximo).                     |
|  O objeto usado na instanciação da classe deve incluir |
|  a sobrecarga do operador >                            |
|  Implementado em 15/04/14 por Marcus V. Andrade (UFV)  |
|  Atualizado em 21/03/15 por Lucas Victor               |
+--------------------------------------------------------+
*/

#ifndef Heap_H__
#define Heap_H__

#include <iostream>
#include <string>
using namespace std;

// Classe definida para tratar exce��es nas opera��es
class ErroHeap {
private:
	char msg[100];
public:
	ErroHeap (const char *s) { strcpy (msg, s); }
	char *what() { return msg; }
};/*

// Tamanho da area reservada para armazenar os elementos
const int MAX_SIZE = 100;

template <class T>
class Heap {
public:
	Heap ();                         // construtor default
	Heap (const Heap<T>&);   // construtor de c�pia

	Heap<T>& operator= (const Heap<T>& );

	void insere(T x);
	T remove();
	T topo();


	void Print(); // FUNCAO QUE SERA USADA APENAS PARA CONFERIR A SUA IMPLEMENTACAO

	~Heap ();         // destrutor
private:
	int num_elem;
	T *storage;

	bool isEmpty();
	bool isFull();

	// copia a Heap
	void copyHeap(const Heap<T> &h);

	// desloca (na descendente) o elemento da �posicao li
	void shiftDown(int li);

	// desloca (na ascendente) o elemento da �posicao li
	void shiftUp(int li);


};

/* ------------------------------------------------------+
|                FUNCOES INTERNAS                        |
+ -------------------------------------------------------+ */
template <class T>
bool Heap<T>::isEmpty() {
	return (num_elem == 0);
}

template <class T>
bool Heap<T>::isFull() {
	return (num_elem == MAX_SIZE);

}

template <class T>
void Heap<T>::copyHeap(const Heap<T> &h) {
	if (h.num_elem > 0)   // se heap nao vazia
		for (int i=1; i <= num_elem; i++)
			storage[i] = h.storage[i];
	num_elem = h.num_elem;
}

//
// Desloca o elemento que esta na primeira posicao do vetor, isto e, em
// storage[1] para a posicao onde o elemento satisfaca o criterio de
// Heap maximo
template <class T>
void Heap<T>::shiftDown(int li) {
	int i,j;
	T aux;

	i=li;
	j=2*i;
	aux = storage[i];
	while (j <= num_elem) {
		if ((j < num_elem) && (storage[j] < storage[j+1]))
           j++;
		if (aux > storage[j])
			break;
		storage[i] = storage[j];
		i=j;
		j=2*i;
	}
	storage[i]=aux;
}


	/*void corrigeDescendo(int index=1)
	{
		// Se index tem filho
		if (filhoE(index) < heap.size())
		{
			// Seleciona o filho com menor valor (esquerda ou direita?)
			int filho = filhoE(index);
			if (filhoD(index) < heap.size() && heap[filhoD(index)] < heap[filhoE(index)])
				filho = filhoD(index);

			// Se o valor do pai � menor do que o valor do menor filho, terminamos
			if (heap[index] < heap[filho])
				return;

			// Caso contr�rio, trocamos o pai com o filho no heap e corrigimos agora para o filho
			swap(heap[index], heap[filho]);
			corrigeDescendo(filho);
		}
	}//*/

//
// Esta funcao deve fazer o inverso da funcao shiftDown, isto e,
// deve deslocar o ultimo elemento que foi adicionado ao Heap para
// a posicao onde ele satisfaca o criterio de Heap maximo
//

/*template <class T>
void Heap<T>::shiftUp(int index) {
	//int i,j;
	T aux;

	i=li;
	j=i/2;
	//aux = storage[i];
		// Se index n�o � a raiz e o valor do index for menor do que o valor de seu pai,
		// troca seus valores (index e pai(index)) e corrige para o pai
		if (index > 1 && heap[index] < heap[pai(index)])
		{
			swap(heap[index], heap[pai(index)]);
			corrigeSubindo(pai(index));
		}
}//*/

template <class T>
void Heap<T>::shiftUp(int li) {
	int i,j;
	T aux;

	i=li;
	j=i/2;
	aux=storage[i];
	while (j >= 1) {
		if (aux > storage[j])
			break;
		storage[i] = storage[j];
		i=j;
		j=i/2;
	}
	storage[i]=aux;

}//*/


/* ------------------------------------------------------+
|                FUNCOES PUBLICAS                        |
+ -------------------------------------------------------+ */


template <class T>
Heap<T>::Heap () {
	storage = new T[MAX_SIZE+1];
	num_elem = 0;
}

template <class T>
Heap<T>::Heap (const Heap<T>& h) {
	this->copyHeap(h);
}

template <class T>
Heap<T>& Heap<T>::operator= (const Heap<T>& h) {
	if (this != &h)
		this->copyHeap(h);
	return *this;
}

//
// Retorna o elemento que esta no topo do Heao sem remove-lo
//
template <class T>
T Heap<T>::topo () {
	if (!isEmpty())
		return storage[num_elem];


	else
	throw ErroHeap("EM TOPO: *** Heap vazia ***");
}

//
// Insere um elemento no Heap, isto e, inclui o elemento em storage[num_elem+1],
// incrementa o numero de elementos e chama a funcao shiftUp para que a posicao
// dos elementos no Heap satisfacam o criterio de Heap maximo
template <class T>
void Heap<T>::insere(T x) {
	if (!isFull()) {
		num_elem++;
		storage[num_elem]=x;
		shiftUp(num_elem);
		//shiftDown(num_elem);
	}
	else
		throw ErroHeap("EM INSERE: *** Heap cheia ***");
}

//
// Remove o elemento que esta no topo do Heap e o retorna.
// Obs: a posicao dos elementos no Heap devem ser ajustadas para que o
// criterio de Heap maximo continue a ser satisfeito
//
template <class T>
T Heap<T>::remove() {
	if (! isEmpty()) {
		storage[1]=storage[num_elem];
		num_elem--;
		shiftDown(1);
		//shiftUp(1)
	}
	else
		throw ErroHeap("EM DEHeap: *** Heap vazia ***");
}

template <class T>
Heap<T>::~Heap() {
	delete [] storage;
}


//
// **********************************************************************
// A funcao Print sera criada nesta implementacao apenas para
// conferir se a sua implementacao das funcoes-membro estao corretas
//
// APOS A CONFERENCIA ELA DEVE SER REMOVIDA DA INTERFACE
// **********************************************************************
//
template <class T>
void Heap<T>::Print () {
	cout << "Heap = ";
	for (int i=1; i <= num_elem; i++)
		cout << storage[i] << "   ";
	cout << endl;
}


#endif
