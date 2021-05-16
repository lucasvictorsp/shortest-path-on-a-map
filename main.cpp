/* 
 * File:   main.cpp
 * Author: Lucas Victor
 * 
 * Created on 20 de Março de 2015
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include "PontoMap.h"
#include "Hash.h"
#include "Lista.h"

using namespace std;

void dijkstra(PontoMap, PontoMap, char **); //função que aplica o algoritmo de custo uniforme em um mapa e retorna o menor caminho entre 2 pontos deste mapa.

void Aestrela(PontoMap, PontoMap, char **); //função que aplica o algoritmo de custo uniforme em um mapa e retorna o menor caminho entre 2 pontos deste mapa.

void WAestrela(PontoMap, PontoMap, char **, int w); //função que aplica o algoritmo de custo uniforme em um mapa e retorna o menor caminho entre 2 pontos deste mapa.

int main() {
    int nlinhas, ncolunas;
    string mapa = "maps/", nameMap;
    cout << "Digite o nome do mapa (sem a extensao): ";
    cin >> nameMap;
    mapa += nameMap;
    mapa += ".map";

    string linha, aux; //cria uma string para guarda o que tem em casa linha do arquivo "arqNomes"


    ifstream arqMapa; //cria uma variavel do tipo ifstream para recebe um arquivo de leitura
    arqMapa.open(mapa.c_str(), ios::in); //abre o arquivo com o nome "arqMapa"
    if (arqMapa.fail()) { //verifica se a abertura foi feita corretamente, caso contrario ele apresenta uma mensagem...
        cerr << "Falha ao abrir\n"; //de erro na tela e returna 1 finaliando o programa.
        exit(1);
    }

    int i = 0;
    arqMapa >> linha; //lê do arquivo(string mapa) a primeira string e grava ela na string linha.
    arqMapa >> linha; //lê do arquivo(string mapa) a segunda string e grava ela na string linha(descartando o que tinha sido gravado antes nela).
    arqMapa >> linha; //lê do arquivo(string mapa) a terceira string e grava ela na string linha(descartando o que tinha sido gravado antes nela).	
    if (linha == "height") { //verifica se a terceira linha do arquivo(string mapa) é igual a strinf "height", caso sim executar:
        arqMapa >> linha; //lê do arquivo(string mapa) a quarta string e grava ela na string linha(descartando o que tinha sido gravado antes nela).

        //esta parte do codigo trasforma uma string em um int
        //como linha[i] é uma "caracter número", e na tabela ASCII os números são gravados em sequência, se fizermos a operação (linha[i] - '0') iremos obter exatemente o valor
        //deste "caracter numero" como um inteiro, se multplicamor ele por aux que é inicializada com valor 1 e a cada interação é multiplicado por 10, conseguiremos
        //criar um inteiro apartir da string linha.
        //OBS.: este código é semelhande a função stoi() do c++ que recebe como parâmetro uma string e a tranforma em um int.
        int t = linha.size(); //grava em t o tamanho da string linha.
        int result = 0; //cria uma variavel(auxiliar) inteira que recebe o valor zero.
        int aux = 1; //cria uma auxiliar que recebe o valor 1 (na primeira interação do for), essa auxiliar será usada para "ciar" as casas unidade, decimal, centena. 
        for (int i = (t - 1); i >= 0; i--) {
            result += (linha[i] - '0') * aux;
            aux *= 10;
        }
        nlinhas = result; //grava em nlinhas a valor de inteiro q corresponde a string linha, ou seja, guarda em nlinhas o tamanho da matriz.
    } //fim do código que transforma uma trings em inteiro.
    arqMapa >> linha; //lê do arquivo(string mapa) a guinta string do arquivo e grava ela na string linha(descartando o que tinha sido gravado antes nela).
    if (linha == "width") { //verifica se a terceira linha do arquivo(string mapa) é igual a strinf "width", caso sim executar:
        arqMapa >> linha; //lê do arquivo(string mapa) a quarta string e grava ela na string linha(descartando o que tinha sido gravado antes nela).

        //////mesmo cógido usado a cima(nas linhas 44 a 52)/////
        int t = linha.size();
        int result = 0;
        int aux = 1;
        for (int i = (t - 1); i >= 0; i--) {
            result += (linha[i] - '0') * aux;
            aux *= 10;
        }
        ncolunas = result; //grava em ncolunas a valor de inteiro q corresponde a string linha, ou seja, guarda em ncolunas a latgura da matriz.
    }

    //cria uma matriz dinâmica com os parametros lidos do carquivo, ou seja, a matriz tem numero de linhas = nlinhas e numero de colunas = ncolunas.
    char **mat = new char*[nlinhas];

    for (int i = 0; i < nlinhas; i++)
        mat[i] = new char[ncolunas];
    //fim da criação da matriz dinâmica.//

    while (arqMapa >> linha) {
        if (linha[1] == 46 || linha[1] == 64) {
            for (int j = 0; j < ncolunas; j++)
                mat[i][j] = linha[j];
            i++;
        }
    }

    arqMapa.close();


    clock_t time1, time2, time_diff; //variaveis da biblioteca ctime que foram criadas para guarda o tempo antes e depois da chama da função dijkstra e a variavel time_diff...
    //que ira receber a diferença entre tempo final e tempo inicial, ou seja, o tempo gasto para completar a realização do algoritmo de dijkstra.


    int xi, yi, xf, yf;
    PontoMap ini, fim;
    srand((unsigned) time(NULL)); //gera valores para a função hand atravez do tempo(hora).

    int qntW;
    cout << "Deseja testar quantos valores de W na funcao WA*: ";
    cin >> qntW;
    int w[qntW], wAux;
    cout << "Deseja cada um dos " << qntW << " valores de W, sendo que a cada entrada eh necessario dar ENTER:\n";
    for(int i = 0; i < qntW; i++){
        cin >> wAux;
        w[i] = wAux;
    }
    
    char op;
    while(op != 'd' && op != 'D' && op != 'r' && op != 'R'){
        cout << "Deseja digitar os dados ou crialos randomicamente(r ou R = randomico, d ou D = digitar): ";
        cin >> op;
            switch(op){
                case 'r':
                case 'R':
                {
                    /*do {
                        xi = rand() % 256;
                        yi = rand() % 256;
                    } while (mat[xi][yi] != '.');
                    do {
                        xf = rand() % 256;
                        yf = rand() % 256;
                    } while (mat[xf][yf] != '.');//*/
                    xi = 247;
                    yi = 32;
                    xf = 215;
                    yf = 34;
                    break;
                }
                case 'd':
                case 'D':
                {
                    cout << "Digite os dados do Ponto inicial:\nx: ";
                    cin >> xi;
                    cout << "y: ";
                    cin >> yi;
                    cout << "Digite os dados do ponto meta:\nx: ";
                    cin >> xf;
                    cout << "y: ";
                    cin >> yf;
                    break;
                }
                default:
                {
                    cout << "Opicao invalida." << endl;
                }
        }
    }

    cout << "\nO menor caminho (caminho otimo) é:\n";

    ini.setX(xi);
    ini.setY(yi);
    ini.setCustoP(0.0);

    fim.setX(xf);
    fim.setY(yf);
    fim.setCustoP(HUGE_VAL);

    cout << "\nDIJKSTRA:\n";
    time1 = clock() / (CLOCKS_PER_SEC / 1000); //obtem o horario (antes de iniciar o calculo).
    dijkstra(ini, fim, mat);
    time2 = clock() / (CLOCKS_PER_SEC / 1000); //obtem o horario (depois de calcular o calculo).
    time_diff = time2 - time1; //obtem a diferenca entre os tempos antes e depois em ms.
    cout << "\nTempo: " << time_diff << " ms\n" << endl; //imprime me tela o tempo gasto para executar o algoritmo de dijkstra.

    cout << "A*:\n";
    time1 = clock() / (CLOCKS_PER_SEC / 1000); //obtem o horario (antes de iniciar o calculo).
    Aestrela(ini, fim, mat);
    time2 = clock() / (CLOCKS_PER_SEC / 1000); //obtem o horario (depois de calcular o calculo).
    time_diff = time2 - time1; //obtem a diferenca entre os tempos antes e depois em ms.
    cout << "\nTempo: " << time_diff << " ms\n" << endl; //imprime me tela o tempo gasto para executar o algoritmo de dijkstra.

    for(int i = 0; i < qntW; i++){
        cout << "WA*: --> " << w[i] << "A*\n";
        time1 = clock() / (CLOCKS_PER_SEC / 1000); //obtem o horario (antes de iniciar o calculo).
        WAestrela(ini, fim, mat, w[i]);
        time2 = clock() / (CLOCKS_PER_SEC / 1000); //obtem o horario (depois de calcular o calculo).
        time_diff = time2 - time1; //obtem a diferenca entre os tempos antes e depois em ms.
        cout << "\nTempo: " << time_diff << " ms\n" << endl; //imprime me tela o tempo gasto para executar o algoritmo de dijkstra.
    }

    for (int i = 0; i < nlinhas; i++)
        delete []mat[i];
    delete []mat;

    return 0;
}

void dijkstra(PontoMap ini, PontoMap fim, char **mat) {
    PontoMap aux1, aux2; //cria dois PontoMap's que serão usados para guardar um ponto na lista aberta(aux1) e outro que será usado para comaprar o ponto atual e aux1(aux2).
    Hash fechado; //cria um Hash que ira guarda todos os PontoMap's que ja foram expandidos na busca pelo Ponto Meta.
    Lista<PontoMap> aberto; //cria uma lista que guarda ordenadamente pelo custo os pontos que deveram ser expandidos na busca pelo Meta.
    Lista<PontoMap>::RefLComp p; //um auxiliar que é usado para "trabalhar" com a Lista aberta.
    aberto.insere(ini); //insere o primeiro elemento, ou seja, o PontoMap inicial na lista aberta
    PontoMap atual; //cria um PontoMap atual, este PontoMap atual será o ponto atual que o algoritmo de dijkstra estara analisando.
    int i = 0; //variavel criada pra conta quantos pontos foram expandidos, ou seja, quantos pontos tem em fechado;

    //enquando o Ponto meta não tiver sido expandido e aberto não estiver vazio, ou seja, há a possibilidade de ainda chegar no meta(ainda a pontos a serem analizados)
    while (!aberto.EstaVazia() && !fechado.localiza_bol(fim.getX(), fim.getY())) {
        atual = aberto.recupera(aberto.primeiro()); //seta em atual o primeiro elemento da lista aberta
        aberto.remove(aberto.primeiro()); //remove o primeiro elemento da lista aberta.
        if (atual.getX() == fim.getX() && atual.getY() == fim.getY()) { //verifica se o ponto atual é igual o ponto meta, se for, o objetivo ja foi alcançado...executar: 
            fim.setCustoP(atual.getCustoP()); //seta o custo do PontoMap atual no PontoMap fim.
            cout << "<<Ponto Inicial>, <Ponto Final>, (Numero de nos expandidos)>: <<" << ini.getX() << ", " << ini.getY() << ", "
            << ini.getCustoP() << ">, <" << fim.getX() << ", " << fim.getY() << ", " << fim.getCustoP() << ">, (" << i << ")>\n";

            //Esta parte do código emprime o caminho
            PontoMap caminha = atual; //cria uma variavel PontoMap que vai caminha pelo caminho otimo de tras para frente
            PontoMap *caminho = new PontoMap[i]; //vetor dinamico que guarda o caminho otimo
            int b = 0; //auxilicar que vai ajudar a imprimir o vetor caminho de tras para frente, já que o caminho ótimo esta armazenado no vetor caminho de forma invertida
            caminho[b] = caminha; //seta a pisição final(meta) e, caminho na posição zero(b);
            while (!(caminha == ini) && (fechado.localiza_bol(caminha.getXPai(), caminha.getYPai()))) {//verifica se o pai de caminha esta em fechado e se caminha é diferente do ponto inicial, se for executar:  
                b++; //incrementa o auxiliar
                caminha = fechado.localiza(caminha.getXPai(), caminha.getYPai()); //recupera o pai de caminha em fechado e grava o mesmo em caminha
                caminho[b] = caminha; //grava gaminha no vetor caminho na posição b
            }

            while (b >= 0) { //enquanto b for maior ou igual a zer executar
                caminho[b].imprime(); //imprime o PontoMap que esta em caminho na posição b
                b--; //decrementa a uxiliar b
            }
            delete []caminho;
            //fim de imprime caminho

            break; //para o laço por o ponto meta ja foi encontrado.
        } else { //caso atual não seja igual ao ponto meta...executar: 

            ////////Movimento para a Direita////////
            if (((atual.getY() + 1) < 256) && (mat[atual.getX()][atual.getY() + 1] == '.') && (!fechado.localiza_bol(atual.getX(), (atual.getY() + 1)))) {//verifica se exite um ponto a direita de atual e se este no mapa é um '.' e também se ele não esta em fechado, se sim, execuar:
                aux1.setX(atual.getX()); //seta em aux1 o valor de atual.x(atual.getX())
                aux1.setY((atual.getY() + 1)); //seta em aux1 o valor de atual.y + 1(atual.getY() + 1)
                aux1.setCustoP(atual.getCustoP() + 1); //seta em aux1 o valor de atual.custoP + 1(atual.getCustoP() + 1)
                aux1.setPai(atual.getX(), atual.getY());
                if (aberto.procura_bol(aux1)) { //verifica se aux1 esta em aberto(custo O(n)), se sim, executar:
                    p = aberto.procura(aux1); //grava em RefLComp a referencia para o PontoMap aux1;
                    aux2 = aberto.recupera(p); //copia para aux2 o PontoMap aux1 encontrado em aberto
                    if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {//verifica se o custo de aux2(ou sej, aux1 encontrado em aberto) é menor que o novo valor de aux1, se for, executar:
                        aberto.remove(p); //remove aux2 da lista aberto
                        aberto.insereOrdenado(aux1); //insere aux1 com o novo valor do custo em aberto
                    }
                } else { //se aux1 não estiver em aberto, executar: 
                    aberto.insereOrdenado(aux1); //insere aux1 na lista aberta
                }
            }

            //todos os outros 7 cados, Inferios Direito, Supeior Direito, Baixo, Inferior Esquerdo, Esquerdo, Superior Esquerdo e para cima apresenta implementação semelhante
            //tratanto os mesmo cados, mudando apenas os pontos testados
            //contudo sempre que o algoritmo vai andar em uma diagonal ele verifica se nas esquinas não existe parede(no nosso casso um '@'), esta verificação foi feita para
            //deixa o algoritmo mais realistico.

            ////////Movimento Inferior Direito////////
            if (((atual.getX() + 1) < 256) && ((atual.getY() + 1) < 256) && (mat[(atual.getX() + 1)][atual.getY() + 1] == '.') && (!fechado.localiza_bol((atual.getX() + 1), (atual.getY() + 1)))) {
                if ((mat[atual.getX()][(atual.getY() + 1)] == '.') && (mat[(atual.getX() + 1)][atual.getY()] == '.')) {
                    aux1.setX((atual.getX() + 1));
                    aux1.setY((atual.getY() + 1));
                    aux1.setCustoP(atual.getCustoP() + 1.5);
                    aux1.setPai(atual.getX(), atual.getY());
                    if (aberto.procura_bol(aux1)) {
                        p = aberto.procura(aux1);
                        aux2 = aberto.recupera(p);
                        if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                            aberto.remove(p);
                            aberto.insereOrdenado(aux1);
                        }
                    } else {
                        aberto.insereOrdenado(aux1);
                    }
                }
            }

            ////////Movimento Superior Direito////////

            if (((atual.getX() - 1) >= 0) && ((atual.getY() + 1) < 256) && (mat[atual.getX() - 1][atual.getY() + 1] == '.') && (!fechado.localiza_bol((atual.getX() - 1), (atual.getY() + 1)))) {
                if ((mat[atual.getX()][(atual.getY() + 1)] == '.') && (mat[(atual.getX() - 1)][atual.getY()] == '.')) {
                    aux1.setX((atual.getX() - 1));
                    aux1.setY((atual.getY() + 1));
                    aux1.setCustoP(atual.getCustoP() + 1.5);
                    aux1.setPai(atual.getX(), atual.getY());
                    if (aberto.procura_bol(aux1)) {
                        p = aberto.procura(aux1);
                        aux2 = aberto.recupera(p);
                        if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                            aberto.remove(p);
                            aberto.insereOrdenado(aux1);
                        }
                    } else {
                        aberto.insereOrdenado(aux1);
                    }
                }
            }

            ////////Movimento para Baixo////////
            if (((atual.getX() + 1) < 256) && mat[atual.getX() + 1][atual.getY()] == '.' && !fechado.localiza_bol((atual.getX() + 1), atual.getY())) {
                aux1.setX((atual.getX() + 1));
                aux1.setY(atual.getY());
                aux1.setCustoP(atual.getCustoP() + 1);
                aux1.setPai(atual.getX(), atual.getY());
                if (aberto.procura_bol(aux1)) {
                    p = aberto.procura(aux1);
                    aux2 = aberto.recupera(p);
                    if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                        aberto.remove(p);
                        aberto.insereOrdenado(aux1);
                    }
                } else {
                    aberto.insereOrdenado(aux1);
                }
            }

            ////////Movimento Inferior Esquerdo////////
            if (((atual.getX() + 1) < 256) && ((atual.getY() - 1) >= 0) && mat[atual.getX() + 1][atual.getY() - 1] == '.' && !fechado.localiza_bol((atual.getX() + 1), (atual.getY() - 1))) {
                if ((mat[atual.getX()][(atual.getY() - 1)] == '.') && (mat[(atual.getX() + 1)][atual.getY()] == '.')) {
                    aux1.setX((atual.getX() + 1));
                    aux1.setY((atual.getY() - 1));
                    aux1.setCustoP(atual.getCustoP() + 1.5);
                    aux1.setPai(atual.getX(), atual.getY());
                    if (aberto.procura_bol(aux1)) {
                        p = aberto.procura(aux1);
                        aux2 = aberto.recupera(p);
                        if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                            aberto.remove(p);
                            aberto.insereOrdenado(aux1);
                        }
                    } else {
                        aberto.insereOrdenado(aux1);
                    }
                }
            }

            ////////Movimento para a Esquerda////////
            if (((atual.getY() - 1) >= 0) && (mat[atual.getX()][atual.getY() - 1] == '.') && !fechado.localiza_bol(atual.getX(), (atual.getY() - 1))) {
                aux1.setX(atual.getX());
                aux1.setY((atual.getY() - 1));
                aux1.setCustoP(atual.getCustoP() + 1);
                aux1.setPai(atual.getX(), atual.getY());
                if (aberto.procura_bol(aux1)) {
                    p = aberto.procura(aux1);
                    aux2 = aberto.recupera(p);
                    if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                        aberto.remove(p);
                        aberto.insereOrdenado(aux1);
                    }
                } else {
                    aberto.insereOrdenado(aux1);
                }
            }

            ////////Movimento Superior Esquerdo////////
            if (((atual.getX() - 1) >= 0) && ((atual.getY() - 1) >= 0) && (mat[atual.getX() - 1][atual.getY() - 1] == '.') && !fechado.localiza_bol((atual.getX() - 1), (atual.getY() - 1))) {
                if ((mat[atual.getX()][(atual.getY() - 1)] == '.') && (mat[(atual.getX() - 1)][atual.getY()] == '.')) {
                    aux1.setX((atual.getX() - 1));
                    aux1.setY((atual.getY() - 1));
                    aux1.setCustoP(atual.getCustoP() + 1.5);
                    aux1.setPai(atual.getX(), atual.getY());
                    if (aberto.procura_bol(aux1)) {
                        p = aberto.procura(aux1);
                        aux2 = aberto.recupera(p);
                        if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                            aberto.remove(p);
                            aberto.insereOrdenado(aux1);
                        }
                    } else {
                        aberto.insereOrdenado(aux1);
                    }
                }
            }

            ////////Movimento para Cima////////
            if ((atual.getX() - 1) >= 0 && mat[atual.getX() - 1][atual.getY()] == '.' && !fechado.localiza_bol((atual.getX() - 1), atual.getY())) {
                aux1.setX((atual.getX() - 1));
                aux1.setY(atual.getY());
                aux1.setCustoP(atual.getCustoP() + 1);
                aux1.setPai(atual.getX(), atual.getY());
                if (aberto.procura_bol(aux1)) {
                    p = aberto.procura(aux1);
                    aux2 = aberto.recupera(p);
                    if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                        aberto.remove(p);
                        aberto.insereOrdenado(aux1);
                    }
                } else {
                    aberto.insereOrdenado(aux1);
                }
            }
        }
        fechado.insere(atual); //depois que atual ja foi todo expandido, inserir atua em fechado
        i++; //incrementa o numero de nós expandidos

        //caso o ponto inicial e final escolhido não sejam interligados, ou seja, caso seja impossivel encontra um caminho q ligue os dois
        //o algoritmo vai exibir em tela esta mensagem apresentar os pontos e seus respectivos custo, neste caso o custo inicial é zero e o custo do meta e infinito
        if (aberto.EstaVazia()) { //caso a lista aberta esvazia sem que o meta seja encontrado, executar:

            cout << "Eh impossivel chegar neste ponto Meta." << endl;
            cout << "Ponto Inicial:" << "(" << ini << " " << ini.getCustoP() << ")";
            cout << "\nPonto Final:" << "(" << fim << fim.getCustoP() << ")" << flush;
        }
    }
}

void Aestrela(PontoMap ini, PontoMap fim, char **mat) {
    PontoMap aux1, aux2; //cria dois PontoMap's que serão usados para guardar um ponto na lista aberta(aux1) e outro que será usado para comaprar o ponto atual e aux1(aux2).
    Hash fechado; //cria um Hash que ira guarda todos os PontoMap's que ja foram expandidos na busca pelo Ponto Meta.
    Lista<PontoMap> aberto; //cria uma lista que guarda ordenadamente pelo custo os pontos que deveram ser expandidos na busca pelo Meta.
    Lista<PontoMap>::RefLComp p; //um auxiliar que é usado para "trabalhar" com a Lista aberta.
    aberto.insere(ini); //insere o primeiro elemento, ou seja, o PontoMap inicial na lista aberta
    PontoMap atual; //cria um PontoMap atual, este PontoMap atual será o ponto atual que o algoritmo de dijkstra estara analisando.
    int i = 0; //variavel criada pra conta quantos pontos foram expandidos, ou seja, quantos pontos tem em fechado;

    //enquando o Ponto meta não tiver sido expandido e aberto não estiver vazio, ou seja, há a possibilidade de ainda chegar no meta(ainda a pontos a serem analizados)
    while (!aberto.EstaVazia() && !fechado.localiza_bol(fim.getX(), fim.getY())) {
        atual = aberto.recupera(aberto.primeiro()); //seta em atual o primeiro elemento da lista aberta
        aberto.remove(aberto.primeiro()); //remove o primeiro elemento da lista aberta.
        if (atual.getX() == fim.getX() && atual.getY() == fim.getY()) { //verifica se o ponto atual é igual o ponto meta, se for, o objetivo ja foi alcançado...executar: 
            fim.setCustoP(atual.getCustoP()); //seta o custo do PontoMap atual no PontoMap fim.
            cout << "<<Ponto Inicial>, <Ponto Final>, (Numero de nos expandidos)>: <<" << ini.getX() << ", " << ini.getY() << ", "
            << ini.getCustoP() << ">, <" << fim.getX() << ", " << fim.getY() << ", " << fim.getCustoP() << ">, (" << i << ")>\n";

            //Esta parte do código emprime o caminho
            PontoMap caminha = atual; //cria uma variavel PontoMap que vai caminha pelo caminho otimo de tras para frente
            PontoMap *caminho = new PontoMap[i]; //vetor dinamico que guarda o caminho otimo
            int b = 0; //auxilicar que vai ajudar a imprimir o vetor caminho de tras para frente, já que o caminho ótimo esta armazenado no vetor caminho de forma invertida
            caminho[b] = caminha; //seta a pisição final(meta) e, caminho na posição zero(b);
            while (!(caminha == ini) && (fechado.localiza_bol(caminha.getXPai(), caminha.getYPai()))) {//verifica se o pai de caminha esta em fechado e se caminha é diferente do ponto inicial, se for executar:  
                b++; //incrementa o auxiliar
                caminha = fechado.localiza(caminha.getXPai(), caminha.getYPai()); //recupera o pai de caminha em fechado e grava o mesmo em caminha
                caminho[b] = caminha; //grava gaminha no vetor caminho na posição b
            }

            while (b >= 0) { //enquanto b for maior ou igual a zer executar
                caminho[b].imprime(); //imprime o PontoMap que esta em caminho na posição b
                b--; //decrementa a uxiliar b
            }
            delete []caminho;
            //fim de imprime caminho

            break; //para o laço por o ponto meta ja foi encontrado.
        } else { //caso atual não seja igual ao ponto meta...executar: 

            ////////Movimento para a Direita////////
            if (((atual.getY() + 1) < 256) && (mat[atual.getX()][atual.getY() + 1] == '.') && (!fechado.localiza_bol(atual.getX(), (atual.getY() + 1)))) {//verifica se exite um ponto a direita de atual e se este no mapa é um '.' e também se ele não esta em fechado, se sim, execuar:
                aux1.setX(atual.getX()); //seta em aux1 o valor de atual.x(atual.getX())
                aux1.setY((atual.getY() + 1)); //seta em aux1 o valor de atual.y + 1(atual.getY() + 1)
                aux1.setCustoP(atual.getCustoP() + 1); //seta em aux1 o valor de atual.custoP + 1(atual.getCustoP() + 1)
                aux1.setValorHeuristico(fim);
                aux1.setPai(atual.getX(), atual.getY());
                if (aberto.procura_bol(aux1)) { //verifica se aux1 esta em aberto(custo O(n)), se sim, executar:
                    p = aberto.procura(aux1); //grava em RefLComp a referencia para o PontoMap aux1;
                    aux2 = aberto.recupera(p); //copia para aux2 o PontoMap aux1 encontrado em aberto
                    if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {//verifica se o custo de aux2(ou sej, aux1 encontrado em aberto) é menor que o novo valor de aux1, se for, executar:
                        aberto.remove(p); //remove aux2 da lista aberto
                        aberto.insereOrdenado(aux1); //insere aux1 com o novo valor do custo em aberto
                    }
                } else { //se aux1 não estiver em aberto, executar: 
                    aberto.insereOrdenado(aux1); //insere aux1 na lista aberta
                }

            }

            //todos os outros 7 cados, Inferios Direito, Supeior Direito, Baixo, Inferior Esquerdo, Esquerdo, Superior Esquerdo e para cima apresenta implementação semelhante
            //tratanto os mesmo cados, mudando apenas os pontos testados
            //contudo sempre que o algoritmo vai andar em uma diagonal ele verifica se nas esquinas não existe parede(no nosso casso um '@'), esta verificação foi feita para
            //deixa o algoritmo mais realistico.

            ////////Movimento Inferior Direito////////
            if (((atual.getX() + 1) < 256) && ((atual.getY() + 1) < 256) && (mat[(atual.getX() + 1)][atual.getY() + 1] == '.') && (!fechado.localiza_bol((atual.getX() + 1), (atual.getY() + 1)))) {
                if ((mat[atual.getX()][(atual.getY() + 1)] == '.') && (mat[(atual.getX() + 1)][atual.getY()] == '.')) {
                    aux1.setX((atual.getX() + 1));
                    aux1.setY((atual.getY() + 1));
                    aux1.setCustoP(atual.getCustoP() + 1.5);
                    aux1.setValorHeuristico(fim);
                    aux1.setPai(atual.getX(), atual.getY());
                    if (aberto.procura_bol(aux1)) {
                        p = aberto.procura(aux1);
                        aux2 = aberto.recupera(p);
                        if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                            aberto.remove(p);
                            aberto.insereOrdenado(aux1);
                        }
                    } else {
                        aberto.insereOrdenado(aux1);
                    }

                }
            }

            ////////Movimento Superior Direito////////
            if (((atual.getX() - 1) >= 0) && ((atual.getY() + 1) < 256) && (mat[atual.getX() - 1][atual.getY() + 1] == '.') && (!fechado.localiza_bol((atual.getX() - 1), (atual.getY() + 1)))) {
                if ((mat[atual.getX()][(atual.getY() + 1)] == '.') && (mat[(atual.getX() - 1)][atual.getY()] == '.')) {
                    aux1.setX((atual.getX() - 1));
                    aux1.setY((atual.getY() + 1));
                    aux1.setCustoP(atual.getCustoP() + 1.5);
                    aux1.setValorHeuristico(fim);
                    aux1.setPai(atual.getX(), atual.getY());
                    if (aberto.procura_bol(aux1)) {
                        p = aberto.procura(aux1);
                        aux2 = aberto.recupera(p);
                        if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                            aberto.remove(p);
                            aberto.insereOrdenado(aux1);
                        }
                    } else {
                        aberto.insereOrdenado(aux1);
                    }
                }
            }

            ////////Movimento para Baixo////////
            if (((atual.getX() + 1) < 256) && (mat[atual.getX() + 1][atual.getY()] == '.') && (!fechado.localiza_bol((atual.getX() + 1), atual.getY()))) {
                aux1.setX((atual.getX() + 1));
                aux1.setY(atual.getY());
                aux1.setCustoP(atual.getCustoP() + 1);
                aux1.setValorHeuristico(fim);
                aux1.setPai(atual.getX(), atual.getY());
                if (aberto.procura_bol(aux1)) {
                    p = aberto.procura(aux1);
                    aux2 = aberto.recupera(p);
                    if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                        aberto.remove(p);
                        aberto.insereOrdenado(aux1);
                    }
                } else {
                    aberto.insereOrdenado(aux1);
                }
            }

            ////////Movimento Inferior Esquerdo////////
            if (((atual.getX() + 1) < 256) && ((atual.getY() - 1) >= 0) && (mat[atual.getX() + 1][atual.getY() - 1] == '.') && (!fechado.localiza_bol((atual.getX() + 1), (atual.getY() - 1)))) {
                if ((mat[atual.getX()][(atual.getY() - 1)] == '.') && (mat[(atual.getX() + 1)][atual.getY()] == '.')) {
                    aux1.setX((atual.getX() + 1));
                    aux1.setY((atual.getY() - 1));
                    aux1.setCustoP(atual.getCustoP() + 1.5);
                    aux1.setValorHeuristico(fim);
                    aux1.setPai(atual.getX(), atual.getY());
                    if (aberto.procura_bol(aux1)) {
                        p = aberto.procura(aux1);
                        aux2 = aberto.recupera(p);
                        if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                            aberto.remove(p);
                            aberto.insereOrdenado(aux1);
                        }
                    } else {
                        aberto.insereOrdenado(aux1);
                    }
                }
            }

            ////////Movimento para a Esquerda////////
            if (((atual.getY() - 1) >= 0) && (mat[atual.getX()][atual.getY() - 1] == '.') && (!fechado.localiza_bol(atual.getX(), (atual.getY() - 1)))) {
                aux1.setX(atual.getX());
                aux1.setY((atual.getY() - 1));
                aux1.setCustoP(atual.getCustoP() + 1);
                aux1.setValorHeuristico(fim);
                aux1.setPai(atual.getX(), atual.getY());
                if (aberto.procura_bol(aux1)) {
                    p = aberto.procura(aux1);
                    aux2 = aberto.recupera(p);
                    if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                        aberto.remove(p);
                        aberto.insereOrdenado(aux1);
                    }
                } else {
                    aberto.insereOrdenado(aux1);
                }
            }

            ////////Movimento Superior Esquerdo////////
            if (((atual.getX() - 1) >= 0) && ((atual.getY() - 1) >= 0) && (mat[atual.getX() - 1][atual.getY() - 1] == '.') && (!fechado.localiza_bol((atual.getX() - 1), (atual.getY() - 1)))) {
                if ((mat[atual.getX()][(atual.getY() - 1)] == '.') && (mat[(atual.getX() - 1)][atual.getY()] == '.')) {
                    aux1.setX((atual.getX() - 1));
                    aux1.setY((atual.getY() - 1));
                    aux1.setCustoP(atual.getCustoP() + 1.5);
                    aux1.setValorHeuristico(fim);
                    aux1.setPai(atual.getX(), atual.getY());
                    if (aberto.procura_bol(aux1)) {
                        p = aberto.procura(aux1);
                        aux2 = aberto.recupera(p);
                        if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                            aberto.remove(p);
                            aberto.insereOrdenado(aux1);
                        }
                    } else {
                        aberto.insereOrdenado(aux1);
                    }
                }
            }

            ////////Movimento para Cima////////
            if ((atual.getX() - 1) >= 0 && (mat[atual.getX() - 1][atual.getY()] == '.') && (!fechado.localiza_bol((atual.getX() - 1), atual.getY()))) {
                aux1.setX((atual.getX() - 1));
                aux1.setY(atual.getY());
                aux1.setCustoP(atual.getCustoP() + 1);
                aux1.setValorHeuristico(fim);
                aux1.setPai(atual.getX(), atual.getY());
                if (aberto.procura_bol(aux1)) {
                    p = aberto.procura(aux1);
                    aux2 = aberto.recupera(p);
                    if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                        aberto.remove(p);
                        aberto.insereOrdenado(aux1);
                    }
                } else {
                    aberto.insereOrdenado(aux1);
                }
            }
        }
        fechado.insere(atual); //depois que atual ja foi todo expandido, inserir atua em fechado
        i++; //incrementa o numero de nós expandidos

        //caso o ponto inicial e final escolhido não sejam interligados, ou seja, caso seja impossivel encontra um caminho q ligue os dois
        //o algoritmo vai exibir em tela esta mensagem apresentar os pontos e seus respectivos custo, neste caso o custo inicial é zero e o custo do meta e infinito
        if (aberto.EstaVazia()) { //caso a lista aberta esvazia sem que o meta seja encontrado, executar:

            cout << "Eh impossivel chegar neste ponto Meta." << endl;
            cout << "Ponto Inicial:" << "(" << ini << " " << ini.getCustoP() << ")";
            cout << "\nPonto Final:" << "(" << fim << fim.getCustoP() << ")" << flush;
        }
    }
}

void WAestrela(PontoMap ini, PontoMap fim, char **mat, int w) {
    PontoMap aux1, aux2; //cria dois PontoMap's que serão usados para guardar um ponto na lista aberta(aux1) e outro que será usado para comaprar o ponto atual e aux1(aux2).
    Hash fechado; //cria um Hash que ira guarda todos os PontoMap's que ja foram expandidos na busca pelo Ponto Meta.
    Lista<PontoMap> aberto; //cria uma lista que guarda ordenadamente pelo custo os pontos que deveram ser expandidos na busca pelo Meta.
    Lista<PontoMap>::RefLComp p; //um auxiliar que é usado para "trabalhar" com a Lista aberta.
    aberto.insere(ini); //insere o primeiro elemento, ou seja, o PontoMap inicial na lista aberta
    PontoMap atual; //cria um PontoMap atual, este PontoMap atual será o ponto atual que o algoritmo de dijkstra estara analisando.
    int i = 0; //variavel criada pra conta quantos pontos foram expandidos, ou seja, quantos pontos tem em fechado;

    //enquando o Ponto meta não tiver sido expandido e aberto não estiver vazio, ou seja, há a possibilidade de ainda chegar no meta(ainda a pontos a serem analizados)
    while (!aberto.EstaVazia() && !fechado.localiza_bol(fim.getX(), fim.getY())) {
        atual = aberto.recupera(aberto.primeiro()); //seta em atual o primeiro elemento da lista aberta
        aberto.remove(aberto.primeiro()); //remove o primeiro elemento da lista aberta.
        if (atual.getX() == fim.getX() && atual.getY() == fim.getY()) { //verifica se o ponto atual é igual o ponto meta, se for, o objetivo ja foi alcançado...executar: 
            fim.setCustoP(atual.getCustoP()); //seta o custo do PontoMap atual no PontoMap fim.
            cout << "<<Ponto Inicial>, <Ponto Final>, (Numero de nos expandidos)>: <<" << ini.getX() << ", " << ini.getY() << ", "
            << ini.getCustoP() << ">, <" << fim.getX() << ", " << fim.getY() << ", " << fim.getCustoP() << ">, (" << i << ")>\n";

            //Esta parte do código emprime o caminho
            PontoMap caminha = atual; //cria uma variavel PontoMap que vai caminha pelo caminho otimo de tras para frente
            PontoMap *caminho = new PontoMap[i]; //vetor dinamico que guarda o caminho otimo
            int b = 0; //auxilicar que vai ajudar a imprimir o vetor caminho de tras para frente, já que o caminho ótimo esta armazenado no vetor caminho de forma invertida
            caminho[b] = caminha; //seta a pisição final(meta) e, caminho na posição zero(b);
            while (!(caminha == ini) && (fechado.localiza_bol(caminha.getXPai(), caminha.getYPai()))) {//verifica se o pai de caminha esta em fechado e se caminha é diferente do ponto inicial, se for executar:  
                b++; //incrementa o auxiliar
                caminha = fechado.localiza(caminha.getXPai(), caminha.getYPai()); //recupera o pai de caminha em fechado e grava o mesmo em caminha
                caminho[b] = caminha; //grava gaminha no vetor caminho na posição b
            }

            while (b >= 0) { //enquanto b for maior ou igual a zer executar
                caminho[b].imprime(); //imprime o PontoMap que esta em caminho na posição b
                b--; //decrementa a uxiliar b
            }
            delete []caminho;
            //fim de imprime caminho

            break; //para o laço por o ponto meta ja foi encontrado.
        } else { //caso atual não seja igual ao ponto meta...executar: 

            ////////Movimento para a Direita////////
            if (((atual.getY() + 1) < 256) && (mat[atual.getX()][atual.getY() + 1] == '.') && (!fechado.localiza_bol(atual.getX(), (atual.getY() + 1)))) {//verifica se exite um ponto a direita de atual e se este no mapa é um '.' e também se ele não esta em fechado, se sim, execuar:
                aux1.setX(atual.getX()); //seta em aux1 o valor de atual.x(atual.getX())
                aux1.setY((atual.getY() + 1)); //seta em aux1 o valor de atual.y + 1(atual.getY() + 1)
                aux1.setCustoP(atual.getCustoP() + 1); //seta em aux1 o valor de atual.custoP + 1(atual.getCustoP() + 1)
                aux1.setValorHeuristico(fim, w);
                aux1.setPai(atual.getX(), atual.getY());
                if (aberto.procura_bol(aux1)) { //verifica se aux1 esta em aberto(custo O(n)), se sim, executar:
                    p = aberto.procura(aux1); //grava em RefLComp a referencia para o PontoMap aux1;
                    aux2 = aberto.recupera(p); //copia para aux2 o PontoMap aux1 encontrado em aberto
                    if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {//verifica se o custo de aux2(ou sej, aux1 encontrado em aberto) é menor que o novo valor de aux1, se for, executar:
                        aberto.remove(p); //remove aux2 da lista aberto
                        aberto.insereOrdenado(aux1); //insere aux1 com o novo valor do custo em aberto
                    }
                } else { //se aux1 não estiver em aberto, executar: 
                    aberto.insereOrdenado(aux1); //insere aux1 na lista aberta
                }

            }

            //todos os outros 7 cados, Inferios Direito, Supeior Direito, Baixo, Inferior Esquerdo, Esquerdo, Superior Esquerdo e para cima apresenta implementação semelhante
            //tratanto os mesmo cados, mudando apenas os pontos testados
            //contudo sempre que o algoritmo vai andar em uma diagonal ele verifica se nas esquinas não existe parede(no nosso casso um '@'), esta verificação foi feita para
            //deixa o algoritmo mais realistico.

            ////////Movimento Inferior Direito////////
            if (((atual.getX() + 1) < 256) && ((atual.getY() + 1) < 256) && (mat[(atual.getX() + 1)][atual.getY() + 1] == '.') && (!fechado.localiza_bol((atual.getX() + 1), (atual.getY() + 1)))) {
                if ((mat[atual.getX()][(atual.getY() + 1)] == '.') && (mat[(atual.getX() + 1)][atual.getY()] == '.')) {
                    aux1.setX((atual.getX() + 1));
                    aux1.setY((atual.getY() + 1));
                    aux1.setCustoP(atual.getCustoP() + 1.5);
                    aux1.setValorHeuristico(fim, w);
                    aux1.setPai(atual.getX(), atual.getY());
                    if (aberto.procura_bol(aux1)) {
                        p = aberto.procura(aux1);
                        aux2 = aberto.recupera(p);
                        if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                            aberto.remove(p);
                            aberto.insereOrdenado(aux1);
                        }
                    } else {
                        aberto.insereOrdenado(aux1);
                    }

                }
            }

            ////////Movimento Superior Direito////////
            if (((atual.getX() - 1) >= 0) && ((atual.getY() + 1) < 256) && (mat[atual.getX() - 1][atual.getY() + 1] == '.') && (!fechado.localiza_bol((atual.getX() - 1), (atual.getY() + 1)))) {
                if ((mat[atual.getX()][(atual.getY() + 1)] == '.') && (mat[(atual.getX() - 1)][atual.getY()] == '.')) {
                    aux1.setX((atual.getX() - 1));
                    aux1.setY((atual.getY() + 1));
                    aux1.setCustoP(atual.getCustoP() + 1.5);
                    aux1.setValorHeuristico(fim, w);
                    aux1.setPai(atual.getX(), atual.getY());
                    if (aberto.procura_bol(aux1)) {
                        p = aberto.procura(aux1);
                        aux2 = aberto.recupera(p);
                        if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                            aberto.remove(p);
                            aberto.insereOrdenado(aux1);
                        }
                    } else {
                        aberto.insereOrdenado(aux1);
                    }
                }
            }

            ////////Movimento para Baixo////////
            if (((atual.getX() + 1) < 256) && (mat[atual.getX() + 1][atual.getY()] == '.') && (!fechado.localiza_bol((atual.getX() + 1), atual.getY()))) {
                aux1.setX((atual.getX() + 1));
                aux1.setY(atual.getY());
                aux1.setCustoP(atual.getCustoP() + 1);
                aux1.setValorHeuristico(fim, w);
                aux1.setPai(atual.getX(), atual.getY());
                if (aberto.procura_bol(aux1)) {
                    p = aberto.procura(aux1);
                    aux2 = aberto.recupera(p);
                    if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                        aberto.remove(p);
                        aberto.insereOrdenado(aux1);
                    }
                } else {
                    aberto.insereOrdenado(aux1);
                }
            }

            ////////Movimento Inferior Esquerdo////////
            if (((atual.getX() + 1) < 256) && ((atual.getY() - 1) >= 0) && (mat[atual.getX() + 1][atual.getY() - 1] == '.') && (!fechado.localiza_bol((atual.getX() + 1), (atual.getY() - 1)))) {
                if ((mat[atual.getX()][(atual.getY() - 1)] == '.') && (mat[(atual.getX() + 1)][atual.getY()] == '.')) {
                    aux1.setX((atual.getX() + 1));
                    aux1.setY((atual.getY() - 1));
                    aux1.setCustoP(atual.getCustoP() + 1.5);
                    aux1.setValorHeuristico(fim, w);
                    aux1.setPai(atual.getX(), atual.getY());
                    if (aberto.procura_bol(aux1)) {
                        p = aberto.procura(aux1);
                        aux2 = aberto.recupera(p);
                        if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                            aberto.remove(p);
                            aberto.insereOrdenado(aux1);
                        }
                    } else {
                        aberto.insereOrdenado(aux1);
                    }
                }
            }

            ////////Movimento para a Esquerda////////
            if (((atual.getY() - 1) >= 0) && (mat[atual.getX()][atual.getY() - 1] == '.') && (!fechado.localiza_bol(atual.getX(), (atual.getY() - 1)))) {
                aux1.setX(atual.getX());
                aux1.setY((atual.getY() - 1));
                aux1.setCustoP(atual.getCustoP() + 1);
                aux1.setValorHeuristico(fim, w);
                aux1.setPai(atual.getX(), atual.getY());
                if (aberto.procura_bol(aux1)) {
                    p = aberto.procura(aux1);
                    aux2 = aberto.recupera(p);
                    if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                        aberto.remove(p);
                        aberto.insereOrdenado(aux1);
                    }
                } else {
                    aberto.insereOrdenado(aux1);
                }
            }

            ////////Movimento Superior Esquerdo////////
            if (((atual.getX() - 1) >= 0) && ((atual.getY() - 1) >= 0) && (mat[atual.getX() - 1][atual.getY() - 1] == '.') && (!fechado.localiza_bol((atual.getX() - 1), (atual.getY() - 1)))) {
                if ((mat[atual.getX()][(atual.getY() - 1)] == '.') && (mat[(atual.getX() - 1)][atual.getY()] == '.')) {
                    aux1.setX((atual.getX() - 1));
                    aux1.setY((atual.getY() - 1));
                    aux1.setCustoP(atual.getCustoP() + 1.5);
                    aux1.setValorHeuristico(fim, w);
                    aux1.setPai(atual.getX(), atual.getY());
                    if (aberto.procura_bol(aux1)) {
                        p = aberto.procura(aux1);
                        aux2 = aberto.recupera(p);
                        if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                            aberto.remove(p);
                            aberto.insereOrdenado(aux1);
                        }
                    } else {
                        aberto.insereOrdenado(aux1);
                    }
                }
            }

            ////////Movimento para Cima////////
            if ((atual.getX() - 1) >= 0 && (mat[atual.getX() - 1][atual.getY()] == '.') && (!fechado.localiza_bol((atual.getX() - 1), atual.getY()))) {
                aux1.setX((atual.getX() - 1));
                aux1.setY(atual.getY());
                aux1.setCustoP(atual.getCustoP() + 1);
                aux1.setValorHeuristico(fim, w);
                aux1.setPai(atual.getX(), atual.getY());
                if (aberto.procura_bol(aux1)) {
                    p = aberto.procura(aux1);
                    aux2 = aberto.recupera(p);
                    if ((aux2.getValorHeuristico() + aux2.getCustoP()) > (aux1.getValorHeuristico()) + aux1.getCustoP()) {
                        aberto.remove(p);
                        aberto.insereOrdenado(aux1);
                    }
                } else {
                    aberto.insereOrdenado(aux1);
                }
            }
        }
        fechado.insere(atual); //depois que atual ja foi todo expandido, inserir atua em fechado
        i++; //incrementa o numero de nós expandidos

        //caso o ponto inicial e final escolhido não sejam interligados, ou seja, caso seja impossivel encontra um caminho q ligue os dois
        //o algoritmo vai exibir em tela esta mensagem apresentar os pontos e seus respectivos custo, neste caso o custo inicial é zero e o custo do meta e infinito
        if (aberto.EstaVazia()) { //caso a lista aberta esvazia sem que o meta seja encontrado, executar:

           cout << "Eh impossivel chegar neste ponto Meta." << endl;
            cout << "Ponto Inicial:" << "(" << ini << " " << ini.getCustoP() << ")";
            cout << "\nPonto Final:" << "(" << fim << fim.getCustoP() << ")" << flush;
        }
    }
}
