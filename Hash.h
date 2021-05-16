/* 
 * File:   Hash.h
 * Author: Lucas Victor
 * 
 * Created on 21 de Março de 2015
 * this creation was based on a class hash created by Marcus V. Andrade professor at UFV in 2014 
 */

#ifndef HASH_H
#define HASH_H

#include<iostream>
#include<string>
using namespace std;

#include "PontoMap.h"

#define TAM 65792 // 256 x 256 + 256 = 65792
#define largura 256

class Erro_Hash {
private:
    string msg;
public:

    Erro_Hash(const string &s) {
        msg = s;
    }

    string what() {
        return msg;
    }
};

class Hash {
    public:
        Hash(); // Construtor default

        // retorna um PontoMap que esta na posição (x * largura) + y da tabhash
        // caso nao exista este elemento, lanca uma excecao do tipo Erro_Hash.
        PontoMap& localiza(int x, int y);
        bool localiza_bol(int x, int y);

        // insere o elemento it na tabela na posição (x * largura) + y
        //tal que x e y são as coordenadas do PontoMap it e largura e uma constante definida acima
        //tendo em vista que a função hash criada é perfeita nunca ira ocorre uma colizão
        //contudo foi criado uma class erro, e então introduzimos este tratamente de excessão nesta função.
        void insere(PontoMap it) throw (Erro_Hash);

        // remove o elemento cuja chave é (x * largura) + y da tabela
        //caso tente remover um elemento que não existe(não se encontra na tabela) é lançada uma exceção.
        void remove(int x, int y) throw (Erro_Hash);


    private:

        PontoMap **tabhash;

        // funcao de transformação que retorna o endereco na tabela
        int fhash(int x, int y);
};

//função privada
int Hash::fhash(int x, int y) {
    int res = (x * largura) + y;
    return res; //Hash perfeito
}

Hash::Hash() {
    tabhash = new PontoMap*[TAM];
    for(int i = 0; i < TAM; i++)
        tabhash[i] = NULL;
}

PontoMap& Hash::localiza(int x, int y){
    int p = fhash(x, y);
    if (tabhash[p] != NULL){
        return *tabhash[p];
    }
    //else{
      //  return NULL;
    //}
}

bool Hash::localiza_bol(int x, int y) {
    int p = fhash(x, y);
    if (tabhash[p] != NULL){
        return true;
    }
    else{
        return false;
    }
}

void Hash::insere(PontoMap it) throw (Erro_Hash) {
    if(tabhash[fhash(it.getX(), it.getY())] == NULL)
        tabhash[fhash(it.getX(), it.getY())] = new PontoMap(it);
    else
        throw Erro_Hash("EM INSERE: Elemento já existe!");
}


void Hash::remove(int x, int y) throw (Erro_Hash) {
    if(tabhash[fhash(x, y)] != NULL)
        tabhash[fhash(x, y)] = NULL;
    else
        throw Erro_Hash("EM REMOVE: Elemento não encontrado!");
}
#endif