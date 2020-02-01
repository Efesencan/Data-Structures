#include <iostream>
#include "linkedlist.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;
LinkedList::LinkedList () // initializing the head pointer to NULL in a linkedlist constructor
{
	head = NULL;
}


LinkedList::~LinkedList () // deleting the each node of the linked list
{
	node * ptr = head;
	node * jump = ptr;
    while (ptr != NULL) 
	{
		bottom * temp = ptr->bottom;
		while(temp != NULL)
		{
			bottom *additional = temp->next;
			delete temp;
			temp = additional;
		}
		jump = ptr->next;
		delete ptr;
		ptr = jump;
	}
}

void LinkedList::addDocNumber(int n, node * & ptr) // adding the values of the document number to the linked list in a sorted manner
{
	if(ptr->bottom == NULL || n < ptr->bottom->number) 
	{
		if(ptr->bottom == NULL)
		{
			ptr->bottom = new bottom(n,NULL); // creating the first node that contains the document number
		}
		else
		{
			bottom * p = new bottom(n,ptr->bottom); // adding the bottom node to the previous of the first bottom node
			ptr->bottom = p;
		}
	}
	else
	{
		bottom *prev;
		bottom *my_ptr = ptr->bottom;
		while(my_ptr != NULL && my_ptr->number < n) 
		{
			prev = my_ptr;
			my_ptr = my_ptr->next;
		}
		prev->next = new bottom(n,my_ptr); // we are creating a new bottom node and inserting it to the right place
	}
}

bool LinkedList::isInList(string n, int num) // checking if the string and the integer pair in the file is already in the linked list (if so return true / otherwise return false)
{
	node * ptr = head;
	bottom * temp;
	while(ptr)
	{
		if(ptr->name == n)
		{
			temp = ptr->bottom;
			while(temp)
			{
				if(temp->number == num)
				{
					return true;
				}
				else
				{
					temp = temp->next;
				}
			}
		}
		ptr = ptr->next;
	}
	return false;
}

string lowerCase(string n) // making the each character of the words lowercase
{
	string temp = n;
	for(int i = 0; i < n.length(); i++)
	{
		if(n[i] >= 'A' && n[i] <= 'Z')
			temp[i] = temp[i] - ('Z' - 'z');
	}
	return temp;
}
void LinkedList::addInOrder(string n,int num) // adding the string value to the linked list in an alphabetical order
{
	if(!isInList(n,num)) // first checking if the string and integer pair is already in the list 
	{
		if(head == NULL || lowerCase(n) <= lowerCase(head->name)) // we check the conditions that the head value shuold be changed
		{
			if(head != NULL && head->name == n)
			{
				node *ptr = head;
				addDocNumber(num,ptr);// after we create each string node we call the addDocNumber functions which adds the corresponding document number
			}
			else
			{
				node * ptr = new node(n,head);
				head = ptr;
				addDocNumber(num,ptr); // second func
			}	
		}
		else
		{
			bool isTrue = true;
			node *prev;
			node *ptr = head;
			node * tempor = head;
			while(tempor) // check whether that string value is already in the list
			{
				if(tempor->name == n)
				{
					isTrue = false;
					break;
				}
				tempor = tempor->next;
			}
			if(isTrue)
			{
				while(ptr != NULL && lowerCase(ptr->name) < lowerCase(n)) // we are traversing in the linked list until we find the correcting inserting place
				{
					prev = ptr;
					ptr = ptr->next;
				}

				if(ptr == NULL && prev->name == n)
				{
					addDocNumber(num,prev);
				}
				else
				{
					prev->next = new node(n,ptr);
					addDocNumber(num,prev->next);// second func
				}
			}
			else // if the string value is already in the list we call the addDocNumber function
			{
				addDocNumber(num,tempor);
			}
		}
	}
	
}


void LinkedList::searchingWords(int num, vector<string> my_vec) // we are searching the words in our linked list
{
	vector<int>result;
	vector<int>common;
	node *ptr = head;
	string word_name;
	bottom * temp;
	for(int i = 0; i<my_vec.size(); i++) 
	{
		word_name = my_vec[i]; 
		while(ptr != NULL) // we look for the corresponding document numbers for the specific string value
		{
			if(ptr->name == word_name) // if that word is in the linked list we store the values of the document numbers
			{
				temp = ptr->bottom;
				while(temp != NULL) 
				{
					result.push_back(temp->number);
					temp = temp->next;
				}
				break;
			}
			else
			{
				ptr = ptr->next;
			}
		}
	}
	int count;
	bool isTrue = true;
	for(int j = 0; j<result.size(); j++) // we are looking if the number of occurences of the document number is equal to the number(total number of words to be searched) parameter in the function, if so add it to the result vector
	{
		count = 0;
		for(int i = 0; i<result.size(); i++)
		{
			if(result[j] == result[i])
			{
				count++;
			}
		}
		if(count == num)  // if so
		{
			for(int a = 0; a < common.size(); a++) 
			{
				if(common[a] == result[j])
				{
					isTrue = false;
				}
			}
			if(isTrue)
				common.push_back(result[j]);
		}
	}
	if(common.size() == 0)
	{
		cout<<0<<endl;
	}
	else
	{
		cout<<common.size()<<" ";
		for(int i = 0; i<common.size(); i++)
		{
			cout<<common[i]<<" ";
		}
	}
	
}



void LinkedList::printList () // printing the each nodes of the linked list
{
	node * ptr = head;
	bottom * temp;
    while (ptr != NULL) 
	{
		cout<<ptr->name<<" ";
		temp = ptr->bottom;
		while(temp != NULL)
		{
			cout<<temp->number<<" ";
			temp = temp->next;
		}
		cout << endl;
		ptr = ptr->next;
	}
}

void LinkedList::lenList() // printing the length of the linked list
{
	int count = 0;
	node *ptr = head;
	while(ptr)
	{
		count++;
		ptr = ptr->next;
	}
	cout<<count<<endl;
}


