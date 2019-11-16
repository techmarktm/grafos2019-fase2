#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#define VERTICE 0
#define ARESTA 1
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <math.h>

using namespace std;

class Aresta;
class Vertice;
class Grafo;

class Vertice {
  private:
    int id;        //Indice do vertice
    int grau;      //Grau do vertice
    Aresta *pri;   //Primeira aresta do v�rtice
    Vertice *prox; //Proximo vertice em relacao ao consultado
    unsigned int cor; //ID da cor do vertice

  public:
    Vertice(int ID);              //construtor
    ~Vertice();                   //destrutor
    void addAresta(Aresta *);     //Adiciona aresta
    void setprox(Vertice *);      //Atribui proximo vertice
    void setId(int);              //Atribui indice do vertice
    void setGrau(int g);          //defini o grau de um vertice (acrescido automaticamente na inser��o de aresta)
    int getId();                  //retorna o indice do v�rtice
    int getGrau();                //retorna o grau do v�rtice
    Vertice *getprox();           //Retorna o proximo vertice
    Aresta *getpri();             //retorna a primeira aresta do vertice
    void setCor(unsigned int);    //Muda a cor do vertice
    int getCor();        //Retorna a cor do vertice
};

class Aresta {
  private:
    Vertice *v1;  //Aponta para o Vertice 1 da aresta
    Vertice *v2;  //Aponta para o Vertice 2 da aresta
    Aresta *prox; //Aponta pra proxima aresta do v�rtice
    float peso;

  public:
    Aresta(Vertice *, Vertice *); //Construtor
    ~Aresta();                    //Destrutor
    void setVertice1(Vertice *);  //Atribui o v�rtice 1 da aresta
    void setVertice2(Vertice *);  //Atribui o v�rtice 2 da aresta
    void setprox(Aresta *);       //Atribui proxima aresta
    void setPeso(float peso);     //Atribui um peso pra aresta
    float getPeso();              //Retorna o peso da aresta
    Vertice *getVertice1();       //Retorna o Vertice 1 da aresta
    Vertice *getVertice2();       //Retorna o Vertice 2 da aresta
    Aresta *getprox();            //Retorna a proxima aresta da lista
};

class Alfa {
  private:
    double valor;
    float mediaResultados;
    float totalCores;
    unsigned int melhorResultado;
    float probabilidade;
    float iteracoes;
  public:
    Alfa(double val);
    ~Alfa();
    void setValor(double);
    void setMedia();
    void setTotalCores(int);
    void setProb();
    void setProbValor(float valor);
    void setMelhorResult(int);
    void addIt();
    double getValor();
    float getMedia();
    int getTotalCores();
    int getMelhorResult();
    float getProb();
    int getIt();
};

class Solucao {
    public:
        double alfasRand[3];
        float totalMelhoresGulosoRand[3];
        float totalMediaGulosoRand[3];
        float tempoMedioGulosoRand;

        double alfasReat[10];
        float totalMelhoresGulosoReat[10];
        float totalMediaGulosoReat[10];
        float totalItGulosoReat[10];
        float tempoMedioGulosoReat;

        Solucao();
        ~Solucao(){};
};

class Grafo {
  public:
    Vertice *vPri; //Primeiro vertice da lista de vertices
    int numV;      //Numero de vertices
    int numA;      //Numero de arestas
  public:
    Grafo();                                    //Construtor
    ~Grafo();                                   //Destrutor
    int getNumV();                              //Retorna o numero de vertices
    int getNumA();                              //Retorna o numero de arestas
    bool existeNo(int);                         //Verifica se um n� existe no grafo
    bool verificaAdjacencia(int, int, bool);    // Verifica se os 2 nos passados por parametros sao ajacentes
    void addVertice(Vertice *);                 //Adiciona um novo vertice ao grafo
    void addAresta(int, int, bool, float);      //Adiciona uma nova aresta ao grafo beseado nos ids dos vertices passados, um bool que indica se � direcionado ou nao, e uma string contendo o peso
    string imprimeGrafo();                      //Imprime o grafo em forma de uma lista encadeada e retorna uma string com esta informacao
    void imprimeCores();                        //Imprime as cores de todos os vértices do grafo
    void limpaCores();                          //Remove as cores de todos os vertices do grafo - Seta todas pra zero
    int algoritmoGuloso();                      //Algoritmo Guloso para coloracao dos vertices do grafo
    int algoritmoGulosoRand(int,float);         //Algoritmo Guloso Randomizado para coloracao dos vertices do grafo, passando a seed e valor do alpha por parametro
    string testesGuloso();                        //Algoritmo em lote para realizar os testes do algoritmo guloso
    string testesGulosoRand (int seed, Solucao*, double vetAlfas[], int tamVetAlfas);                   //Algoritmo em lote para realizar os testes do algoritmo guloso randomizado
    string testesGulosoRandReativo(int seed, Solucao*, double vetAlfas[], int tamVetAlfas);             //Algoritmo em lote para realizar os testes do algoritmo guloso randomizado
    bool verifViabilidade();                    //Algoritmo que dado um grafo, ele verifica se atende as restrições do problema de coloração
};

#endif // GRAFO_H_INCLUDED
