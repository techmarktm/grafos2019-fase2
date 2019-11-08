#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include "grafo.h"
#include "funcoesGerais.h"
#include <locale.h>
#include <ctime>

using namespace std;

//Funcao de Impressao de Menu
//Entrada: Arquivo .txt do menu a ser impresso em tela
//Saida: Impressao em tela do Menu de opcoes
//Instancias https://sites.google.com/site/graphcoloring/vertex-coloring
void imprimeMenu() {

    ifstream leitor;
    leitor.open("menu.txt");//Le o menu to txt
    string buffer;

    if (leitor.is_open()) {
        while(!leitor.eof()) {
            getline(leitor, buffer);
            cout << buffer << endl;
        }
        leitor.close();
    } else {
        cout << "Erro ao abrir Arquivo menu.txt!" << endl;
    }
}

//Funcao Que salva uma string em um arquivo .txt
//Entrada: String a ser salva e arquivo .txt onde os dados serao salvos.
//Saida: Escrita da string passada por parametro em um arquivo .txt (tambem passado por parametro)
void salvarTxt(string salvar, string file) {
    ofstream arquivo;
    arquivo.open(file);
    arquivo << salvar << endl;
    //arquivo.close();
}

//instancia um grafo a partir de um arquivo txt
Grafo* insereGrafoTxt(string nomeArquivo, bool orientado, bool ponderado) {
    ifstream arquivo(nomeArquivo);
    string linha;
    Grafo *grafo = new Grafo();
    unsigned int numV, a1, a2 = 0;
    char identificador;
    int peso = 0;
    if (arquivo.good()) { //Verifica se o arquivo esta aberto
        cout << "Lendo grafo do arquivo "  << nomeArquivo << " ..." << endl;
        getline(arquivo, linha); //pula a primeira linha
        while (getline(arquivo, linha)) { //Continua lendo o arquivo
            if (ponderado) {
                istringstream iss(linha);
                iss >> identificador >> a1 >> a2 >> peso;
                if (identificador == 'e') {
                    if (!grafo->existeNo(a1)) {
                        grafo->addVertice(new Vertice(a1));
                    }
                    if (!grafo->existeNo(a2)) {
                        grafo->addVertice(new Vertice(a2));
                    }
                    grafo->addAresta(a1,a2, orientado, peso);
                }
            } else {
                istringstream iss(linha);
                iss>> identificador >> a1 >> a2;
                if (identificador == 'e') {
                    if (!grafo->existeNo(a1)) {
                        grafo->addVertice(new Vertice(a1));
                    }
                    if (!grafo->existeNo(a2)) {
                        grafo->addVertice(new Vertice(a2));
                    }
                    grafo->addAresta(a1,a2, orientado, -1);
                }
            }
        }
    } else { //Caso o arquivo nao esteja aberto, mostra um erro.
        cout << "Erro ao abrir arquivo." << nomeArquivo << endl;
        exit(1);
    }
    return grafo;
}
