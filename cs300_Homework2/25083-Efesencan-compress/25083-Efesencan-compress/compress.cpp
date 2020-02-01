#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "binarySearchTree.h"

using namespace std;
// Efe Sencan 2503
// This program compresses the file by giving the appropriate codes to the strings of the input, and stores it in a binary tree. 
void compress(ifstream & inputFile,binarySearchTree<string,int> & compressFile) // encoding the input file 
{
	ofstream outputFile;
	outputFile.open("compout.txt");
	int code = 256; // code variable starts from 256 because we already know the ascii codes of the single characters
	string fileName = "compin.txt";
	inputFile.open(fileName.c_str());
	char ch;
	string current = "",temp;
	char next;
	if(inputFile.get(ch)) // reading the first character of the file
	{
		current = ch;
	}
	while(inputFile.get(ch))
	{
		next = ch;
		temp = current+ next;
		if(compressFile.isInTree(temp)) // checking if the character pairs are already in the tree
		{
			current = current + next; // if so concatenate the current and the next character
		}
		else
		{
			if(current.length() == 1)  // if the length of the character is 1 than we can directly put its code to the outputFile
			{
				outputFile<<int(current[0])<<" ";
			}
			else
			{
				int code_number = compressFile.findCodeValue(current); // finding the code of the string 
				outputFile<<code_number<<" ";
				//cout<<code_number<<" ";// find the code of the string value in the tree and print the code
			}
			string value = current + next;
			if(value.length() >= 2)
			{
				if(code <4096) // if the code is greater or equal to 4096 than we will not insert that code to the tree
				{
					compressFile.insert(value,code);
					code++;	
				}
			}
			current = next;
		}
	}
	if(current.length() != 0) // if the length of the current is zero this means that the ile is empty so we will print anything to the output file
	{
		if(current.length() != 1) // if the length of the current is not 1 the this means we have that string in the tree otherwise we will print its ascii code
		{
			int code_number = compressFile.findCodeValue(current);
			outputFile<<code_number;
		}
		else
		{
			outputFile<<int(current.at(0))<<endl;
		}
	}
	
	outputFile.close();
	inputFile.close();
	//compressFile.printTree();
	//cout<<"----------------Encoded------------------"<<endl;
}

int main()
{
	binarySearchTree<string,int> compressFile;
	ifstream inputFile;
	compress(inputFile,compressFile);

	return 0;
}