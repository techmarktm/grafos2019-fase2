#include "grafo.h"
#include <iostream>
#include <string>
#include <sstream>

Alfa::Alfa(double val) {
    valor = val;
    mediaResultados = 0;
    probabilidade = 0;
    iteracoes = 0;
    totalCores = 0;
}

Alfa::~Alfa() {}

void Alfa::setValor(double val){
    valor = val;
}

void Alfa::setMedia(){
    mediaResultados = (totalCores / iteracoes);
}

void Alfa::setTotalCores(int numCores){
    totalCores = totalCores + numCores;
}

void Alfa::setMelhorResult(int result){
    melhorResultado = result;
}

void Alfa::setProb(){
    //garante que há ao menos uma media de resultados, e impede a divisao pro zero
    if (mediaResultados != 0){
        probabilidade = 1/mediaResultados;
    }
    else {
        probabilidade = 0;
    }
}

void Alfa::setProbValor(float valor){
    probabilidade = valor;
}

void Alfa::addIt(){
    iteracoes = iteracoes + 1;
}

double Alfa::getValor(){
    return valor;
}

float Alfa::getMedia(){
    return mediaResultados;
}

int Alfa::getMelhorResult(){
    return melhorResultado;
}

float Alfa::getProb(){
    return probabilidade;
}

int Alfa::getIt(){
    return iteracoes;
}

int Alfa::getTotalCores(){
    return totalCores;
}

Solucao::Solucao(){
     for (int i = 0; i < 3; i++){
        totalMelhoresGulosoRand[i] = 0;
        totalMediaGulosoRand[i] = 0;
        tempoMedioGulosoRand = 0;
     }

     for (int i = 0; i < 10; i++){
        totalMelhoresGulosoReat[i] = 0;
        totalMediaGulosoReat[i] = 0;
        totalItGulosoReat[i] = 0;
        tempoMedioGulosoReat = 0;
     }
}

