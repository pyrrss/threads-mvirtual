#ifndef QUEUE_H
#define QUEUE_H

#include "Item.hxx"
#include "Type.hxx"

class Queue
{
	public:
		Queue(Int size);
		~Queue();
		
		Int size();
		Int capacity();
		
		Item pop();
		None push(Item item);
		
		friend ostream& operator<<(ostream& stream, const Queue& queue);
	
	private:
		Int first;
		Int final;
		
		Int limit;
		
		Item* items;
		
		None resize(Int size);
};

#endif