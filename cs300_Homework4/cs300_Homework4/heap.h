#ifndef _HEAP
#define _HEAP
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct heapElement // in the heap we will store the height and the label
{
	int height;
	int label;
	heapElement()
	{

	}
	heapElement(int input_height, int input_label)
	{
		height = input_height;
		label = input_label;
	}
};

	
class Heap
{
public:
	explicit Heap(int & size) // constructor of the heap array
	{
		currentSize = 0;
		heapArray.resize(size + 1);
		location.resize(size + 1);
	}
	~Heap()// destructor
	{

	}
	bool isEmpty(); // checking if the array is empty
	void insert(int & value,int & label); // inserting element in to the heap
	int remove(int label); // removing element fro mthe heap
	int getMax(); // reaching the element with the maximum height
private:
	int currentSize;
	vector<heapElement> heapArray;
	vector<int> location;
	void buildHeap(vector<int> & items);
	void percolateDown(int hole);

};
	
bool Heap::isEmpty() 
{
	if(currentSize == 0) // checking if the currentsize is zero if so return true otherwise false
	{
		return true;
	}
	return false;
}

void Heap::insert(int & value,int & label)
{
	heapElement element(value,label);
	if(currentSize == heapArray.size( )-1) // constructing the heap again if we need extra space
	{
		heapArray.resize(heapArray.size( ) * 2 );
	}
	int hole = ++currentSize; // incrementing the current size
	for(; hole > 1 && value > heapArray[hole/2].height; hole/=2)
	{
		heapArray[hole] = heapArray[hole/2];
		location[heapArray[hole].label] = hole; // updating the urrent location of the element
	}
	heapArray[hole] = element;
	location[element.label] = hole; // updating the urrent location of the element
}

void Heap::buildHeap(vector<int> & items) 
{
	for(int i = 0; i<items.size(); i++)
	{
		heapArray[i].height = items[i];
	}
	currentSize = items.size();
	for(int i = currentSize / 2; i > 0; --i)
		percolateDown(i);
}

void Heap::percolateDown(int hole) // we use percolate down when we delete the element with the given label from the heap in order maintain the max -heap property
{
	int child;
	heapElement temp = heapArray[hole];
	for(; hole*2<= currentSize; hole = child)
	{
		child = hole*2;
		if(child != currentSize && heapArray[child + 1].height > heapArray[child].height) 
		{
			child++; // reaching the maximum child
		}
		if(heapArray[child].height > temp.height)
		{
			heapArray[hole] = heapArray[child];
			location[heapArray[hole].label] = hole; // updating the current location of the element
		}
		else
			break;
	}
	heapArray[hole] = temp;
	location[temp.label] = hole; // updating the current location of the element
}

int Heap::remove(int label)
{
	if(!isEmpty()) // if the heap is not empty we will remove the element with the given label
	{
		int index = location[label];
		int value = heapArray[index].height;
		heapArray[index] = heapArray[currentSize--]; 
		percolateDown(index);
		return value;
	}
	cout<<"Heap is  empty"<<endl;
}

int Heap::getMax() // taking the first element which is the maximum one
{
	if(!isEmpty())
		return heapArray[1].height;
	return 0;
}

#endif