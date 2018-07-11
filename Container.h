#ifndef CONTAINER_H
#define CONTAINER_H


#include "Item.h"

using namespace std;

class Container
{
private:
	int IDc;
	int capacT; //capacidade total da caixa
	int conteudo; //quantidade guardada na caixa
	vector<int> itens; //vetor de itens contidos na caixa, somente o ID do item eh guardado
public:
	Container();
	void setcapacT(int);
	void setconteudo(int);
	int getcapacT();
	int getconteudo();
	int getNumItens();
	int getitem(int);
	void additem(int);
	void removeitem(int,int);

};

#endif // !CONTAINER_H