

#include "Header.h"
#include "Metodos.cpp"
#include "BronKerbosch.cpp"
#include "Sorting.cpp"
#include "Entrada_e_Saida.cpp"

using namespace std;

int main(int argc, char*argv[])
{
	srand(time(NULL));
	duration<double> time_span2;
	t1 = high_resolution_clock::now();
	int Arq_entrada = 1, Arq_saida = 2, Tempo = 3, Metodo = 4, P1 = 5, P2 = 6;
	LeituraDeDados(argv[Arq_entrada]);
	TMax = atoi(argv[Tempo]);
	switch (*argv[Metodo])
	{
	case '1':
		cout << "FF";
		if (argc > 5)
		{
			//FirstFit decrescente
			quickSort(VOrd, 0, NumV - 1, 2);
		}
		//FirstFit
		FirstFit();
		break;
	case '2':
		cout << "CQFF";
		//Firstfit com clique
		CalculoDoGrauMod();
		quickSort(VOrd, 0, NumV - 1, 3);
		CliqueMaximo();
		break;
	case '3':
		cout << "BF";
		BestFit();
		break;
	case '4':
		cout << "WF";
		WorstFit();
		break;
	case '5':
		cout << "SA:";
		TemperMAX = atoi(argv[P1]);
		if (argc > 6)
		{
			switch (*argv[P2])
			{
			case '1':
				cout << "FF";
				FirstFit();
				break;
			case '2':
				cout << "BF" << endl;
				BestFit();
				break;
			case '3':
				cout << "WF" << endl;
				WorstFit();
				break;
			case '4':
				cout << "SR";
				SolucaoRandomica();
				break;
			}
		}
		else
		{
			SolucaoRandomica();
		}
		SimulatedAnnealing();

		break;
	}
	cout << endl << "*" << Solucao.size() << "*" << endl;
	Saida(argv[Arq_saida]);
	t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
	cout << "Tempo: " << time_span.count() << endl;
	delete[] V;
	delete[] VOrd;
	//desalocar outros 
	return 0;
}