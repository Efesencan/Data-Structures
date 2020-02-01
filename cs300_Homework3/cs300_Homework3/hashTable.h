#ifndef _HASHTABLE
#define _HASHTABLE
#include <vector>
#include <iostream>
using namespace std;
class HashTable
{
public:
	explicit HashTable(int size);
	bool couldFind(int & num);
	void makeEmpty();
	bool couldInsert(int & num);
	bool couldRemove(int & num);
	bool isInTable(int & num);
	int hash(int & key);
	bool isPrime(int num);
	int nextPrime(int num);
	int getProbeNumber();
	int getCurrentSize();
	int getArraySize();
	void printTable()
	{
		for (unsigned int i = 0; i < array.size(); i++)
		{
			cout<<array[i].number<<"	 "<<array[i].info<<endl;
		}
	}

	enum EntryType{Active,Empty,Deleted};
private:
	struct HashEntry
	{
		int number;
		EntryType info;
		HashEntry(int num, EntryType i)
		{
			number = num;
			info = i;
		}
		HashEntry()
		{

		}
	};
	vector<HashEntry> array;
	int currentSize;
	bool isActive(int currentPos);	
	int findPos(int & num); // added by extra for the insertion case
	int probeNumber; // added extra to count the probeNumber for each spesific operation (insert,remove,find)
	int findingPos(int & num); 
};

int HashTable::getArraySize() // method to acces the table size
{
	return array.size();
}

int HashTable::getCurrentSize() // method to acces the current size of the table
{
	return currentSize;
}

int HashTable::getProbeNumber() // method to acces the number of probes made for after each operation
{
	return probeNumber;
}

void HashTable::makeEmpty() // making the table empty
{
	currentSize = 0;
	for(unsigned int i = 0; i<array.size(); i++)
	{
		array[i].info = Empty; 
	}
}

bool HashTable::isInTable(int & num) // checks whether that value is in the table
{
	return isActive(findingPos(num));
}

HashTable::HashTable(int size) // constructor for the hash table
{
	array.resize(nextPrime(size));
	
	makeEmpty();
}

int HashTable::findPos(int & num) // finding the appropriate position for the insert operation since we can insert to the deleted places
{
	probeNumber = 0;
	unsigned int currentPos = hash(num);
	while(array[currentPos].info != Empty && array[currentPos].info != Deleted && array[currentPos].number != num)
	{
		probeNumber++;
		currentPos ++;
		if(currentPos >= array.size())
			currentPos -= array.size();
	}
	return currentPos;
}

int HashTable::findingPos(int & num) // finding the appropriate position for the find and remove operation
{
	probeNumber = 0;
	unsigned int currentPos = hash(num);
	while(array[currentPos].info != Empty && array[currentPos].number != num && probeNumber < array.size())
	{
		probeNumber++;
		currentPos ++;
		if(currentPos >= array.size())
			currentPos -= array.size();
	}
	return currentPos;
}

bool HashTable::couldInsert(int & num) // this function checks whether the number could be inserte to the table, if so it inserts and return true, otherwise it returns false
{
	int currentPos = findPos(num);
	if(isActive(currentPos))
	{
		return false;
	}
	if(array[currentPos].info == Deleted)
	{
		if(isInTable(num))
		{
			return false;
		}
		else
		{
			array[currentPos] = HashEntry(num,Active);
			currentSize++;
		}
	}
	else
	{
		array[currentPos] = HashEntry(num,Active);
		currentSize++;
	}
	return true;
}

bool HashTable::couldFind(int & num) // this function checks whether the number could be found to the table, if so it returns true, otherwise it returns false
{
	int currentPos = findingPos(num);
	if(isActive(currentPos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HashTable::couldRemove(int & num) // this function checks whether the number could be removed from the table, if so it removes and returns true, otherwise it returns false
{
	int currentPos = findingPos(num);
	if(isActive(currentPos))
	{
		array[currentPos].info = Deleted;
		currentSize--;
		return true;
	}
	else
	{
		return false;
	}
}

bool HashTable::isPrime(int num) // checks whether the number is prime or not
{
	if(num == 2 || num == 3)
		return true;
	if(num == 1 || num % 2 == 0)
		return false;
	for(int i = 3; i*i <= num; i+=2)
	{
		if(num % i == 0)
		{
			return false;
		}
	}
	return true;
}

int HashTable::nextPrime(int num) // finds the next closest prime number unless the number is prime
{
	if(num % 2 == 0)
	{
		num++;
	}
	for(; !isPrime(num); num+=2);
	return num;
}

int HashTable::hash(int & key) // hash function that takes the modulus of the key by the array size
{
	return key % array.size();
}

bool HashTable::isActive(int curPos) // checks whether there is an element in that position
{
	HashEntry temp =  array[curPos];
	return array[curPos].info == Active;
}


#endif