
#include "stdafx.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <time.h> 
#include <Windows.h>

using namespace std;

class Gc
{
public:

	int n;
	int pop;
	vector <vector<int>> matrix;
	vector <vector<int>> population;
	vector <int> scores;

	Gc() //wczytywanie z pliku
	{
		

		fstream file;
		string line;
		file.open("file.txt", ios::in);
		getline(file, line);
		n = atoi(line.c_str());

		for (int i = 0; i < n; i++)
		{
			vector<int> vec;
			matrix.push_back(vec);
			for (int j = 0; j < n; j++)
			{
				matrix[i].push_back(0); //zerowanie wektora
			}
		}

		while (getline(file, line)) //wczytywanie z pliku
		{
			int i = atoi(line.substr(0, line.find(" ")).c_str()) - 1;
			int j = atoi(line.substr(line.find(" ")).c_str()) - 1;
			matrix[i][j] = -1;
			matrix[j][i] = -1;
		}	

		if (n % 2 == 0) pop = n;
		else pop = n - 1;
	}

	void show_graph()
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << matrix[i][j];
			}
			cout << endl;
		}
	}

	void generate_population() //tworzenie populacji początkowych
	{
		int tcolor;
		bool loop = true;
		vector <int> chrom;
		for (int i = 0; i < n; i++) chrom.push_back(0);
		

		for (int i = 0; i < n; i++)
		{	
			while (loop)
			{
				loop = false;
				tcolor = rand() % n + 1;
				for (int j = 0; j < n; j++)
				{
					if (matrix[i][j] == -1 && chrom[j] == tcolor)
					{
						loop = true;
					}
				}
			}
			loop = true;
			chrom[i] = tcolor;
		}
		population.push_back(chrom);
	}

	void count_scores() //liczenie punktów
	{
		for (int i = 0; i < population.size(); i++)
		{
			vector <int> temp;
			for (int j = 0; j < population[i].size(); j++)
			{
				if (find(temp.begin(), temp.end(), population[i][j]) != temp.end())
				{
					/* v contains x */
				}
				else
				{
					/* v does not contain x */
					temp.push_back(population[i][j]);
				}
			}
			
			scores.push_back(temp.size());
		}
	}


};



int main()
{
	srand(time(NULL));
	Gc gc;
	//gc.show_graph();
	
	
	for (int i = 0; i < gc.pop; i++) //generowanie początkowej populacji
	{
		gc.generate_population();
	}

	gc.count_scores(); //obliczanie punktów dla każdego osobnika
	for (int i = 0; i < gc.pop; i++)
	{
		//for (int j = 0; j < gc.pop; j++) cout << gc.population[i][j]<<"-";
		cout << "|"<<gc.scores[i] << "|" << endl;
	}

	system("pause");

    return 0;
}

