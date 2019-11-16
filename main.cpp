/*
Fase 2 - Coloração de Vértices - Teoria dos Grafos 2019.3 - UFJF
Grupo 3 - Bruno, Fernanda, Diogo
*/
#define I __INT_MAX__ //Infinito
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include "grafo.h"
#include "funcoesGerais.h"
#include <locale.h>
#include <ctime>

string saida = "";
clock_t clockIni;
clock_t clockFim;

using namespace std;

//Instancias https://sites.google.com/site/graphcoloring/vertex-coloring

//para executar, navegue no prompt de comando ou terminal at� o diretorio do arquivo grafos2019.exe e execute o comando abaixo:
//grafos2019.exe grafoTeste.txt saidas.txt 0 0
//ao utilizar o codeblocks, voc� tamb�m poder� definir os argumentos acima no menu Project->Set Project Arguments e colar a linha acima
//no campo "Project Arguments"

int main(int argc, char *argv[]) {


    /* ============================================================= /*
        ETAPA DE TRATAMENTO DOS ARGUMENTOS E CONFIGURACOES INICIAIS
    /* ============================================================= */

    setlocale(LC_ALL, "portuguese"); //Define o padrao de char para portugues, para fazer impressao correta de cedilha e acentos

    //Verificação dos argumentos
    if (argc < 6) {
        cout << "\numero incorreto de argumentos. \nUtilize <nomePrograma.exe> <nomeArquivoEntrada.txt> <nomeArqSaida.txt> <orientado(bool)> <ponderado nas arestas(bool)> <ponderado nos vertices (bool)>" << endl;
        cout << "\nEXEMPLO: grafos2019.exe grafoTeste.txt saidas.txt 0 0 0\n"
             << endl;
        return 0;
    }

    //Atribuindo cada argumento para uma variavel dentro do programa
    string nomePrograma = argv[0];
    string arquivoEntrada = argv[1];
    string arquivoSaida = argv[2];
    string orient = argv[3];
    bool orientado = false; //por padrao, o grafo nao ser� orientado.
    string pond = argv[4];
    bool ponderado = false; //por padrao, o grafo nao ser� ponderado nas arestas
    string pondV = argv[5];
    bool ponderadoV = false; //por padrao, o grafo nao ser� ponderado nos vertices.

    if (orient == "1") {
        //atribuindo o valor em bool dependendo do parametro
        orientado = true;
    }

    if (pond == "1") {
        //atribuindo o valor em bool dependendo do parametro
        ponderado = true;
    }



    /* ===================================================================== /*
        ETAPA DE PREPARACAO DO GRAFO E CARREGAMENTO DA INSTANCIA DE ENTRADA
    /* ===================================================================== */



    cout << "Instanciando o grafo do arquivo " << arquivoEntrada << "..." << endl;
    saida += "Instanciando o grafo do arquivo " + arquivoEntrada + "...\n";

    if (orientado) {
        cout << "O grafo sera orientado." << endl;
        saida += "O grafo sera orientado.\n";
    } else {
        cout << "O grafo nao sera orientado." << endl;
        saida += "O grafo nao sera orientado.\n";
    }

    if (ponderado) {
        cout << "O grafo sera ponderado." << endl;
        saida += "O grafo sera ponderado.\n";
    } else {
        cout << "O grafo nao sera ponderado." << endl;
        saida += "O grafo nao sera ponderado.\n";
    }

    //Instancia um novo grafo para alocar dados do arquivoEntrada
    Grafo *grafo;

    //Chama a funcao que carrega o grafo com informacoes a partir da instancia no arquivo txt
    grafo = insereGrafoTxt(arquivoEntrada, orientado, ponderado); //Atribui os valores do arquivo txt para o grafo

    cout << "O Grafo possui " << grafo->getNumV() << " vertices e " << grafo->getNumA() << " arestas." << endl;
    saida += "O Grafo possui " + to_string(grafo->getNumV()) + " vertices e " + to_string(grafo->getNumA()) + " arestas.";




    /* ============================================================= /*
        ETAPA DE DE CHAMADA DE TESTES E ARMAZENAMENTO DE RESULTADOS
    /* ============================================================= */

    //Instancia um novo objeto Solucao, que armazena os resultados de todos os testes para calcular a media de todas as execucoes
    Solucao* solucao = new Solucao();

    //Criacao das Variaveis - Vetor de Alfas
    double vetAlfasRand [3] = {0.10, 0.30, 0.50};
    int tamVetAlfasRand = (sizeof(vetAlfasRand)/sizeof(*vetAlfasRand));

    double vetAlfasReat [10] = {0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50};
    int tamVetAlfasReat = (sizeof(vetAlfasReat)/sizeof(*vetAlfasReat));

    //Define quantas iteracoes serao executadas para cada instancia de entrada
    int numExecucoes = 30;

    clockIni = clock();

    int seed = 1; //seed inicial. A cada execucao dos algoritmos, mudará a seed.

    //Realiza as numExecucoes para executar com cada instancia
    for (int i = 1; i <= numExecucoes; i++) {
        seed += i;
        cout << "\nEXECUCAO NUM " << i << " de 30. Seed: " << seed << endl;
        saida += "\nEXECUCAO NUM " + to_string(i) + " de 30. Seed: " + to_string(seed) + "\n";

        saida += grafo->testesGulosoRand(seed, solucao, vetAlfasRand, tamVetAlfasRand);
        saida += grafo->testesGulosoRandReativo(seed, solucao, vetAlfasReat, tamVetAlfasReat);
    }

    //Realiza a coloracao com algoritmo Guloso
    cout << "\n\n\n\n\nRESULTADOS PARA o ALGORITMO GULOSO. INSTANCIA: " << arquivoEntrada << "." << endl;
    saida += "\n\n\nRESULTADOS PARA O ALGORITMO GULOSO. INSTANCIA: " + arquivoEntrada + ".\n";
    saida += grafo->testesGuloso();


    cout << "\nMEDIAS DE RESULTADOS PARA AS " << numExecucoes << " EXECUCOES DO ALGORITMO GULOSO RANDOMIZADO. INSTANCIA: " << arquivoEntrada << "." << endl;
    saida += "\n\nMEDIAS DE RESULTADOS PARA AS " + to_string(numExecucoes) + " EXECUCOES DO ALGORITMO GULOSO RANDOMIZADO. INSTANCIA: " + arquivoEntrada + ".\n";


    for (int i=0; i < 3; i++){

        cout << "\nMedia Geral das " << numExecucoes << " execucoes para o alfa " << solucao->alfasRand[i]  << ": " << solucao->totalMediaGulosoRand[i] / numExecucoes << endl;
        saida += "\n\nMedia Geral das " + to_string(numExecucoes) + " execucoes para o alfa " + to_string(solucao->alfasRand[i]) + ": " + to_string(solucao->totalMediaGulosoRand[i] / numExecucoes);

        cout << "Media dos Melhores Resultados das " << numExecucoes << " execucoes para o alfa " << solucao->alfasRand[i]  << ": " << solucao->totalMelhoresGulosoRand[i] / numExecucoes << endl;
        saida += "\nMedia dos Melhores Resultados das " + to_string(numExecucoes) + " execucoes para o alfa " + to_string(solucao->alfasRand[i])  + ": " + to_string(solucao->totalMelhoresGulosoRand[i] / numExecucoes);
    }

    cout << "\nMedia de Tempo de Execucao das " << numExecucoes << " execucoes do algoritmo guloso randomizado: " << solucao->tempoMedioGulosoRand / numExecucoes << endl;
    saida += "\n\nMedia de Tempo de Execucao das " + to_string(numExecucoes) + " execucoes do algoritmo guloso randomizado: " + to_string(solucao->tempoMedioGulosoRand / numExecucoes);

    cout << "\n\nMEDIAS DE RESULTADOS PARA AS " << numExecucoes << " EXECUCOES DO ALGORITMO GULOSO RANDOMIZADO REATIVO. INSTANCIA: " << arquivoEntrada << "." << endl;
    saida += "\n\n\nMEDIAS DE RESULTADOS PARA AS " + to_string(numExecucoes) + " EXECUCOES DO ALGORITMO GULOSO RANDOMIZADO REATIVO. INSTANCIA: " + arquivoEntrada + ".\n";

    for (int i=0; i < 10; i++){

        cout << "\nMedia Geral das " << numExecucoes << " execucoes para o alfa " << solucao->alfasReat[i]  << ": " << solucao->totalMediaGulosoReat[i] / numExecucoes << endl;
        saida += "\n\nMedia Geral das " + to_string(numExecucoes) + " execucoes para o alfa " + to_string(solucao->alfasReat[i])  + ": " + to_string(solucao->totalMediaGulosoReat[i] / numExecucoes);

        cout << "Media dos Melhores Resultados das " << numExecucoes << " execucoes para o alfa " << solucao->alfasReat[i]  << ": " << solucao->totalMelhoresGulosoReat[i] / numExecucoes << endl;
        saida +=  "\nMedia dos Melhores Resultados das " + to_string(numExecucoes) + " execucoes para o alfa " + to_string(solucao->alfasReat[i])  + ": " + to_string(solucao->totalMelhoresGulosoReat[i] / numExecucoes);

        cout << "Total do Num de Iteracoes para as " << numExecucoes << " execucoes para o alfa " << solucao->alfasReat[i]  << ": " << solucao->totalItGulosoReat[i] << endl;
        saida += "\nTotal do Num de Iteracoes para as " + to_string(numExecucoes) + " execucoes para o alfa " + to_string(solucao->alfasReat[i])  + ": " + to_string(solucao->totalItGulosoReat[i]);
    }

    cout << "\nMedia de Tempo de Execucao das " << numExecucoes << " execucoes do algoritmo guloso reativo: " << solucao->tempoMedioGulosoReat / numExecucoes << endl;
    saida += "\n\nMedia de Tempo de Execucao das " + to_string(numExecucoes) + " execucoes do algoritmo guloso reativo: " + to_string(solucao->tempoMedioGulosoReat / numExecucoes);
    cout << "\n\n";

    //Nomeia o arquivo de Saida com o nome da instancia
    //string saidaInst = "results-instancia-";
    //saidaInst += arquivoEntrada + ".txt";

    salvarTxt(saida, arquivoSaida);
    delete solucao;

    clockFim = clock(); //finaliza contador de tempo de execucao
    double tempoTotal = double(clockFim - clockIni) / CLOCKS_PER_SEC;

    cout << "\n\nTEMPO TOTAL DE EXECUCAO: " << tempoTotal << endl;
    cout << "\n\nPrograma finalizado com sucesso!" << endl;
    return 0;
}
