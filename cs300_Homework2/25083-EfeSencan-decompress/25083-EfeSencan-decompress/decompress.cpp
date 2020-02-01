#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

// Efe Sencan 25083
// This program decompresses the integer codes and convertes them to the corresponding string value

void decompress(ifstream & inputFile,string  arr[4096])
{
	int count = 256;
	ofstream outputFile;
	outputFile.open("decompout.txt");
	string fileName = "compout.txt";
	inputFile.open(fileName.c_str());
	int code;
	string decode = "",temp = "";
	if(inputFile >> code) // getting the first code of the file
	{
		decode = arr[code];
		outputFile<<decode;
	}
	while(inputFile >> code) 
	{
		if(arr[code] != "") // if the array's corresponding index value is not an empty string which means we have that value in the string
		{
			temp = decode;
			decode = arr[code];
			arr[count] = temp + decode[0];
			count++;
		}
		else
		{
			arr[count] = decode + decode[0];
			decode = arr[code];
			count++;
		}
		outputFile << decode; // printing that corresponding string to the outputfile
	}
	outputFile.close();
	inputFile.close();
	//cout<<"----------------Decoded--------------"<<endl;
}

int main()
{
	ifstream inputFile;
	string arr[4096];
	for(int i = 0;i<4096; i++) // constructing an array of length 4096 and adding the characters of the ascii table since we have 256 of them, otherwise we assign an empty string to the that index of the array
	{
		if(i<256)
		{
			arr[i] = char('A' + i -65);
		}
		else
		{
			arr[i] = "";
		}
	}
	decompress(inputFile,arr);


	return 0;
}