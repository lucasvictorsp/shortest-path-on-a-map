/* 
 * File:   PontoMap.h
 * Author: Lucas Victor es71512
 *
 * Created on 20 de Março de 2015, 15:01
 * modified on 18/04/2015
 */
#ifndef PONTOMAP_H
#define	PONTOMAP_H

#include <iostream>
#include <cmath>

using namespace std;

class PontoMap {
    private:
        int x, y, xPai, yPai;
        float custoP, valorHeuristico;  

    public:
        //construtores
        PontoMap(){} //construtor default
        PontoMap(int, int, float = HUGE_VAL, float = 0.0, int = -1, int = -1); // HUGE_VAL é uma constante da classe cmath que representa infinito
        PontoMap(const PontoMap &);

        //funcoes
            //gets:
        int getX() const;
        int getY() const;
        float getCustoP() const;
        float getValorHeuristico() const;
        int getXPai() const;
        int getYPai() const;

            //sets:
        void setX(int );
        void setY(int );
        void setCustoP(float );
        void setPai(int , int );
            //Calcula função Heuristica do A*
        void setValorHeuristico(const PontoMap & , int = 1);

            //sobrecarga dos operadors:
        PontoMap& operator=(const PontoMap &);
        bool operator==(const PontoMap &);
        bool operator!=(const PontoMap &);
        bool operator>(const PontoMap &);
        bool operator<(const PontoMap & );
        friend ostream& operator<<(ostream & , const PontoMap& );
        
            //imprime
        void imprime();
        
            //Destrutor
        ~PontoMap();
};

#endif	/* PONTOMAP_H */


