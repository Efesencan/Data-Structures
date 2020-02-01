#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "heap.h"

using namespace std;

// Efe Sencan 25083
struct x_coord 
{
	int x_value;
	string position;
	int label;
	int y_value;
};

void merge(vector<x_coord> & a, vector<x_coord> & tempArray,int leftPos, int rightPos, int rightEnd) // sorting the elements according to their x coordinate values
{
	int leftEnd = rightPos - 1;
	int tempPos = leftPos;
	int numElements = rightEnd - leftPos +1;

	while(leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if(a[leftPos].x_value <= a[rightPos].x_value)
			tempArray[tempPos ++] = a[leftPos ++];
		else
			tempArray[tempPos ++] = a[rightPos++];
	}

	while(leftPos <= leftEnd)
	{
		tempArray[tempPos ++] = a[leftPos ++];
	}
	while (rightPos <= rightEnd)
	{
		tempArray[tempPos ++] = a[rightPos++];
	}

	for(int i = 0; i<numElements; i++,rightEnd--)
	{
		a[rightEnd] = tempArray[rightEnd];
	}

}

void mergeSort(vector<x_coord> & a,vector<x_coord>tempArray,int left,int right)
{
	if(left < right)
	{
		int center = (left + right) / 2;
		mergeSort(a,tempArray,left,center);
		mergeSort(a,tempArray,center + 1,right);
		merge(a,tempArray,left,center + 1,right);
	}
}

void mergeSort(vector<x_coord> & a)
{
	vector<x_coord> tempArray(a.size());
	mergeSort(a,tempArray,0,a.size()-1);
}

int main()

{
	vector<x_coord>elements;
	ifstream inputFile;
	int buildings = 0,left,right,middle;
	string line;
	inputFile.open("input.txt");
	bool isTrue = true;
	int count = 0;
	while(getline(inputFile,line)) // reading the files line by line
	{
		if(line != "")
		{
			istringstream sentence(line);
			if(isTrue)
			{
				sentence>>buildings; // we get the total number of buildings
				isTrue = false;
			}
			else
			{ 
				x_coord first_item,second_item;  // we read the properties of the object and assign it to the struct of the element
				sentence>>left; 
				first_item.label = count;
				first_item.position = "left";
				first_item.x_value = left;
				sentence>>middle;
				first_item.y_value = middle;
				sentence >> right;
				second_item.label = count;
				second_item.position = "right";
				second_item.x_value = right;
				second_item.y_value = middle;
				elements.push_back(first_item);
				elements.push_back(second_item);
			}
			count++;
		}
	}
	mergeSort(elements); // calling the merge sort function to sort elements
	Heap heapArr(buildings); // constructing the heap
	int maximumHeight = 0, currentHeight = INT_MIN;
	int max = 0,second = 0;
	if(elements[0].x_value != 0) // if the first elements x coordinate is not zero we directly print 0
	{
		cout<<0<<" "<<0<<endl; 
	}
	for(int i = 0; i<elements.size(); i++)
	{
		if(elements[i].position == "left") // if the position of the element is left we will insert element to the heap
		{
			
			heapArr.insert(elements[i].y_value , elements[i].label);
			if(maximumHeight != heapArr.getMax() && max != heapArr.getMax())
			{
				maximumHeight = heapArr.getMax();
				if(elements[i].x_value != elements[i + 1].x_value && (currentHeight != maximumHeight || currentHeight < 0)) // if the maximum height of the array is changed adter inserting that we print that cordinate
				{
					cout<<elements[i].x_value<<" "<<heapArr.getMax()<<endl;
					currentHeight = heapArr.getMax(); // every time we store the previous maximum height of the heap
				}
			}	
		}
		else if(elements[i].position == "right")  // if the position of the element is right we will remove element to the heap
		{
			heapArr.remove(elements[i].label);
			if(maximumHeight != heapArr.getMax())
			{
				maximumHeight = heapArr.getMax();
				if(i == elements.size() -1 )
					cout<<elements[i].x_value<<" "<<heapArr.getMax()<<endl;
				else
				{
					if(elements[i].x_value != elements[i + 1].x_value && (currentHeight != maximumHeight || currentHeight < 0)) // if the maximum height of the array is changed after removing that we print that cordinate
					{
						cout<<elements[i].x_value<<" "<<heapArr.getMax()<<endl;
						currentHeight = heapArr.getMax(); 
					}
				}
			}	
		}
	}
	return 0;
}