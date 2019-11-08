#include "grafo.h"
#include <iostream>
#include <string>
#include <sstream>

Aresta::Aresta(Vertice *V1,Vertice *V2) {

    v1=V1;
    v2=V2;
    prox=NULL;
    peso = -1;
}

Aresta::~Aresta() {}

Aresta* Aresta::getprox() {
    return prox;
}

Vertice * Aresta::getVertice1() {
    return v1;
}

Vertice * Aresta::getVertice2() {
    return v2;
}

void Aresta::setprox(Aresta* a) {
    prox =a;
}

void Aresta::setVertice1(Vertice* V1) {
    v1=V1;
}

void Aresta::setVertice2(Vertice* V2) {
    v2=V2;
}

void Aresta::setPeso(float p) {
    peso = p;
}

float Aresta::getPeso() {
    return peso;
}
