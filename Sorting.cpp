#include "Header.h"
#include "Item.h"
//as funcoes a seguir sao do quicksort
void swap(Item* a, Item* b)
{
	Item t = *a;
	*a = *b;
	*b = t;
}

int partition(Item arr[], int low, int high,int m)
{
	int pivot;
	if (m == 1 || m == 2)
	{
		pivot = arr[high].getGrau();    //pivo
	}
	if (m == 3)
	{
		pivot = arr[high].getGrauMod();    //pivo
	}
	
	int i = (low - 1);  // Indice do menor elemento

	for (int j = low; j <= high - 1; j++)
	{
		//Se o elemento corrente eh maior ou igual o pivo
		if (m == 1 || m == 2)
		{
			if (arr[j].getGrau() >= pivot)
			{
				i++;    // incrementa o indice do maior elemento
				swap(&arr[i], &arr[j]);
			}
		}
		if (m == 3)
		{
			if (arr[j].getGrauMod() >= pivot)
			{
				i++;    // incrementa o indice do maior elemento
				swap(&arr[i], &arr[j]);
			}
		}
		
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(Item arr[], int low, int high,int m)
{
	if (low < high)
	{
		int pi = partition(arr, low, high,m);
		// separadamente ordena os elementos antes e depois da particao
		quickSort(arr, low, pi - 1,m);
		quickSort(arr, pi + 1, high,m);
	}
}
