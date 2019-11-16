#include "grafo.h"
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <locale.h>
#include <ctime>
#include <math.h>
#include <cstdlib>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

#define I __INT_MAX__ //Infinito

using namespace std;
clock_t relInicio;
clock_t relFim;

Grafo::Grafo() {

    vPri = NULL;
    numV = 0;
    numA = 0;
}

int Grafo::getNumV() {

    return numV;
}

int Grafo::getNumA() {

    return numA;
}

void Grafo::addVertice(Vertice *a) {

    numV++;
    Vertice *p = vPri;
    if (p == NULL) {
        vPri = a;
    } else {
        for (; p->getprox() != NULL; p = p->getprox())
            ;
        p->setprox(a);
    }
}

void Grafo::addAresta(int v1, int v2, bool orientado, float peso) {

    Vertice *p1, *p2;
    numA++;
    p1 = p2 = NULL;
    for (Vertice *p = vPri; p != NULL; p = p->getprox()) {
        if (p->getId() == v1) {
            p1 = p;
        } else if (p->getId() == v2) {
            p2 = p;
        }
        if (p1 != NULL && p2 != NULL) {
            Aresta *a = new Aresta(p1, p2);
            a->setPeso(peso);
            p1->addAresta(a);

            //se o grafo nao for orientado, cria a aresta de p2 para p1 tambem
            if (!orientado) {
                a = new Aresta(p2, p1);
                a->setPeso(peso);
                p2->addAresta(a);
            }
            break;
        }
    }
}

//confere se existe um determinado vertice no grafo
bool Grafo::existeNo(int no) {

    for (Vertice *v = vPri; v != NULL; v = v->getprox()) {
        if (v->getId() == no) {
            return true;
        }
    }
    return false;
}

//Verifica se 2 nos sao adjacentes entre si
bool Grafo::verificaAdjacencia(int v1, int v2, bool orient) {

    if (existeNo(v1) && existeNo(v2)) {
        for (Vertice *v = vPri; v != NULL; v = v->getprox()) {
            if (v->getId() != 0) {
                for (Aresta *a = v->getpri(); a != NULL; a = a->getprox()) {
                    if (orient) {
                        //se o grafo for orientado, verifica apenas da aresta oriegem para a destino
                        if (v1 == a->getVertice1()->getId() && v2 == a->getVertice2()->getId()) {
                            return true;
                        }
                    } else {
                        //se o grafo nao for orientado, olha tando a "ida" quanto a "volta"
                        if ((v1 == a->getVertice1()->getId() && v2 == a->getVertice2()->getId()) || (v1 == a->getVertice2()->getId() && v2 == a->getVertice1()->getId())) {
                            return true;
                        }
                    }
                }
            }
        }
    } else {
        cout << "O grafo nao possui os nos " << v1 << " e/ou " << v2 << "." << endl;
        return 0;
    }
    return false;
}

//imprime toda a lista de adjacencia do grafo
string Grafo::imprimeGrafo() {

    string opcao, imprimePeso;
    string impresso = "\n\nIMPRESSAO DO GRAFO POR LISTA DE ADJACENCIA:\n";

    cout << "\nDeseja imprimir o Grafo e Salvar a Sa�da nas sa�das via txt? (Digite s ou n)" << endl;
    cin >> opcao;

    if (opcao == "n") {
        return "";
    }

    cout << "\nDeseja imprimir os pesos das Arestas do Grafo? (Digite s ou n)" << endl;
    cin >> imprimePeso;

    if (opcao == "s") {
        for (Vertice *v = vPri; v != NULL; v = v->getprox()) {
            if (v->getId() != -1) {
                cout << endl
                     << endl;
                impresso += "\n";
                cout << "No [" << v->getId() << "] ";
                impresso += "No [" + to_string(v->getId()) + "] ";
                for (Aresta *a = v->getpri(); a != NULL; a = a->getprox()) {
                    cout << "-> " << a->getVertice2()->getId();
                    impresso += "-> " + to_string(a->getVertice2()->getId());
                    if (imprimePeso == "s") {
                        cout << "(" << a->getPeso() << ") ";
                        impresso += "(" + to_string(a->getPeso()) + ") ";
                    }
                }
            }
        }
        cout << endl
             << endl;
        impresso += "\n";
        return impresso;
    } else {
        cout << "Opcao Invalida. Por favor, tente novamente." << endl;
        imprimeGrafo();
    }
}

/* ---------- ALGORITMOS DE COLORAÇÃO DOS VÉRTICES DO GRAFO ---------- */

//Limpa as cores do grafo (define para 0 a cor de cada vértice)
void Grafo::limpaCores() {
    for (Vertice *v = vPri; v != NULL; v = v->getprox()) {
        v->setCor(0);
    }
}

//Algoritmo de comparacao para ordenacao.
//Retorna True se o grau do primeiro vertice passado por parametro é maior > que o grau do segundo e false c.c
//Usado para ordenar o vetor de candidatos do menor para o maior grau
bool geq(Vertice* g1, Vertice* g2) {
    if(g1->getGrau() > g2->getGrau())
        return true;
    else
        return false;
}

//Realiza a coloracao do grafo pelo algoritmo guloso
//Ordenando a lista de candidatos pelo grau
int Grafo::algoritmoGuloso() {

    limpaCores();

    //Vetor de candidados
    vector<Vertice*> vertices;

    int tamanhoGrafo = this->getNumV();
    //vetor que armazenará as cores dos vizinhos de cada vértice (cores já utilizadas, ou seja, cores que o vértice atual nao pode assumir))
    bool coresVizinhos [tamanhoGrafo];

    //instanciando o vertice que será testado a cada iteracao
    Vertice* v = nullptr;

    int i = 0;//indice do vetor das cores dos vizinhos

    for (Vertice *v = vPri; v != NULL; v = v->getprox()) {
        //adiciona todos os vertices do grafo no vetor de candidados
        vertices.push_back(v);
        //define todas as cores de vizinhos como nao utilizadas (false)
        coresVizinhos[i] = false;
        i++;
    }

    //Lista de candidados ordenada pelo grau - Vertice de maior grau para o de menor grau
    sort(vertices.begin(), vertices.end(), geq);

    //Define a cor 1 para o primeiro vértice (cor nao utilizada)
    vertices[0]->setCor(1);

    //Percorre a lista de candidatos, verificando a cor do seu vizinho e atribuindo as cores ja utilizadas como true
    for (int i = 1; i < vertices.size(); i++) {
        Aresta* a = nullptr;
        for(a = vertices[i]->getpri(); a != nullptr; a=a->getprox()) {
            //se o vizinho já possui cor
            if(a->getVertice2()->getCor() != 0) {
                //marca as cores já utilizadas como true (cores do vizinho do vertice atual)
                coresVizinhos[a->getVertice2()->getCor()] = true;
            }
        }

        //percore em busca da cor disponivel com menor rótulo possivel e atribui pro vertice atual
        for(int disp = 1; disp < tamanhoGrafo; disp++) {
            if(coresVizinhos[disp] == false) {
                vertices[i]->setCor(disp);
                break;
            }
        }

        //Limpa as cores dos vizinhos
        for(a = vertices[i]->getpri(); a != nullptr; a=a->getprox()) {
            if(a->getVertice2()->getCor() != 0) {
                coresVizinhos[a->getVertice2()->getCor()] = false;
            }
        }
    }

    //Verifica o numero de cores total da solucao
    int numCores = 0;
    for (v = vPri; v != nullptr; v=v->getprox()) {
        if(v->getCor() > numCores)
            numCores = v->getCor();
    }
    return numCores;
}

//Realiza a coloracao do grafo pelo algoritmo guloso randomizado
//Ordenando a lista de candidatos pelo grau, e obtendo sempre um vertice aleatorio dentro do intervalo alfa
int Grafo::algoritmoGulosoRand(int seed, float alfa) {

    limpaCores();

    //Vetor de candidados
    vector<Vertice*> vertices;

    int tamanhoGrafo = this->getNumV();
    //vetor que armazenará as cores dos vizinhos de cada vértice (cores já utilizadas, ou seja, cores que o vértice atual nao pode assumir))
    bool coresVizinhos [tamanhoGrafo];

    //instanciando o vertice que será testado a cada iteracao
    Vertice* v = nullptr;

    int i = 0;
    for (Vertice *v = vPri; v != NULL; v = v->getprox()) {
        //adiciona todos os vertices do grafo no vetor de candidados
        vertices.push_back(v);
        //define todas as cores de vizinhos como nao utilizadas (false)
        coresVizinhos[i] = false;
        i++;
    }

    //Lista de candidados ordenada pelo grau
    sort(vertices.begin(), vertices.end(), geq);

    //Define a seed do rand
    srand(seed);
    int verticeRand; //Numero aleatorio

    //Itera pela lista de vertices até ficar vazia (todos os vertices coloridos)
    while(!vertices.empty()) {

        //Escolhe aleatoriamente um vertice no intervalo do alfa
        verticeRand = fmod(rand(), (vertices.size()*alfa));


        Aresta* a = nullptr;

        //Percore os vizinhos e atribui as cores ja utilizadas como true
        for(a = vertices[verticeRand]->getpri(); a != nullptr; a=a->getprox()) {
            if(a->getVertice2()->getCor() != 0) {
                coresVizinhos[a->getVertice2()->getCor()] = true;
            }
        }

        //percore em busca da cor disponivel com menor rótulo possivel e atribui pro vertice atual
        for(unsigned int disp = 1; disp < tamanhoGrafo; disp++) {
            if(coresVizinhos[disp] == false) {
                vertices[verticeRand]->setCor(disp);
                break;
            }
        }

        //Reseta a marcacao de vertices coloridos para a proxima iteracao
        for(a = vertices[verticeRand]->getpri(); a != nullptr; a=a->getprox()) {
            if(a->getVertice2()->getCor() != 0) {
                coresVizinhos[a->getVertice2()->getCor()] = false;
            }
        }

        //Retira o vertice atual da lista de candidados
        if(vertices.size() == 1)
            vertices.erase(vertices.begin());
        else
            vertices.erase(vertices.begin() + verticeRand);
    }

    //Calcula o total de cores usadas
    unsigned int numCores = 0;
    for (Vertice *v = vPri; v != NULL; v = v->getprox()) {
        if(v->getCor() > numCores)
            numCores = v->getCor();
    }
    return numCores;
}

string Grafo::testesGuloso() {

    string results = "\n\n----------------------------------------------------------------------------------------------\n";
    results += "------------------- RESULTADOS DOS TESTES DO ALGORITMO GULOSO --------------------------------\n";
    results += "----------------------------------------------------------------------------------------------\n";
    Grafo *grafo = this;

    cout << "\n---------------------------------------------------------------------------------\n";
    cout << "----------------- RESULTADOS DOS TESTES DO ALGORITMO GULOSO ---------------------\n";
    cout << "---------------------------------------------------------------------------------\n";

    relInicio = clock();
    int resultado = grafo->algoritmoGuloso();
    relFim = clock();
    double tempoExec = double(relFim - relInicio) / CLOCKS_PER_SEC;

    cout << "\n\nNumero de cores obtidas com algoritmo guloso: " << resultado << ".\n" << endl;
    results += "Numero de cores obtidas com algoritmo guloso: " + to_string(resultado) + ".\n";

    cout << "Tempo de Execucao: " << tempoExec << " segundos.\n"<< endl;
    results += "Tempo de Execucao: " + to_string(tempoExec) + " segundos.\n";

    results += "----------------------------------------------------------------------------------------------\n";

    return results;
}

//Nesta funcao, atribui-se uma probabilidade pro alfa, sendo ela inversamente proporcional ao qi (melhor resultado/media de resultados)
//Valores de probabilidade sao atribuidos manualmente para cada alfa
//Beneficiando os alfas com melhores resultados (menores medias)
void defineProb(Alfa*vetAlfas[], int tamVetAlfas) {

    //calcula o qi (1 / (melhor result/media result elevado a 10)
    for(int i = 0; i < tamVetAlfas; i++) {
        float qi = pow( (vetAlfas[i]->getMelhorResult() / vetAlfas[i]->getMedia()), 10);
        //faz com que a probabilidade seja inversamente proporcionao ao qi
        //qi = 1 / qi;
        vetAlfas[i]->setProbValor(qi);
    }

    float somatorioQi = 0;

    //obtem o total das probabilidades
    for(int i = 0; i<tamVetAlfas; i++) {
        somatorioQi = somatorioQi + vetAlfas[i]->getProb();
    }


    float porcentagem;

    //atribui quantos porcento a probabilidade do alfa representa em relaçao a soma total das probabilidades (100%)
    for (int i=0; i<tamVetAlfas; i++) {
        porcentagem = (100 / somatorioQi) * vetAlfas[i]->getProb();

        vetAlfas[i]->setProbValor(porcentagem);
        //cout << "Porcentagem do alfa " << vetAlfas[i]->getValor() << ": " << porcentagem << "." << endl;
    }
}

string Grafo:: testesGulosoRand(int seed, Solucao* solucao, double vetAlfas[], int tamVetAlfas) {

    string results = "\n\n---------------------------------------------------------------------------------------------\n";
    results += "----------------- RESULTADOS DOS TESTES DO ALGORITMO GULOSO RANDOMIZADO ----------------------\n";
    results += "----------------------------------------------------------------------------------------------\n";
    Grafo *grafo = this;

    cout << "\n--------------------------------------------------------------------------------------\n";
    cout << "-------------- RESULTADOS DOS TESTES DO ALGORITMO GULOSO RANDOMIZADO ----------------\n";
    cout << "-------------------------------------------------------------------------------------\n\n";

    clock_t relInicio;
    clock_t relFim;

    relInicio = clock(); //finaliza contador de tempo de execucao

    unsigned int resulAtual;

    Alfa* vetorAlfas[tamVetAlfas];

    //instancia os objetos do vetor de alfa com os valores definidos no enunciado
    for (int i = 0; i < tamVetAlfas; i++) {
        Alfa* aux = new Alfa(vetAlfas[i]);
        vetorAlfas[i] = aux;
    }

    //armazena o numero de iteracoes que o teste deve executar (como descrito no enunciado do trabalho)
    int numIteracoes = 500;

    //percorre todos os alfas
    for (int i = 0; i < tamVetAlfas; i++) {

        for (int j=0; j < numIteracoes; j++) {

            resulAtual = algoritmoGulosoRand(seed * j, vetorAlfas[i]->getValor());

            //verifica se é a primeira iteracao do alfa
            if (vetorAlfas[i]->getMelhorResult() == 0) {
                vetorAlfas[i]->setMelhorResult(resulAtual);
                vetorAlfas[i]->setTotalCores(resulAtual);
                vetorAlfas[i]->addIt();
            } else { //se nao for a primeira iteracao, aplica os calculos

                //verifica se o resultado atual é o melhor. Se for, substitui
                if (resulAtual < vetorAlfas[i]->getMelhorResult()) {
                    vetorAlfas[i]->setMelhorResult(resulAtual);
                }

                //incrementa o total de cores com resultado atual
                vetorAlfas[i]->setTotalCores(resulAtual);

                //incrementa as iteracoes do alfa atual
                vetorAlfas[i]->addIt();

                //define a media (num total de cores/num iteracoes)
                vetorAlfas[i]->setMedia();
            }
        }
    }

    relFim = clock(); //finaliza contador de tempo de execucao
    double tempoExec = double(relFim - relInicio) / CLOCKS_PER_SEC;

    for (int i = 0; i < tamVetAlfas; i++) {
        cout << "\n\nValor Alfa: " << vetorAlfas[i]->getValor() << endl;
        results += "\n\nValor Alfa: " + to_string(vetorAlfas[i]->getValor());

        cout << "Valor Melhor Resultado: " << vetorAlfas[i]->getMelhorResult() << endl;
        results += "\nValor Melhor Resultado: " + to_string(vetorAlfas[i]->getMelhorResult());

        cout << "Valor Media: " << vetorAlfas[i]->getMedia() << endl;
        results += "\nValor Media: " + to_string(vetorAlfas[i]->getMedia());

        cout << "Iteracoes executadas: " << vetorAlfas[i]->getIt() << endl;
        results += "\nIteracoes executadas: " + to_string(vetorAlfas[i]->getIt());

        cout << "Tempo de Execução: " << tempoExec << " segundos." << endl;
        results += "\nTempo de Execução: " + to_string(tempoExec) + " segundos.";
    }

    //adiciona as informações à solucao final (para calcular as medias)
    for (int i = 0; i < 3; i++){
        solucao->alfasRand[i] = vetorAlfas[i]->getValor();
        solucao->totalMelhoresGulosoRand[i] += vetorAlfas[i]->getMelhorResult();
        solucao->totalMediaGulosoRand[i] += vetorAlfas[i]->getMedia();
        solucao->tempoMedioGulosoRand += tempoExec;
    }

    return results;
}

string Grafo:: testesGulosoRandReativo(int seed, Solucao* solucao, double vetAlfas[], int tamVetAlfas) {
    string results = "\n\n------------------------------------------------------------------------------------------------\n";
    results += "--------------- RESULTADOS DOS TESTES DO ALGORITMO GULOSO RANDOMIZADO REATIVO ----------------\n";
    results += "----------------------------------------------------------------------------------------------\n";
    Grafo *grafo = this;

    cout << "\n\n---------------------------------------------------------------------------------\n";
    cout << "---------- RESULTADOS DOS TESTES DO ALGORITMO GULOSO RANDOMIZADO REATIVO -----------\n";
    cout << "------------------------------------------------------------------------------------\n";

    clock_t relInicio = clock();
    clock_t relFim;

    unsigned int resulAtual; //armazena o resultado atual de cada iteracao
    float media; //armazena a media da iteracao, para aplicar o valor na média do alfa
    int sorteiaAlfa; //receberá um valor aleatório entre 1 e 100, que definirá qual alfa será escolhido para próxima iteracao
    int alfaEscolhido; //id do vetor de alfas do alfa escolhido no sorteio

    Alfa* vetorAlfas[tamVetAlfas];

    //instancia os objetos do vetor de alfa com os valores definidos no enunciado
    for (int i = 0; i < tamVetAlfas; i++) {
        Alfa* aux = new Alfa(vetAlfas[i]);
        vetorAlfas[i] = aux;
    }


    //armazena o numero de iteracoes que o teste deve executar (como descrito no enunciado do trabalho)
    int numIteracoes = 1520;
    //o teste inicial defini as primeiras n iterações, à fim de distribuir as médias e probabilidades dos resultados iniciais
    int testeInicial = 20;
    //define de quantas em quantas iteracoes será sorteado um novo alfa para ser aplicado na coloração
    int intervaloAttAlfa = 150;

    //aplica as iteracoes de testes
    for (int j=0; j < numIteracoes; j++) {

        //defini as primeiras rodadas para distribuicao das probabilidades iniciais
        if (j < testeInicial) {

            //percorre todos os alfas
            for (int i = 0; i < tamVetAlfas; i++) {

                //guarda o resultado desta iteracao (numero cromático)
                resulAtual = algoritmoGulosoRand(seed * j, vetorAlfas[i]->getValor());

                //verifica se é a primeira iteracao do alfa, para definir corretamente a média inicial
                if (vetorAlfas[i]->getMelhorResult() == 0) {
                    vetorAlfas[i]->setMelhorResult(resulAtual);
                    vetorAlfas[i]->setTotalCores(resulAtual);
                    vetorAlfas[i]->addIt();
                    vetorAlfas[i]->setMedia();
                } else { //se nao for a primeira iteracao, aplica os calculos da média como a média anterior + a media atual dividido por 2

                    //verifica se o resultado atual é o melhor. Se for, substitui
                    if (resulAtual < vetorAlfas[i]->getMelhorResult()) {
                        vetorAlfas[i]->setMelhorResult(resulAtual);
                    }

                    //incrementa o total de cores com resultado atual
                    vetorAlfas[i]->setTotalCores(resulAtual);

                    //incrementa as iteracoes do alfa atual
                    vetorAlfas[i]->addIt();

                    //calcula a media (total de cores / num iteracoes)
                    vetorAlfas[i]->setMedia();
                }

            }
        } else if (j == testeInicial){ //apos os 20 testes iniciais, define as probabilidades e começa o guloso reativo de fato
            //define as probabilidades/porcentagens de chance de cada alfa baseados na sua média de resultados do teste inicial
            defineProb(vetorAlfas, tamVetAlfas);

        } else {
            //sorteia um valor entre 1 e 101 (porcentagem) para definir qual alfa será escolhido para próxima iteracao
            srand(seed * j);

            sorteiaAlfa = rand() % 101;

            //buffer que soma todas as porcentagens, a fim de verificar qual alfa foi encontrado no sorteio
            float bufferProb = 0;

            for (int i =0; i < tamVetAlfas; i++) {
                //vai incrementando o buffer com os valores das probabilidades
                bufferProb += vetorAlfas[i]->getProb();

                //se em algum momento o buffer for menor que o valor sorteado, encontra-se qual posicao do vetor do alfa que foi escolhido
                if (sorteiaAlfa<=bufferProb) {
                    alfaEscolhido = i; //armazena a posicao do vetor alfa sorteado
                    break;
                }
            }

            //os testes subsequentes, realizam a coloracao sempre com o alfa sorteado
            //e mais uma vez lembrando que os alfas com menores médias de resultados terao mais chance de serem sorteados para ser usado na coloracao
            resulAtual = algoritmoGulosoRand(seed * j, vetorAlfas[alfaEscolhido]->getValor());

            //verifica se o resultado atual é o melhor. Se for, substitui
            if (resulAtual < vetorAlfas[alfaEscolhido]->getMelhorResult()) {
                vetorAlfas[alfaEscolhido]->setMelhorResult(resulAtual);
            }

            //calcula a media (num total cores / num iteracoes)
            vetorAlfas[alfaEscolhido]->setTotalCores(resulAtual);

            //incrementa as iteracoes do alfa atual
            vetorAlfas[alfaEscolhido]->addIt();

            //calcula a media (num total cores / num iteracoes)
            vetorAlfas[alfaEscolhido]->setMedia();

            //se a iteracao atual estiver no intervalo definido no inicio da função,
            //realiza novamente a distribuição das probabilidades (quem tem menor média de cores tem maior prob de ser escolhido), e sorteia um novo alfa
            if (j % intervaloAttAlfa == 0) {
                srand(seed*j);
                defineProb(vetorAlfas, tamVetAlfas);
            }
        }

    }
    relFim = clock(); //finaliza contador de tempo de execucao
    double tempoExec = double(relFim - relInicio) / CLOCKS_PER_SEC;

    //redefine as probabilidades finais para verificação do resultado
    defineProb(vetorAlfas, tamVetAlfas);

    for (int i = 0; i < tamVetAlfas; i++) {
        cout << "\n\nValor Alfa: " << vetorAlfas[i]->getValor() << endl;
        results += "\n\nValor Alfa: " + to_string(vetorAlfas[i]->getValor());
        cout << "Valor Melhor Resultado: " << vetorAlfas[i]->getMelhorResult() << endl;
        results += "\nValor Melhor Resultado: " + to_string(vetorAlfas[i]->getMelhorResult());
        cout << "Valor Media: " << vetorAlfas[i]->getMedia() << endl;
        results += "\nValor Media: " + to_string(vetorAlfas[i]->getMedia());
        cout << "Iteracoes executadas: " << vetorAlfas[i]->getIt() << endl;
        results += "\nIteracoes executadas: " + to_string(vetorAlfas[i]->getIt());
        cout << "Valor Probabilidade: " << vetorAlfas[i]->getProb() << endl;
        results += "\nValor Probabilidade: " + to_string(vetorAlfas[i]->getProb()) + "%";
        cout << "Tempo de Execução: " << tempoExec << " segundos." << endl;
        results += "\nTempo de Execução: " + to_string(tempoExec) + " segundos.";
    }

    results += "\n----------------------------------------------------------------------------------------------\n";

    //atribui os resultados a solucao para calcular as medias dos resultados das 30 iteracoes
    for (int i = 0; i < 10; i++){
        solucao->alfasReat[i] = vetorAlfas[i]->getValor();
        solucao->totalMelhoresGulosoReat[i] += vetorAlfas[i]->getMelhorResult();
        solucao->totalMediaGulosoReat[i] += vetorAlfas[i]->getMedia();
        solucao->totalItGulosoReat[i] += vetorAlfas[i]->getIt();
        solucao->tempoMedioGulosoReat += tempoExec;
    }

    return results;
}

//Dado um grafo já colorido, verifica se a coloracao cumpre as restricoes
bool Grafo::verifViabilidade(){
    Grafo *grafo = this;
    bool validade = true;
    for (Vertice *v = vPri; v != NULL; v = v->getprox()){
        for (Aresta *a = v->getpri(); a != NULL; a = a->getprox()) {
            //verifica se algum vertice tem vizinho com a mesma cor, o que é inválido
            if (v->getCor() == a->getVertice2()->getCor()){
                validade = false;
            }
        }
    }
    return validade;
}
