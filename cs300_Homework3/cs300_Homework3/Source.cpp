#include "hashTable.h"
#include <fstream>

struct arrayData
{
	int transaction;
	int totalProbes;
	arrayData()
	{
		transaction = 0;
		totalProbes = 0;
	}
	arrayData(int trans, int probes)
	{
		transaction = trans;
		totalProbes = probes;
	}
};

int main()
{
	/*arrayData successfulInsert[10008];
	arrayData failInsert[10008];
	arrayData successfulFind[10008];
	arrayData failFind[10008];
	arrayData successfulRemove[10008];
	arrayData failRemove[10008];
	HashTable table(10007);
	ofstream deneme;
	deneme.open("deneme1.csv");

	int a = 1,b = 10008,c= 2,d = 3;

	table.couldInsert(a);
	table.couldInsert(b);
	cout<<"Suc Insert probe: "<<table.getProbeNumber()<<endl;
	table.couldInsert(c);
	table.couldInsert(d);
	if(table.couldRemove(b))
	{
		successfulRemove[table.getCurrentSize() + 1].transaction++;
		successfulRemove[table.getCurrentSize() + 1].totalProbes += table.getProbeNumber();
	}
	for(int i = 0; i<10007; i++)
	{
		deneme << successfulRemove[i].totalProbes<<endl;
	}
	*/
	
	
	for (int i = 0; i < 500; i++)
	{
		int num = rand() % (10*10007);
		int m = num  % 8;
		cout<<num<<endl;
	}

	

	return 0;
}