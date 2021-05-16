/* 
 * File:   PontoMap.cpp
 * Author: Lucas Victor
 * 
 * Created on 20 de Março de 2015
 * modified on 25/05/2015
 */

#include "PontoMap.h"

#define largura 256 //define a largura do map, é usado no setChave para criar um chave pro hash(chave única, hash perfeito

PontoMap::PontoMap(int x1, int y1, float cP, float vH, int xP, int yP):x(x1), y(y1), custoP(cP), valorHeuristico(vH), xPai(xP), yPai(yP){  }

        //contrutor de copia
PontoMap::PontoMap(const PontoMap &p){
    this->x = p.getX( );
    this->y = p.getY( );
    this->custoP = p.getCustoP( );
    this->valorHeuristico = p.getValorHeuristico();
    this->xPai = p.getXPai( );
    this->yPai = p.getYPai( );
}

//funções Gats:
    //getX: retorna o valor de x.
int PontoMap::getX( ) const{
    return x;
}


    //getY:retorna valor de y.
int PontoMap::getY( ) const{
    return y;
}

    //getCustoP: retorna valor do custo.
float PontoMap::getCustoP( ) const{
    return custoP;
}

float PontoMap::getValorHeuristico( ) const{
    return valorHeuristico;
}

int PontoMap::getXPai( ) const{
    return xPai;
}

int PontoMap::getYPai( ) const{
    return yPai;
}

//Funções set's
    //setX: modifica o valor de x.
void PontoMap::setX(int x){
    this->x = x;
}

    //setY: modifica o valor de y.
void PontoMap::setY(int y){
    this->y = y;
}

    //setCustoP: modifica o valor do custoP.
void PontoMap::setCustoP(float cP){
    this->custoP = cP;
}

void PontoMap::setPai(int x, int y){
    this->xPai = x;
    this->yPai = y;
}

void PontoMap::setValorHeuristico(const PontoMap& p, int w){
    float maior = max(abs(p.getX() - getX()), abs(p.getY() - getY()));
    
    float menor = min(abs(p.getX() - getX()), abs(p.getY() - getY()));
    
    valorHeuristico = w * (maior + (0.5 * menor));
}

//Sobrecarga de Operadores:
    //Sobrecarga do operador de comparação igual: verifica se dois PontosMap's são iguais.
    //para tal ele verifica apenas se as coordenas são iguais.
bool PontoMap::operator==(const PontoMap& p){
    return (this->x == p.getX( ) && this->y == p.getY( ));
}

    //sobrecarga do operador maior: verifica entre dois PontosMap's qual é maior.
    //para tal ele verifica o custo entre os dois.
bool PontoMap::operator>(const PontoMap& p){
    //return (this->custoP >= p.getCustoP( ));
    return ((this->custoP + this->valorHeuristico) >= (p.getCustoP( ) + p.getValorHeuristico( )));
}

    //Sobrecarga do operador de comparação diferente: verifica se dois PontosMap's são diferentes.
    //para tal ele verifica apenas se as coordenas são iguais.
bool PontoMap::operator!=(const PontoMap& p){
    return (this->x != p.getX( ) || this->y != p.getY( ));
}

    //sobrecarga do operador menor: verifica entre dois PontosMap's qual é o menor.
    //para tal ele verifica o custo entre os dois.
bool PontoMap::operator<(const PontoMap &p ){
    //return (this->custoP < p.getCustoP( ));
    return ((this->custoP + this->valorHeuristico) < (p.getCustoP( ) + p.getValorHeuristico( )));
}

    //sobrecarda do operador de atribuição: recebe um PontoMap em outro PontoMap, sendo q esses dois PontoMap's serão identicos.
PontoMap& PontoMap::operator=(const PontoMap &p){  
    if(this != &p){
        this->x = p.getX( );
        this->y = p.getY( );
        this->custoP = p.getCustoP( );
        this->valorHeuristico = p.getValorHeuristico( );
        this->xPai = p.getXPai();
        this->yPai = p.getYPai();
    }
    return *this;
}

//Função FRIEND da class PontoMap.
    //sobrecarga do operador<<:usado para que o copilador c++ reconheca a segunte linha de código.
    //cout << atual;       -->tal que atual é um PontoMap.
ostream& operator<<(ostream &os, const PontoMap &p){
    //os << "X: " << p.getX() << "\nY: " << p.getY() << "\nCusto: " << p.getCustoP() << endl;
    os << p.getX() << " " << p.getY() << " ";// << p.getCustoP() << " ";
    //os << "<" << p.getX() << ", " << p.getY() << ", " << p.getCustoP() << "> ";// << ", " << getValorHeuristico();
    return os;
}

//Função imprime: imprime as coordenas(x e y) de um PontoMAp e o seu custoP
void PontoMap::imprime( ){
    cout << "<" << getX() << ", " << getY() << ", " << getCustoP() << "> ";// << ", " << getValorHeuristico();
}

//Sabendo q minha classe ponto não trabalha comnenhuma matriz dinâmica, ou seja, não é necessario desalocar([]delete) nada, eu a criei para DEBUGR o erro de impressão do
//caminho otimo criado pelo algoritmo de dijkstra, pois usando a função(recursiva) camminho acima eu não conseguia a impressão do caminho ótimo, criando o destrutor e colocando
//e colocando um cout nele pude perceber que o copilador chamava o destrutor a cada interação do laço pois eu estava criando o pai dinâmicamente, vindto isso eu passei a setar
//o pai dentro da função dijkstra da seguinte forma(Ex.: aux1.setPaiPonteiro(new PontoMap(atual));) sendo aux1 e atual PontoMap's.
PontoMap::~PontoMap() {
 //DEBUG//cout << "Destruido." << endl;
}
