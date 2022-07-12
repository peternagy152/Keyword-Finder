#include <string>
using namespace std;
struct Data
{
	string bookname;
	int lines[100];
	int arrnum;
	int wnum;
	
};
class Node
{
public :
	string name;
	Node *next = nullptr;
};
class search
{
private:
	Node *head = nullptr;
	int size = 0;
public :
	search();
	void Append(string bookname);
	void  GetWord(string &word );
	int Mapping(string word);
	int Mapping(string word, int R , int start );
	void find(string word , Data F[10]);
	void Sorting(Data F[10]);
	void View(Data F[10]);
};