/* 
 * File:   Nodo.h
 * Author: Marcus V. Andrade (UFV)
 * Updated by Lucas Victor
 * 
 * Created on April 15, 2014 
 * Updated on March 19, 2015 
 */

class Nodo { 

friend class Lista<TipoItem>;
    
private:
    TipoItem item;
    Nodo *prox;

    Nodo() { prox = NULL; }

    Nodo (TipoItem a, Nodo *ptr=NULL)  {   // construtor 
	    item = a;
	    prox = ptr;
    }
};
