#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "linkedlist.h"

using namespace std;
// Efe Sencan 25083
// this program searches the number of occurences and the document number that contains the words entered by the user
void readFile(ifstream & inputFile, string fileName,LinkedList & myList) // this function reads the pair of words and the document number in the each line of the file and adds it to the linked list
{
	inputFile.open(fileName.c_str());
	string line,name;
	int number;
	while(getline(inputFile,line)) // reading the file line by line
	{
		istringstream sentence(line);
		sentence >> name;
		sentence >> number;
		myList.addInOrder(name,number); // calling the function that adds the string and integers values to the linked list in a sorted manner 
	}
}

string lowering(string n) // making the each character of the words lowercase and return the newly formed string
{
	string temp = n;
	for(int i = 0; i < n.length(); i++)
	{
		if(n[i] >= 'A' && n[i] <= 'Z')
			temp[i] = temp[i] - ('Z' - 'z');
	}
	return temp;
}

void selectionSort(vector<string> & my_vec) // sorting the words in the alphabetical order in the vector
{
	int i,j;
	string temp = "";
	for(i=0; i<my_vec.size(); i++)
	{
		for(j=i+1; j<my_vec.size(); j++)
		{
			if(lowering(my_vec[i])>lowering(my_vec[j]))
			{
				temp=my_vec[i];
				my_vec[i]=my_vec[j];
				my_vec[j]=temp;
			}
		}
	}
}

int main()
{
	ifstream inputFile;
	string fileName = "docdb.txt";
	LinkedList myList;
	readFile(inputFile,fileName,myList);
	int number;
	string word, search;
	cin>>number;
	while(number > 0) // we will not deal with the input if the first integer number is less than 1
	{
		vector<string>my_vec; 
		getline(cin,word);
		istringstream line(word);
		while(line >> search)
		{
			my_vec.push_back(search); 
		}
		for(int i = 0; i<my_vec.size(); i++)
		{
			cout<<my_vec[i]<<" ";
		}
		selectionSort(my_vec);
		myList.searchingWords(number,my_vec);
		cin>>number;
	}
	//cout<<endl;

	return 0;
}