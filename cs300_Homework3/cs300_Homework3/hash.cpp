#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "hashTable.h"
#include <vector>

// Efe Sencan 25083
// This program collects the data of average number of probes needed for insert,find, delete(succesful/failed) operation for each spesific load factor of the hash table

using namespace std;

struct arrayData // We collect the data for each spesific operation on the arrays, therefore we store 2 information in the struct
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
	for(int value = 0; value<3; value++) // since we will experince 3 cases, our outer loop will be run for 3 times
	{	
		ofstream graph1,graph2,graph3,outputFile;
		int insert;
		int deletion;
		int find;
		if(value == 0) // for the first case
		{
			srand(1);
			graph1.open("Case1.csv");
			insert = 6;
			deletion = 1;
			find = 1;
		}
		else if(value == 1) // for the second case
		{
			srand(4);
			graph2.open("Case2.csv");
			insert = 4;
			deletion = 2;
			find = 2;
		}
		else if(value ==2) // for the third case
		{
			srand(6);
			graph3.open("Case3.csv");
			insert = 2;
			deletion = 1;
			find = 5;
		}
		HashTable mainTable(10007); // we initalize our hash table and arrays
		arrayData successfulInsert[10008];
		arrayData failInsert[10008];
		arrayData successfulFind[10008];
		arrayData failFind[10008];
		arrayData successfulRemove[10008];
		arrayData failRemove[10008];
		
		int numberofTransaction = 0;

		while(mainTable.getCurrentSize() != mainTable.getArraySize() && numberofTransaction<1000000) // our operations on hash table will continue until the table becomes full or out total number of transactions reach 1000000
		{

			int random = rand(); // we generate a random number
			random = random % (10*10007);
			int m = rand() % 8; // we again use random generator in order to decide the opeation
			if(m >= 0 && m <= insert -1) // insertion case 
			{
				if(mainTable.couldInsert(random)) // this function checks whether the number could be inserte to the table, if so it inserts and return true, otherwise it returns false
				{
					successfulInsert[mainTable.getCurrentSize() - 1].transaction++;
					successfulInsert[mainTable.getCurrentSize() - 1].totalProbes+= mainTable.getProbeNumber();
				}
				else
				{
					failInsert[mainTable.getCurrentSize()].transaction++;
					failInsert[mainTable.getCurrentSize()].totalProbes+= mainTable.getProbeNumber();
				}
				numberofTransaction++;
			}
			else if(m>= insert && m<= (insert + deletion -1)) // deletion case 
			{
				if(mainTable.couldRemove(random)) // this function checks whether the that number could be removed from the table, if so it removes and returns true otherwise it returns false
				{
					successfulRemove[mainTable.getCurrentSize() + 1].transaction++;
					successfulRemove[mainTable.getCurrentSize() + 1].totalProbes += mainTable.getProbeNumber();
				}
				else
				{
					failRemove[mainTable.getCurrentSize()].transaction++;
					failRemove[mainTable.getCurrentSize()].totalProbes += mainTable.getProbeNumber();
				}
				numberofTransaction++;
			}
			else // finding case
			{
				if(mainTable.couldFind(random)) // this function checks whether that number is in the hash table if so it returns true, therwise it returns false
				{
					successfulFind[mainTable.getCurrentSize()].transaction++;
					successfulFind[mainTable.getCurrentSize()].totalProbes += mainTable.getProbeNumber();
				}
				else
				{
					failFind[mainTable.getCurrentSize()].transaction++;
					failFind[mainTable.getCurrentSize()].totalProbes += mainTable.getProbeNumber();
				}
				numberofTransaction++;
			}
		}
		//cout<<numberofTransaction<<" "<<mainTable.getCurrentSize()<<endl;
		for(int i = 0; i<10008; i++) // since we need to calculate the average number of probes, we need to check whether transaction number is zero in order to avoid the zero division
		{
			if(successfulInsert[i].transaction == 0)
				successfulInsert[i].transaction++; 
			
			if(failInsert[i].transaction == 0)
				failInsert[i].transaction++;
			
			if(successfulRemove[i].transaction == 0)
				successfulRemove[i].transaction++;

			if(failRemove[i].transaction == 0)
				failRemove[i].transaction++;

			if(successfulFind[i].transaction == 0)
				successfulFind[i].transaction++;
			if(failFind[i].transaction == 0)
				failFind[i].transaction++;
			if(value == 0) // we transfer the data to excel for the first case
			{
				graph1<<i/10007.0<<";";
				graph1<<(successfulInsert[i].totalProbes)/(successfulInsert[i].transaction)<<" ;"<<" ;";

				graph1<<i/10007.0<<";";
				graph1<<(failInsert[i].totalProbes)/(failInsert[i].transaction)<<";"<<" ;";

				graph1<<i/10007.0<<";";
				graph1<<(successfulRemove[i].totalProbes)/(successfulRemove[i].transaction)<<";"<<";";

				graph1<<i/10007.0<<";";
				graph1<<(failRemove[i].totalProbes)/(failRemove[i].transaction)<<";"<<";";

				graph1<<i/10007.0<<";";
				graph1<<(successfulFind[i].totalProbes)/(successfulFind[i].transaction)<<";"<<";";

				graph1<<i/10007.0<<";";
				graph1<<(failFind[i].totalProbes)/(failFind[i].transaction)<<endl;
			}
			
			else if(value == 1)  // we transfer the data to excel for the second case
			{
				graph2<<i/10007.0<<";";
				graph2<<(successfulInsert[i].totalProbes)/(successfulInsert[i].transaction)<<" ;"<<" ;";

				graph2<<i/10007.0<<";";
				graph2<<(failInsert[i].totalProbes)/(failInsert[i].transaction)<<";"<<" ;";

				graph2<<i/10007.0<<";";
				graph2<<(successfulRemove[i].totalProbes)/(successfulRemove[i].transaction)<<";"<<";";

				graph2<<i/10007.0<<";";
				graph2<<(failRemove[i].totalProbes)/(failRemove[i].transaction)<<";"<<";";

				graph2<<i/10007.0<<";";
				graph2<<(successfulFind[i].totalProbes)/(successfulFind[i].transaction)<<";"<<";";

				graph2<<i/10007.0<<";";
				graph2<<(failFind[i].totalProbes)/(failFind[i].transaction)<<endl;
			}
			else if(value == 2) // we transfer the data to excel for the third case
			{
				graph3<<i/10007.0<<";";
				graph3<<(successfulInsert[i].totalProbes)/(successfulInsert[i].transaction)<<" ;"<<" ;";

				graph3<<i/10007.0<<";";
				graph3<<(failInsert[i].totalProbes)/(failInsert[i].transaction)<<";"<<" ;";

				graph3<<i/10007.0<<";";
				graph3<<(successfulRemove[i].totalProbes)/(successfulRemove[i].transaction)<<";"<<";";

				graph3<<i/10007.0<<";";
				graph3<<(failRemove[i].totalProbes)/(failRemove[i].transaction)<<";"<<";";

				graph3<<i/10007.0<<";";
				graph3<<(successfulFind[i].totalProbes)/(successfulFind[i].transaction)<<";"<<";";

				graph3<<i/10007.0<<";";
				graph3<<(failFind[i].totalProbes)/(failFind[i].transaction)<<endl;
			}
		}
	}
	return 0;
}