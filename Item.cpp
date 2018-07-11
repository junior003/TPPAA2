#include "Item.h"
#include "Header.h"

Item::Item()
{
	this->ID = ident++;
	this->Grau = 0;
	this->GrauMod = 0;
}
void Item::addVizinhoPOS(int vizinho)
{
	if (vizinho + 1 != ID)
	{
		conf.push_back(&V[vizinho]);
		this->Grau++;
	}
}
void Item::CalculaGrauMod() //Grau modificado eh a soma dos graus dos vizinhos de um Item mais o seu próprio grau
{
	int GM = 0;
	for (V_iter i = conf.begin(); i != conf.end(); i++)
	{
		GM += (*i)->getGrau();
	}
	GM += this->Grau;
	this->GrauMod = GM;
}
bool Item::EhVizinho(int vizinho)
{
	if (vizinho == this->ID)
	{
		return true;//analisar
	}

	for (int i = 0; i < conf.size(); i++)
	{
		if (conf.at(i)->getID() == vizinho)
		{
			return true;
		}
	}
	return false;
}
void Item::setPeso(int P)
{
	this->peso = P;

}
int Item::getPeso()
{
	return this->peso;
}
int Item::getGrau()
{
	return this->Grau;
}
int Item::getGrauMod()
{
	return this->GrauMod;
}
int Item::getID()
{
	return ID;
}
void Item::getVizinhos(vector<Item> *viz)
{
	for (V_iter i = conf.begin(); i != conf.end(); i++)
	{
		viz->push_back(*(*i));
	}
}

void Item::printaVizinhos()
{
	for (int i = 0; i < conf.size(); i++)
	{
		cout << "v" << conf.at(i)->getID();
	}
	cout << endl;
}
