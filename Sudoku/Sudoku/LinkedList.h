#pragma once

struct node {
	int num;
	node *next;
};


class LinkedList
{
private:
	node * head;
public:
	LinkedList();
	void add(int num);
	int get(int num);
	int size();
	void deleteNum(int num);
	void printList();

	~LinkedList();
};

