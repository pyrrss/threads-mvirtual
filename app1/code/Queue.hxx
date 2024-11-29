#ifndef QUEUE_H
#define QUEUE_H

#include "Item.hxx"
#include "Type.hxx"

class Queue
{
	public:
		Queue(int size);
		~Queue();
		
		int size();
		int capacity();
		
		Item pop();
		void push(Item item);
		
		friend ostream& operator<<(ostream& stream, const Queue& queue);
	
	private:
		int first;
		int final;
		
		int limit;
		
		Item* items;
		
		void resize(int size);
};

#endif

