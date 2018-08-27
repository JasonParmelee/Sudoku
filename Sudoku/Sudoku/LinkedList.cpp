#include "stdafx.h"
#include "LinkedList.h"
#include <iostream>
#include <stdexcept>

LinkedList::LinkedList()
{
	
}

//Used to add a number to the Linked List
void LinkedList::add(int num)
{
	node *temp = new node, *helper;

	temp->num = num;
	temp->next = NULL;

	if (head == NULL)
	{
		head = temp;
	}
	else
	{
		helper = head;
		while (helper->next != NULL)
		{
			helper = helper->next;
		}

		helper->next = temp;
	}
}

//Used to get a number from the Linked List, based on position in the list (0 based index)
int LinkedList::get(int num)
{
	int i = 0;
	int numAt = NULL;
	node *n = head;

	while (n != NULL)
	{
		if (i == num)
		{
			return n->num;
		}

		n = n->next;
		i++;
	}

	exit(EXIT_FAILURE);

	return numAt;
}

//Used to get the size of the Linked List, or number of nodes
int LinkedList::size()
{
	int i = 0;

	node *n = head;

	while (n != NULL)
	{
		i++;
		n = n->next;
	}

	return i;
}

//Deletes and element of the list by location in the list (0 based index)
void LinkedList::deleteNum(int num)
{
	int i = 0;
	node * n = head;
	node * prev = new node;

	if (n == NULL)
	{
		return;
	}

	while (n != NULL)
	{
		if (i == num)
		{
			if (n == head)
			{
				head = n->next;
				return;
			}
			else
			{
				prev->next = n->next;
				return;
			}
		}
		else
		{
			if (n->next != NULL)
			{
				prev = n;
				n = n->next;
			}
		}

		i++;
	}

	exit(EXIT_FAILURE);

	return;
}

//Used to print the contents of the list
void LinkedList::printList()
{
	node *n = head;

	if (n == NULL)
	{
		std::cout << "List empty" << std::endl;
	}
	else
	{
		while (n != NULL)
		{
			std::cout << n->num << " ";
			n = n->next;
		}
	}
}


LinkedList::~LinkedList()
{
}
