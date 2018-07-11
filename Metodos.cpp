#include "Header.h"
#include "Item.cpp"
#include "Container.cpp"

using namespace std;

//Funcao que verifica se o tempo acabou
bool VerificaTempo()
{
	t2 = high_resolution_clock::now();
	time_span = duration_cast<duration<double> >(t2 - t1);
	//Tporc é a porcentagem do tempo que deve ser considerar pois o método nao pode acabar
	//no ultimo instante do tempo alocado, portanto ele é encerrado um pouco antes
	if (time_span.count() > TMax*Tporc)
	{
		return false;
	}
	return true;
}

/*
FIRST_FIT
Este método utiliza a estratégia de sempre por o item no primeiro container em que ele couber,
e que ele não tenha conflito.
*/
void FirstFit()
{
	bool inclui = false;
	bool repetido = false;
	int resto;

	//Para cada item procura um container entre os existentes para pôr o item
	for (int i = 0; i < NumV; i++)
	{
		//Caso o item tenha peso negativa, significa que ele já foi alocado por outro método
		if (VOrd[i].getPeso() == -1)
		{
			continue;
		}
		//Varre todos os containers procurando o primeiro que couber
		for (int j = 0; j < Solucao.size(); j++)
		{
			//Verifica se ele cabe no espaço restante
			resto = CAP - Solucao.at(j).getconteudo();
			if (VOrd[i].getPeso()<= resto)
			{
				inclui = true;
				//Verifica se o item tem conflito com algum que já está no container
				for (int k = 0; k < Solucao.at(j).getNumItens(); k++)
				{
					if (VOrd[i].EhVizinho(Solucao.at(j).getitem(k)))
					{
						inclui = false;
						break;
					}

				}
				if (inclui)
				{
					//se ele cabe e não possui conflito ele é posto no container
					Solucao.at(j).setconteudo(VOrd[i].getPeso());
					Solucao.at(j).additem(VOrd[i].getID());
					break;
				}
			}
		}
		if (!inclui || resto < VOrd[i].getPeso())
		{
			//se ele não pode ser posto em nenhum container existente, cria-se um novo para coloca-lo
			Container *c = new Container();
			c->additem(VOrd[i].getID());
			Solucao.push_back(*c);
			Solucao.at(Solucao.size() - 1).setconteudo(VOrd[i].getPeso());
			resto = CAP;
		}
		
	}
}

/*
CLIQUE_MAXIMAL_COM_FIRST_FIT
Este método usa o clique maximal encontrado no grafo que representa os itens e seus conflitos,
para criar uma solucao onde cada item do clique se encontra em um container diferente.
*/
void Clique_com_FF()
{
	for (int i = 0; i < X.size(); i++)
	{
		//Para cada item do clique, cria-se um container e o põe dentro
		Container *c = new Container();
		c->additem(X.at(i).getID());
		Solucao.push_back(*c);
		Solucao.at(Solucao.size() - 1).setconteudo(X.at(i).getPeso());
		for (int k = 0; k < NumV; k++)
		{
			//para cada item já alocado a um container, atribui-se peso negativo para que nao haja copias
			//sendo possível identifica-los no FirstFit
			if (VOrd[k].getID() == X.at(i).getID())
			{                                      
				VOrd[k].setPeso(-1);
			}
		}
	}
	//Chama o método FirstFit para continuar o processo de geração da solução
	FirstFit();
}

/*
BEST_FIT
Este método utiliza a estratégia de sempre por o item no container que tiver a menor capacidade restante,
se ele couber verifica se há conflito com os demais itens, caso haja, procura outro container para por o item.
*/
void BestFit()
{
	bool valido=false;
	int i, j, k;
	int min;
	int best;
	//Rest é o vetor que terá a capacidade restante de cada container
	//assume que no máximo haverão NumV containers
	int *Rest = new int[NumV]; 
	//Para cada item procura um container entre os existentes para pôr o item
	for (i = 0; i < NumV; i++)
	{
		Rest[i] = 0;
		min = CAP + 1;
		for (j = 0; j < Solucao.size(); j++)
		{
			//Além de verificar se o item cabe  no container verifica se o resto deste container menos o peso do item
			//é o menor de todos
			if (VOrd[i].getPeso() <= CAP - Solucao.at(j).getconteudo()  && Rest[j] - VOrd[i].getPeso() < min)
			{
				valido = true;

				//Verifica se há conflito entre os itens
				for (k = 0; k < Solucao.at(j).getNumItens(); k++)
				{
					if (VOrd[i].EhVizinho(Solucao.at(j).getitem(k)))
					{
	
						valido = false;
						break;
					}
				}
				if (valido)
				{
					//guardar qual o container de menor espaco restante e de quanto é esse espaço
					best = j;
					min = Rest[j] - VOrd[i].getPeso();
				}
			}
		}
		if (min == CAP + 1 && !valido)
		{
			//Se não foi possivel colocar em nenhum container, cria-se um novo
			Container *c = new Container();
			c->additem(VOrd[i].getID());
			Solucao.push_back(*c);
			Solucao.at(Solucao.size() - 1).setconteudo(VOrd[i].getPeso());
			Rest[Solucao.size() - 1] = CAP - VOrd[i].getPeso();
			
		}
		else
		{
			//caso contrário coloca o item no container de menor espaço restante
			Rest[best] -= VOrd[i].getPeso();
			Solucao.at(best).setconteudo(VOrd[i].getPeso());
			Solucao.at(best).additem(VOrd[i].getID());
			min = CAP + 1;
			valido = false;
			best = 0;
		}
		
	}
	delete[] Rest;
}

/*
WORST_FIT
Este método utiliza a estratégia de sempre por o item no container que tiver a maior capacidade restante,
se ele couber verifica se há conflito com os demais itens, caso haja, procura outro container para por o item.
*/
void WorstFit()
{
	bool valido = false;
	int i, j, k;
	int max;
	int best;
	//Rest é o vetor que terá a capacidade restante de cada container
	//assume que no máximo haverão NumV containers
	int *Rest = new int[NumV];

	//Para cada item procura um container entre os existentes para pôr o item
	for (i = 0; i < NumV; i++)
	{
		Rest[i] = 0;
		max = 0;
		for (j = 0; j < Solucao.size(); j++)
		{
			//Além de verificar se o item cabe  no container verifica se o resto deste container menos o peso do item
			//é o maior de todos
			if (VOrd[i].getPeso() <= CAP - Solucao.at(j).getconteudo() && Rest[j] - VOrd[i].getPeso() >max)
			{
				valido = true;
				//Verifica se há conflito entre os itens
				for (k = 0; k < Solucao.at(j).getNumItens(); k++)
				{

					if (VOrd[i].EhVizinho(Solucao.at(j).getitem(k)))
					{

						valido = false;
						break;
					}
				}
				if (valido)
				{
					//guardar qual o container de menor espaco restante e de quanto é esse espaço
					best = j;
					max = Rest[j] - VOrd[i].getPeso();
				}

			}
		}
		if (max == 0 && !valido)
		{
			//Se não foi possivel colocar em nenhum container, cria-se um novo
			Container *c = new Container();
			c->additem(VOrd[i].getID());
			Solucao.push_back(*c);
			Solucao.at(Solucao.size() - 1).setconteudo(VOrd[i].getPeso());
			Rest[Solucao.size() - 1] = CAP - VOrd[i].getPeso();

		}
		else
		{
			//caso contrário coloca o item no container de maior espaço restante
			Rest[best] -= VOrd[i].getPeso();
			Solucao.at(best).setconteudo(VOrd[i].getPeso());
			Solucao.at(best).additem(VOrd[i].getID());
			max = 0;
			valido = false;
			best = 0;
		}

	}
	delete[] Rest;
}

//Calcula o quão bom é uma solucao através da fórmula:
// Somatório de : (ID dos itens do container i) ao quadrado
double CalculaDistancia(vector<Container> Sx)
{
	double result=0;
	double temp=0;
	for (int i = 0; i < Sx.size(); i++)
	{
		for (int j = 0; j < Sx.at(i).getNumItens(); j++)
		{
			temp += Sx.at(i).getitem(j);
		}
		result += pow(temp, 2);
	}
	return result;
}

/*
SOLUCAO_RANDOMICA
Este método cria uma solução factível não ótima de forma aleatória. Utiliza-se da aleatoriedade para decidir
entre por um item em um container ou cria um container novo.
*/
void SolucaoRandomica()
{
	bool inclui = false;
	int resto;
	//Para cada item procura um container entre os existentes para pôr o item
	for (int i = 0; i < NumV; i++)
	{
		//Varre todos os containers procurando o primeiro que couber
			for (int j = 0; j < Solucao.size(); j++)
			{
				//Verifica se ele cabe no espaço restante
				resto = CAP - Solucao.at(j).getconteudo();
				if (VOrd[i].getPeso() <= resto)
				{
					inclui = true;
					//Verifica se o item tem conflito com algum que já está no container
					for (int k = 0; k < Solucao.at(j).getNumItens(); k++)
					{
						if (Solucao.at(j).getitem(k) == VOrd[i].getID())
						{
							i++;
							break;
						}
						if (VOrd[i].EhVizinho(Solucao.at(j).getitem(k)) || Solucao.at(j).getitem(k) == VOrd[i].getID())
						{
							inclui = false;
							break;
						}
					}
					if (inclui)
					{
						//se ele cabe e não possui conflito ele é posto no container
						//porém o container escolhido varia aleatóriamente entre um existente e um novo
						if (rand() % NumV > i)
						{
							Solucao.at(j).setconteudo(VOrd[i].getPeso());
							Solucao.at(j).additem(VOrd[i].getID());
						}
						else
						{
							Container *c = new Container();
							c->additem(VOrd[i].getID());
							Solucao.push_back(*c);
							Solucao.at(Solucao.size() - 1).setconteudo(VOrd[i].getPeso());
							resto = CAP;
						}
						break;
					}
				}
			}
		if (!inclui || resto < VOrd[i].getPeso())
		{
			//se o item não coube em nenhum container existente cria-se um novo
			Container *c = new Container();
			c->additem(VOrd[i].getID());
			Solucao.push_back(*c);
			Solucao.at(Solucao.size() - 1).setconteudo(VOrd[i].getPeso());
			resto = CAP;
		}
	}
}
/*
Esta função tem como objetivo melhorar um solucao ja existente, ela segue as seguintes etapa:
	1) Cria-se uma sequencia de tamanho proporcional a temperatura do SA
	2) Esta sequência terá valores aleatórios que indicam quais containers serão escolhidos
	3) Então, de dois em dois são realizadas trocas entre itens de forma que o objetivo seja
	diminuir o número de containers.
	4)A "Qualidade" da solução gerada em relação a anterior é verificada na função de CalculaDistancia()
*/ 
void CalculaProx(vector<Container>* prox,int temp)
{
	//Cria uma sequencia com tamanho variando de acordo com a temperatura
	int tamSeq = (temp*prox->size()) / TemperMAX; 
	if (tamSeq < 2)
	{
		//tem q ter no minimo dois containers
		tamSeq = 2; 
	}
	int *seq = new int[tamSeq];
	bool troca = 0;
	int itemC1[2] = { 0,0 }; //vetor para capturar os dados dos itens escolhidos, posição 0:id, posição 1: peso
	int itemC2[2] = { 0,0 }; //idem
	int aux;
	int postemp;
	for (int i = 0; i < tamSeq; i++)
	{
		//gera a sequencia
		seq[i] = rand() % prox->size(); 

	}
	//varre o a sequencia
	for (int i = 0; i < tamSeq - 1; i++)
	{
		// se foram gerados dois iguais nao troca OU se o tamanho do vetor foi excedido passa para a próxima troca
		if (seq[i] == seq[i + 1] || seq[i] >prox->size() || seq[i+1]>prox->size()) 
		{
			continue;
		}
		itemC1[0] = 0;
		itemC1[1] = 0;
		itemC2[0] = 0;
		itemC2[1] = 0;
		//Posicao 1 válida aleatória é gerada
		postemp = rand() % prox->at(seq[i]).getNumItens();
		//captura os dados do item
		itemC1[0] = prox->at(seq[i]).getitem(postemp);
		itemC1[1] = VOrd[prox->at(seq[i]).getitem(postemp)-1].getPeso();
		//Posicao 2 válida aleatória é gerada
		postemp = rand() % prox->at(seq[i + 1]).getNumItens();
		//captura os dados do item
		itemC2[0] = prox->at(seq[i + 1]).getitem(postemp);
		itemC2[1] = VOrd[prox->at(seq[i + 1]).getitem(postemp)-1].getPeso();

		if (itemC1[1] > itemC2[1])
		{
			//verifica se o item maior cabe no outro depois q o menor sair
			if (itemC2[1] + (CAP - prox->at(seq[i + 1]).getconteudo()) >= itemC1[1])
			{
				troca = true;
				// verifica se há conflito do item novo com os que já estão no container
				for (int j = 0; j < prox->at(seq[i + 1]).getNumItens(); j++)
				{
					if (VOrd[itemC1[0] - 1].EhVizinho(prox->at(seq[i + 1]).getitem(j)))
					{
						troca = false;
						break;
					}
				}
				// verifica se há conflito do item que saiu com os que já estão no outro container
				for (int j = 0; j < prox->at(seq[i]).getNumItens(); j++)
				{
					if (VOrd[itemC2[0] - 1].EhVizinho(prox->at(seq[i]).getitem(j)))
					{
						troca = false;
						break;
					}
				}
			}
			else
			{
				//se o item não cabe no outro container não troca;
				troca = false;
			}
		}
		else//se c2>=c1
		{
			//verifica se o item maior cabe no outro depois q o menor sair
			if (itemC1[1] + (CAP - prox->at(seq[i]).getconteudo()) >= itemC2[1])
			{
				troca = true;
				// verifica se há conflito do item novo com os que já estão no container
				for (int j = 0; j < prox->at(seq[i]).getNumItens(); j++)
				{
					if (VOrd[itemC2[0] - 1].EhVizinho(prox->at(seq[i]).getitem(j)))
					{
						troca = false;
						break;
					}
				}
				// verifica se há conflito do item que saiu com os que já estão no outro container
				for (int j = 0; j < prox->at(seq[i + 1]).getNumItens(); j++)
				{
					if (VOrd[itemC1[0] - 1].EhVizinho(prox->at(seq[i + 1]).getitem(j)))
					{
						troca = false;
						break;
					}
				}
			}
			else
			{
				//se o item não cabe no outro container não troca;
				troca = false;
			}
		}
		if (troca)
		{
			//Se a troca for possivel, remove-se um dos itens de sua origem e verifica se o container ficou vazio
			// se ficou vazio verifica se ele pode ser enviado para o outro sem mandar o outro item de volta
			//caso isso ocorra o container vazio é removido e a solução melhora
			prox->at(seq[i]).removeitem(itemC1[0], itemC1[1]); 
			if (prox->at(seq[i]).getNumItens() == 0)
			{
				if (itemC1[1] <= CAP - prox->at(seq[i + 1]).getconteudo())
				{
					prox->at(seq[i + 1]).additem(itemC1[0]);
					prox->at(seq[i + 1]).setconteudo(itemC1[1]);
					prox->erase(prox->begin() + seq[i]);
					break;
				}
			}
			prox->at(seq[i + 1]).additem(itemC1[0]);
			prox->at(seq[i + 1]).setconteudo(itemC1[1]);
			prox->at(seq[i + 1]).removeitem(itemC2[0], itemC2[1]);
			prox->at(seq[i]).additem(itemC2[0]);
			prox->at(seq[i]).setconteudo(itemC2[1]);

		}
	}
	delete[] seq;

}


/*
SIMULATED_ANNEALING
Esta técnica começa sua busca a partir de uma solução inicial qualquer.
O procedimento principal consiste em um loop ou laço que a cada iteração,
gera aleatoriamente uma solução vizinha da solução corrente.
*/
void SimulatedAnnealing()
{
	bool melhor = true;
	vector<Container> best;
	vector<Container> prox;
	double prob;
	double alpha = 0.999;
	double temp = TemperMAX;
	double epsilon = 0.001;
	double delta;
	//calcula-se a qualidade da solucao recebida
	double distancia = CalculaDistancia(Solucao);
	//passa a solucao corrente para uma proxima
	prox.assign(Solucao.begin(), Solucao.end());
	//Todo o processo abaixo é interrompido se: 1) o tempo acabar 2) A temperatura for menor que epsilon
	while (temp > epsilon && VerificaTempo())
	{
		//Tenta melhorar a solucao
		CalculaProx(&prox,temp);
		//verifica a diferenca dela para a anterior
		delta = CalculaDistancia(prox) - distancia;
		//A solucao gerada so vai menor que o delta se os itens estiverem mais "equilibrados"
		// com isso numa proxima iteracão pode ser possível diminuir o número de containers
		if (delta < 0)
		{
			melhor = true;
			Solucao.assign(prox.begin(),prox.end());
			best.assign(prox.begin(), prox.end());
			distancia = delta + distancia;
		}
		else
		{
			//aceita a solucao aleatoriamente
			prob = rand();
			if (prob < exp(-delta / temp))
			{
				melhor = false;
				Solucao.assign(prox.begin(), prox.end());
				distancia = delta + distancia;
			}
		}
		temp -=alpha;
	}
	if (!melhor)
	{
		//se a ultima solucao nao for a melhor, atribui a soluco final o valor da melhor encontrada.
		Solucao.assign(best.begin(), best.end());
	}

}

