#ifndef HEADER_H
#define HEADER_H
/*
UNIVERSIDADE FEDERAL DE OURO PRETO
Graduação em Ciência da Computação

Disciplina:BCC241 - PROJETO E ANALISE DE ALGORITMOS
Professor: Dr. Haroldo Gambini Santos

Aluno: Joaquim Alves Viana Júnior
Matrícula:14.2.4338

Este trabalho tem como objetivo o desenvolvimento de diferentes métodos e heurísticas
para a resolução do problema do empacotamento com conflitos.
*/

#include <cmath>
#include <iostream>
#include <list>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <chrono>
#include "Item.h"
#include "Container.h"
#include <fstream>
using namespace std;
using namespace std::chrono;

// Declaracao de variáveis globais

//Variaveis responsaveis pela contagem do tempo
high_resolution_clock::time_point t1;
high_resolution_clock::time_point t2;
duration<double> time_span;

//Define qual o proximo ID a ser gerado
int ident = 1; 

// número total de itens que são representados como vértices de um grafo
int NumV; 
//Capacidade máxima dos containers
int CAP=0;

//Vetor que guardará os itens lidos
Item *V; 

// cópia do vetor original
Item *VOrd; 

//Vetor que representa a solucao corrente
vector<Container> Solucao;

//Vetor que representa os itens pertencentes ao clique
vector<Item> X; 

//Tempo máximo de execução em segundos
int TMax;

//porcentagem que o metodo terá do tempo total para criar uma solução
double Tporc = 0.7; 

//Temperatura maxima do Simulated Annealing
int TemperMAX=100000; 


//Funções responsaveis pela entrada e saida de dados
void LeituraDeDados(char* nome);
void Saida(char* nome);

//Função que indica se já acabou o tempo(retorna 1) ou não(retorna 0)
bool VerificaTempo();

//Funções referentes aos métodos implementados:
void FirstFit();
void BestFit();
void WorstFit();
void Clique_com_FF();
void SolucaoRandomica();
void SimulatedAnnealing();

//Cria uma solucao vizinha a solucao corrente baseado na temperatura do SA
void CalculaProx(vector<Container>*,int );

//Funcao que converte uma solucao em um valor para comparar solucoes e definir a melhor,
//Para isso a funcao faz um somatorio dos itens ao quadrado em cada container
double CalculaDistancia(vector<Container>);



//QuickSort personalizado: Ordena pelo peso(FirstFit Decrescente) ou pelo grau modificado(Clique Maximo), a depender do método  ser usado
void swap(Item*, Item*);
int partition(Item[], int , int ,int);
void quickSort(Item [], int , int ,int);

//Funções que compõem o Algoritmo de Bron e Kerborsch

//Calcula para cada vertice seu grau modificado
void CalculoDoGrauMod();

//Recebe dois conjuntos e retorna a interseção dos mesmos
void CalculaInter_CC(vector<Item>*P, vector<Item> *C, vector<Item> *Inter);

//Recebe dois conjuntos e retorna a união dos mesmos
void CalculaUniao_CC(vector<Item>*P, vector<Item> *C, vector<Item> *Uniao);

//Recebe um conjunto e um elemento e retorna a união dos mesmos
void CalculaUniao_CE(vector<Item>*R, Item v, vector<Item> *Uniao);

//Recebe um conjunto e um elemento e retorna a diferença dos mesmos
void CalculaDiferenca_CE(vector<Item>*P, Item v);

//Recebe um conjunto e um elemento e retorna a diferença dos mesmos
void CalculaDiferenca_CC(vector<Item>*P, vector<Item>*X);

//Algoritmo de Bron e Kerbosch
void CalculaCliqueMaximo(vector<Item> *C, vector<Item> *P, vector<Item> *R,int);

//Função que chama as demais do clique
int CliqueMaximo();

#endif // !HEADER_H