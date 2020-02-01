#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <vector>
#include <sstream>
#include <string>

using namespace std;

template <class type1>//int
struct bottom // forming the bottom nodes which contains the document number in an ascending order with a corresponding string value
{
	type1 number;
	bottom<type1> *next; 

	bottom::bottom ()
	{}

	bottom<type1>::bottom (type1 & num, bottom<type1> * link)
		: number(num), next(link)
	{}
};
// type 1 int // type 2 string
template <class type1,class type2>
struct node {  // forming the nodes which contains the string values in an alphabetical order
	type2 name;
	node<type2,type1> *next;
	bottom<type1> *bottom;
	node::node ()
	{}

	node<type2,type1>::node (type2 & s, node<type2,type1> * link)
	{
		name = s;
		next = link;
		bottom = NULL;
	}
};

// data_type string, second_type int
template <class data_type,class second_type>
class LinkedList 
{
	private:
		node<data_type,second_type> * head;
		
	public:
		 LinkedList ();  // constructor
		 //LinkedList (const LinkedList & );  //copy constructor
		 ~LinkedList (); // deleting the elements that are dynamically allocated
		 void printList(); // printing the elements of the linked list
		 void addInOrder(data_type n,second_type num); // adding the string values to a linked list in an alphabetical  manner
		 void addDocNumber(second_type number,node<data_type,second_type> * & ptr); // adding the documents numbers to the respecting string value in an ascending order
		 void lenList(); // printing the length of the linked list
		 bool isInList(data_type n, second_type num); // checking if the word and the document number pair is already in the linked list
		 void searchingWords(second_type num,vector<data_type> vec); // searching the common words that occur in document in the list entered by the user

		 
};


template <class data_type,class second_type>
LinkedList<data_type,second_type>::LinkedList () // initializing the head pointer to NULL in a linkedlist constructor
{
	head = NULL;
}

template <class data_type,class second_type>
LinkedList<data_type,second_type>::~LinkedList () // deleting the each node of the linked list
{
	node<data_type,second_type> * ptr = head;
	node<data_type,second_type> * jump = ptr;
    while (ptr != NULL) 
	{
		bottom<second_type> * temp = ptr->bottom;
		while(temp != NULL)
		{
			bottom<second_type> *additional = temp->next;
			delete temp;
			temp = additional;
		}
		jump = ptr->next;
		delete ptr;
		ptr = jump;
	}
}

template <class data_type,class second_type>
void LinkedList<data_type,second_type>::addDocNumber(second_type n, node<data_type,second_type> * & ptr) // adding the values of the document number to the linked list in a sorted manner
{
	if(ptr->bottom == NULL || n < ptr->bottom->number) 
	{
		if(ptr->bottom == NULL)
		{
			ptr->bottom = new bottom(n,NULL); // creating the first node that contains the document number
		}
		else
		{
			bottom<second_type> * p = new bottom(n,ptr->bottom); // adding the bottom node to the previous of the first bottom node
			ptr->bottom = p;
		}
	}
	else
	{
		bottom<second_type> *prev;
		bottom<second_type> *my_ptr = ptr->bottom;
		while(my_ptr != NULL && my_ptr->number < n) 
		{
			prev = my_ptr;
			my_ptr = my_ptr->next;
		}
		prev->next = new bottom(n,my_ptr); // we are creating a new bottom node and inserting it to the right place
	}
}

template <class data_type,class second_type>
bool LinkedList<data_type,second_type>::isInList(data_type n, second_type num) // checking if the string and the integer pair in the file is already in the linked list (if so return true / otherwise return false)
{
	node<data_type,second_type> * ptr = head;
	bottom<second_type> * temp;
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

//template <class data_type,class second_type>
//string lowerCase(data_type n) // making the each character of the words lowercase
//{
//	data_type temp = n;
//	for(int i = 0; i < n.length(); i++)
//	{
//		if(n[i] >= 'A' && n[i] <= 'Z')
//			temp[i] = temp[i] - ('Z' - 'z');
//	}
//	return temp;
//}

template <class data_type,class second_type>
void LinkedList<data_type,second_type>::addInOrder(data_type n,second_type num) // adding the string value to the linked list in an alphabetical order
{
	if(!isInList(n,num)) // first checking if the string and integer pair is already in the list 
	{
		if(head == NULL || lowerCase(n) <= head->name) // we check the conditions that the head value shuold be changed
		{
			if(head != NULL && head->name == n)
			{
				node<data_type,second_type> *ptr = head;
				addDocNumber(num,ptr);// after we create each string node we call the addDocNumber functions which adds the corresponding document number
			}
			else
			{
				node<data_type,second_type> * ptr = new node(n,head);
				head = ptr;
				addDocNumber(num,ptr); // second func
			}	
		}
		else
		{
			bool isTrue = true;
			node<data_type,second_type> *prev;
			node<data_type,second_type> *ptr = head;
			node<data_type,second_type> * tempor = head;
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
				while(ptr != NULL && ptr->name < n) // we are traversing in the linked list until we find the correcting inserting place
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


template <class data_type,class second_type>
void LinkedList<data_type,second_type>::searchingWords(second_type num, vector<data_type> my_vec) // we are searching the words in our linked list
{
	vector<second_type>result;
	vector<second_type>common;
	node<data_type,second_type> *ptr = head;
	data_type word_name;
	bottom<second_type> * temp;
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


template <class data_type,class second_type>
void LinkedList<data_type,second_type>::printList () // printing the each nodes of the linked list
{
	node<data_type,second_type> * ptr = head;
	bottom<second_type> * temp;
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

template <class data_type,class second_type>
void LinkedList<data_type,second_type>::lenList() // printing the length of the linked list
{
	int count = 0;
	node<data_type,second_type> *ptr = head;
	while(ptr)
	{
		count++;
		ptr = ptr->next;
	}
	cout<<count<<endl;
}


#endif





