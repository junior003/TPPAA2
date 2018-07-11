#include "Header.h"

void LeituraDeDados(char* nome)
{
	ifstream arq;
	char X, ed[5];
	int N;
	int M;
	int l;
	string Rest;
	string num_str;
	arq.open(nome, ios::in);
	arq >> N >> M;
	CAP = M;
	NumV = N;
	V = new Item[NumV];
	ident = 1;
	VOrd = new Item[NumV];
	l = N;
	int contCol = 0;
	
	//A estrategia de leitura aqui é de ler a linha inteira e ir capturando os valores um a um
	
	while (!arq.eof())
	{
		for (int i = 0; i < l + 1; i++)
		{
			//pega toda a linha
			getline(arq, Rest);
			for (int k = 0; k<Rest.length(); k++)
			{
				//entra se for número
				if (Rest[k] != ' ' && k != Rest.length() - 1)
				{
					num_str += Rest[k]; //concatena os algoritmos
				}
				else
				{
					if (k == Rest.length() - 1)
					{
						//se for quebra de linha tem que concatenar +1 vez
						num_str += Rest[k];
					}
					N = atoi(num_str.c_str());
					contCol++;
					if (contCol == 2)//se  for a segunda coluna do arquivo lê o peso
					{
						V[i - 1].setPeso(N);
						VOrd[i - 1].setPeso(N);
					}
					if (contCol>2) //acima disso são os conflitos
					{
						//cria aresta de i para N e vice-versa
						V[i - 1].addVizinhoPOS(N - 1);
						VOrd[i - 1].addVizinhoPOS(N - 1);
						V[N - 1].addVizinhoPOS(i - 1);
						VOrd[N - 1].addVizinhoPOS(i - 1);
					}
					num_str = "";
				}
			}
			Rest = "";
			contCol = 0;
		}
	}
	arq.close();
}

void Saida(char* nome)
{
	ofstream arq;
	arq.open(nome, ios::out);
	arq << Solucao.size() << '\n';
	for (int i = 0; i < Solucao.size(); i++)
	{
		arq << Solucao.at(i).getNumItens() << ' ';
		for (int j = 0; j<Solucao.at(i).getNumItens(); j++)
		{
			arq << Solucao.at(i).getitem(j) << ' ';
		}
		arq << '\n';
	}
	arq.close();
}
