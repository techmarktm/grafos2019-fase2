#include "grafo.h"
#include <iostream>
#include <string>
#include <sstream>

Vertice::Vertice(int ID)
{
    id = ID;
    prox = NULL;
    pri = NULL;
    grau = 0;
    cor = 0;
}

void Vertice::addAresta(Aresta *a)
{
    grau++;
    if (pri == NULL)
    {
        pri = a;
    }
    else
    {
        Aresta *p;
        for (p = pri; p->getprox() != NULL; p = p->getprox())
            ;
        p->setprox(a);
    }
}

void Vertice::setId(int ID)
{
    id = ID;
}

void Vertice::setprox(Vertice *V)
{
    prox = V;
}

int Vertice::getId()
{
    return id;
}

int Vertice::getGrau()
{
    return grau;
}

Aresta *Vertice::getpri()
{
    return pri;
}

Vertice *Vertice::getprox()
{
    return prox;
}
void Vertice::setGrau(int g)
{
    grau = g;
}

void Vertice::setCor(unsigned int c){
    cor = c;
}

int Vertice::getCor(){
    return cor;
}
