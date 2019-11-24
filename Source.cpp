#include <iostream>
#include <conio.h>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

struct proceso {
	int at, bt, wt, tat, bt_inicial;
	int name;
	proceso()
	{
		name = 0;
		bt_inicial = 0;
		at = bt = wt = tat = 0;
	}
};

void sumar_procesos(vector<proceso> *arr, int n)
{
	srand(time(nullptr));
	for (int i = 0; i < n; i++)
	{
		proceso aux;
		aux.at = rand() % 9; aux.bt = rand() % 10 + 1; aux.name = i + 1;
		aux.bt_inicial = aux.bt;
		arr->push_back(aux);
	}
}

void ordenar(vector<proceso>*arr)
{
	sort(arr->begin(), arr->end(), [](proceso a, proceso b) {return a.at < b.at; });
}

void print(const vector<proceso>*arr)
{
	for (int i = 0; i < arr->size(); i++)
	{
		cout << arr->at(i).name << "\t " << arr->at(i).at << "\t " << arr->at(i).bt_inicial << "\t " << arr->at(i).wt << "\t " << arr->at(i).tat << "\t " << endl;
	}
}


int main()
{
	int time = 0;
	int time_quantum = 0, total_burst_time = 0;

	int total_tat = 0, total_wt = 0;

	vector<proceso> arr;
	vector<proceso> res;
	
	for (int i = 0; i < 5; i++)
	{
		proceso aux;
		cout << "Ingrese bt: "; cin >> aux.bt;
		cout << "Ingrese at: "; cin >> aux.at;
		aux.bt_inicial = aux.bt;
		aux.name = i + 1;
		arr.push_back(aux);
	}
	
	ordenar(&arr);
	cout << "ID \t" << "At \t" << "Bt \t" << "Wt \t" << "Tat \t" << endl;
	print(&arr);

	cout << endl << endl;

step2:
	total_burst_time = 0;
	time_quantum = 0;
	int n = 0;

	for (int i = 0; i < arr.size(); i++)
	{
		if (arr.at(i).at <= time)
		{
			total_burst_time += arr.at(i).bt;
			n++;
		}
	}

	time_quantum = 4;

	int i = 0;

	while (i < n)
	{
		if ((*arr.begin()).bt <= time_quantum)
		{
			time = time + (*arr.begin()).bt;

			(*arr.begin()).wt = time - (*arr.begin()).bt_inicial - (*arr.begin()).at;

			(*arr.begin()).tat = (*arr.begin()).bt_inicial + (*arr.begin()).wt;

			res.push_back((*arr.begin()));

			arr.erase(arr.begin());
		}
		else
		{
			time += time_quantum;

			(*arr.begin()).bt = (*arr.begin()).bt - time_quantum;

			proceso aux;

			aux = (*arr.begin());
			arr.erase(arr.begin());
			arr.push_back(aux);
		}
		i++;
	
	}

	if (!arr.empty())
		goto step2;

	print(&res);

	for (int i = 0; i < res.size(); i++)
	{
		total_tat += res.at(i).tat;
		total_wt += res.at(i).wt;
	}

	cout << endl;

	cout << "Atat: " << (float)total_tat / res.size() << endl;
	cout << "Awt : " << (float)total_wt / res.size()<< endl;

	_getch();
}
