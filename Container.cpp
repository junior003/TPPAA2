#include "Container.h"
#include "Header.h"


Container::Container()
{
	this->IDc=ident++;
	this->capacT = CAP;
	this->conteudo = 0;
}

void Container::setcapacT(int c)
{
	this->capacT = c;
}

void Container::setconteudo(int c)
{
	this->conteudo += c;
}

int Container::getcapacT()
{
	return this->capacT;
}

int Container::getconteudo()
{
	return this->conteudo;
}

int Container::getNumItens()
{
	return this->itens.size();
}

int Container::getitem(int pos)
{
	return this->itens.at(pos);
}

void Container::additem(int i)
{
	this->itens.push_back(i);
}

void Container::removeitem(int id,int peso)//TEST
{
	if (this->itens.size() == 0)
	{
		return;
	}
	for (vector<int>::iterator j = this->itens.begin(); j != this->itens.end(); j++)
	{
		if (id == *j)
		{
			this->conteudo -= peso;
			itens.erase(j);
			j--;
			break;
		}
	}
	
}
