#include "search.h"
#include<string>
#include <iostream>
using namespace std;
int main()
{
	search obj;
	Data F[10];
	string word;
	int openion;
	while (true)
	{
		
		cout << "1. Search a word            2. Exit    " << endl;
		cin >> openion;
		if (openion == 2)
			break;
		if (openion == 1)
		{
			obj.GetWord(word);
			obj.find( word , F );
			obj.Sorting(F);
			obj.View(F);
		}
		
	}
	//...............................
	system("pause");
	return 0;
}