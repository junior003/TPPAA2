#include "Header.h"
#include "Item.h"

//calcula todos os graus modificados
void CalculoDoGrauMod()
{
	for (int i = 0; i < NumV; i++)
	{
		VOrd[i].CalculaGrauMod();
	}
}

//Calcula a intersecao entre dois conjuntos e retorna em um terceiro passado por parâmetro
void CalculaInter_CC(vector<Item>*P, vector<Item> *C, vector<Item> *Inter)
{
	if (P->size() == 0 || C->size() == 0)
	{
		return;
	}
	else
	{
		for (vector<Item>::iterator i = P->begin(); i != P->end(); i++)
		{
			for (vector<Item>::iterator j = C->begin(); j != C->end(); j++)
			{
				if (i->getID() == j->getID())
				{
					Inter->push_back(*i);
				}
			}
		}
	}
}

//Calcula a uniao de dois conjuntos e retorna em um terceiro passado por parametro
void CalculaUniao_CC(vector<Item>*P, vector<Item> *C, vector<Item> *Uniao)
{
	bool Flag=true;
	if (P->size() == 0 || C->size() == 0)
	{
		if (P->size() == 0 && C->size() != 0)
		{
			Uniao->assign(C->begin(), C->end());
		}
		else
		{
			Uniao->assign(P->begin(),P->end());
		}
	}
	else
	{
		if (P->size() >= C->size())
		{
			Uniao->assign(P->begin(), P->end());
			for (vector<Item>::iterator i = C->begin(); i != C->end(); i++)
			{
				for (vector<Item>::iterator j = Uniao->begin(); j != Uniao->end(); j++)
				{
					if (i->getID() == j->getID())
					{
						Flag = false;
						break;
					}
				}
				if (Flag == true)
				{
					Uniao->push_back(*i);
				}
				Flag = true;
			}
		}
		else{
			Uniao->assign(C->begin(), C->end());
			for (vector<Item>::iterator i = P->begin(); i != P->end(); i++)
			{
				for (vector<Item>::iterator j = Uniao->begin(); j != Uniao->end(); j++)
				{
					if (i->getID() == j->getID())
					{
						Flag = false;
						break;
					}
				}
				if (Flag == true)
				{
					Uniao->push_back(*i);
				}
				Flag = true;
			}
		}
	}
}

//Calcula a uniao entre um conjunto e um elemento e retorna em um terceiro passado por parametro
void CalculaUniao_CE(vector<Item>*R, Item v, vector<Item> *Uniao)
{
	bool Flag = true;
	if (R->size() == 0)
	{
		Uniao->push_back(v);
	}else
	{
		Uniao->assign(R->begin(), R->end());
		for (vector<Item>::iterator j = Uniao->begin(); j != Uniao->end(); j++)
		{
			if (v.getID()== j->getID())
			{
				Flag = false;
				break;
			}
		}
		if (Flag == true)
		{
			Uniao->push_back(v);
		}
	}
}

//Calcula a diferenca entre um conjunto e um elemento, o resultado e dado no proprio conjunto
void CalculaDiferenca_CE(vector<Item>*P, Item v)
{
	if (P->size() == 0)
	{
		return;
	}
	for (vector<Item>::iterator j = P->begin(); j != P->end(); j++)
	{
		if (v.getID() == j->getID())
		{
			P->erase(j);
			//j--;
			break;
		}
	}
}
//Calcula a Diferenca entre dois conjuntos e retorna o resultado no primeiro
void CalculaDiferenca_CC(vector<Item>*P, vector<Item>*X)
{
	if (P->size() == 0)
	{
		return;
	}
	for (vector<Item>::iterator i = P->begin(); i != P->end(); i++)
	{
		for (vector<Item>::iterator j = X->begin(); j != X->end(); j++)
		{
			if (i->getID() == j->getID())
			{
				P->erase(i);
				X->erase(j);
				//i--;
				break;
			}
		}
	}
}

//usado para a comparaçao do resultado anterior com o proximo
int resultado = 0;

//indica se é necessário parar a procura pelo clique para gerar uma solução
bool gerar = true;

//Calcula o clique máximo usando algoritmo de Bron e Kerbosch
void CalculaCliqueMaximo(vector<Item> *C, vector<Item> *P,vector<Item> *R)
{
	vector<Item> Uniao,Uniao2;
	vector<Item> Inter1,Inter2;
	vector<Item> Dif;
	Item v;
	Item Pivo;
	vector<Item> viz;
	//Verifica se o tempo acabou
	if (VerificaTempo())
	{
		P->clear();
		R->clear();
		if (gerar)
		{
			Clique_com_FF();
			cout << "Tempo: " << time_span.count() << endl;
			cout << endl << "*" << Solucao.size() << "*" << endl;
			gerar = false;
		}
		return;
	}
	if (P->size() == 0 && R->size()==0) //Se P e R estao vazios
	{
		if (C->size() >resultado)//So captura resultados maiores que os anteriores
		{
			resultado = C->size();
			X.assign(C->begin(), C->end());
		}
		return;
	}
	for (vector<Item>::iterator j = P->begin(); j != P->end(); j++) //Para cada Item j em P
	{
		if (j > P->end())
		{
			break;
		}
		j->getVizinhos(&viz);

		CalculaUniao_CE(C, (*j), &Uniao); //C uniao com (j)

		CalculaInter_CC(P, &viz, &Inter1);//P interseção com Vizinhos de (j)

		CalculaInter_CC(R, &viz, &Inter2);//R iinterseção com Vizinhos de (j)

		viz.clear();
		
		CalculaCliqueMaximo(&Uniao,&Inter1,&Inter2); //C uniao j, P inter Viz(j),R inter Viz(j)
		CalculaDiferenca_CE(P, (*j)); //P = P diferença com (j)
		if (j != P->end())
		{
			j++;
		}
		Uniao.clear();
		CalculaDiferenca_CE(R, (*j)); //R = R diferença com j
	}
}


int CliqueMaximo()
{
	vector<Item> C; // Items do clique maximo 
	vector<Item> P; // Items a serem analisados
	vector<Item> R; // Items ja analisados
	for (int i = 0; i < NumV; i++)
	{
		P.push_back(VOrd[i]);
	}
	CalculaCliqueMaximo(&C,&P, &R);
	return X.size();
}

