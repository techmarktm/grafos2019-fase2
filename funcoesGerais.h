#ifndef FUNCOESGERAIS_H_INCLUDED
#define FUNCOESGERAIS_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include "grafo.h"
#include <locale.h>
#include <ctime>

using namespace std;

void imprimeMenu();
void salvarTxt(string salvar, string file);
Grafo* insereGrafoTxt(string nomeArquivo, bool orientado, bool ponderado);

#endif // FUNCOESGERAIS_H_INCLUDED
