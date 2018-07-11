#ifndef ITEM_H
#define ITEM_H

#include <vector>
using namespace std;
class Item
{
	//identificador unico
	int ID;

	//peso do item
	int peso;

	//lista de conflitos
	vector<Item*> conf;

	//grau do vertice representado pelo item
	int Grau;

	//grau modificado 
	int GrauMod;
	typedef vector<Item*>::iterator V_iter; // iterator para percorrer os itens do conflito

public:
	Item();
	void addVizinhoPOS(int); // adiciona uma aresta no grafo
	void CalculaGrauMod(); //Calcula o grau modificado de cada Item
	bool EhVizinho(int); // verifica se dois itens sao vizinhos
	void setPeso(int);
	int getPeso();
	int getGrau();
	int getGrauMod();
	int getID();
	void getVizinhos(vector<Item>*); //retorna todos os vizinhos do Item 
	void printaVizinhos();
};
#endif // !ITEM_H