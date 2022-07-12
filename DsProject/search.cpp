#include"search.h"
#include<fstream>
#include <iostream>
#include <string>
using namespace std;
void search::Append(string bookname)
{
	// create a new node 
	Node *Newnode = new Node;
	Newnode->name = bookname;
	Newnode->next = nullptr;
	//..........................................
	Node *temp = head;
	if (head == nullptr)
	{
		head = Newnode;
		size++;
	}
	else
	{
		while (temp->next != nullptr)
		{
			temp = temp->next;

		}
		temp->next = Newnode;
		size++;
	}
}
search::search()
{
	Append("Book1.txt");
	Append("Book2.txt");
	Append("Book3.txt");
}
void search::GetWord(string &word )
{
	int space = 0;
	cout << "Enter a Word you Want to search : ";
	cin.ignore();
	getline(cin, word);
	cout << "........................... Result .............................." << endl;
	for (int i = 0; i < word.size(); i++)
	{
		if (word[i] >= 65 && word[i] <= 90)
			word[i] += 32;
	}
	
}
int search::Mapping(string word)
{
	int map = 0;
	for (int i = 0; i < word.size(); i++)
		map = map + word[i];
	map = map % 300;
	return map;

}
int search::Mapping(string word, int end , int start )
{
	int map = 0;
	for (int i = start ; i < end; i++)
		map = map + word[i];
	map = map % 300;
	return map;

}
void search::find(string word, Data F[10])
{
	Node *temp = head;
	Node *arr[300];
	ifstream file;
	int f = 0;
	int lines[100], L = 0;
	//....................
	string line , letter;
	char letters[30];
	//..................................
	bool found1 = false , found2 = false;
	int gline = 0, number = 0,  space = 0;
	int split = 0;
	//............................
	int counter = 0, counter2 = 0, R = 0, map;
	// Find Space in the Word given 
	for (int i = 0; i < word.size(); i++)
		if (word[i] == ' ')
		{
			split = i;
			space++;
		}
	
	// ...................................... Main Loop ............................................

	while (true) // Loop of files 
	{
		L = 0;

		// loop intialization 
		for (int i = 0; i < 299; i++)
			arr[i] = nullptr;
		gline = 0, number = 0;
		file.open(temp->name);
		while (file.eof() == 0) // Loop of lines 
		{
			// Array Intialization 
			for (int i = 0; i < 299; i++)
				arr[i] = nullptr;
			// Loop intialization 
			counter = 0 , R = 0 ;
			getline(file, line);
			//Fix Sensitivity 
			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] >= 65 && line[i] <= 90)
					line[i] += 32;
			}
			gline++;
			//Creating Linked List 
			for (int i = counter; i < line.size(); i++, R++)
			{


				if (line[i] == ' ')
				{
					letter = letters;
					map = Mapping(letter, R , 0)  ;
					// create a new node 
					Node *Newnode = new Node;
					Newnode->name = letter;
					Newnode->next = nullptr;
					//..........................................
					Node *iemp = arr[map];
					if (arr[map] == nullptr)
						arr[map] = Newnode;
					else
					{
						while (iemp->next != nullptr)
						{
							iemp = iemp->next;

						}
						iemp->next = Newnode;
					}
					i++;
					R = 0;
					counter = i;

				}
				letters[R] = line[i];

			}
			// Search for a word 
			
			if (space == 0)
			{
				map = Mapping(word);
				Node *lemp = arr[map];
				while (true)
				{
					if (arr[map] == nullptr)
						break;
					for (int i = 0; i < word.size(); i++)
					{
						if (lemp->name[i] == word[i])
							counter2++;
						else
						{
							counter2 = 0;
							break;
						}
					}
					if (counter2 != 0)
					{
						lines[L] = gline;
						L++;
						number++;
					}
						
					//..................... Loop Small Linked List .....................
					if (lemp->next == nullptr)
						break;
					lemp = lemp->next;
					counter2 = 0;
					

				}
			}
			else
			{
				// .................... Split Word ..................................
				found1 = false, found2 = false;
				int map2 , round , word1 = 0, word2 = 0 ;
				counter2 = 0;
				map = Mapping(word, split , 0 );
				map2 = Mapping(word, word.size(), split + 1);
				Node * two = arr[map];
				while (true)
				{
					if (arr[map] == nullptr)
						break;
					for (int i = 0; i < split; i++)
					{
						if (two->name[i] == word[i])
							word1++;
						else
						{
							word1 = 0;
							break;
						}
					}
					if (word1 != 0)
					{
						found1 = true;

					}
					if (two->next == nullptr)
						break;
					two = two->next;
				}
				word1 = 0;
				Node * one = arr[map2];
				while (true)
				{
					if (arr[map2] == nullptr)
						break;
					for (int i = split + 1 , j = 0 ; i < word.size(); i++ , j++)
					{
						if (one->name[j] == word[i])
							word2++;
						else
						{
							word2 = 0;
							break;
						}
					}
					if (word2 != 0)
					{
						found2 = true;
					}
					if (one->next == nullptr)
						break;
					one= one->next;
				}

				word2 = 0;
				if (found1 == true && found2 == true)
				{
					int K = 0;
					for (int i = 0 ; i < line.size() ;i++)
					{
						round = line.find(word, K);
						if (round != -1)
						{
							lines[L] = gline;
							L++;
							number++;
							K = round + word.size();
						}
					}
					
					
						
				}
				found1 = found2 = false;
			}
		}
		file.close();
		//.......................... Entering Data .................................
		F[f].wnum = number;
		F[f].bookname = temp->name;
		F[f].arrnum = L;
		for (int q = 0; q < L; q++)
			F[f].lines[q] = lines[q];
		f++;
		// ............................loop Large Linked List ....................
		if (temp->next == nullptr)
			break;
		
		temp = temp->next;
		
	}
}
void search::Sorting(Data F[10])
{
	int temp;
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 3; j++)
		{
			if (F[i].wnum > F[j].wnum)
			{
				swap(F[i].wnum, F[j].wnum);
				swap(F[i].bookname, F[j].bookname);
				swap(F[i].arrnum, F[j].arrnum);
				swap(F[i].lines, F[j].lines);
			}
		}
	}

	

	
}
void search::View(Data F[10])
{
	for (int i = 2; i >= 0; i--)
	{
		if (F[i].wnum > 0)
		{
			cout << F[i].bookname << endl;
			cout << "Found " << F[i].wnum << " Times "<< endl;
			cout << " At line : ";
			for (int j = 0; j < F[i].arrnum; j++)
				cout << F[i].lines[j] << "  ";
			cout << endl;
			cout << "..............................................." << endl;
		}
		
	}
}
