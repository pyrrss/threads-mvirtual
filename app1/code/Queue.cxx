#include <cassert>

#include "Queue.hxx"

Queue::Queue(int size) : first(0), final(0), limit(size)
{
	SELF.items = (Item*) malloc(sizeof(Item) * SELF.limit);
}

Queue::~Queue()
{
	delete SELF.items;
}

int Queue::size()
{
	if(SELF.first <= SELF.final)
		return SELF.final - SELF.first;
	
	else
		return SELF.limit - (SELF.first - SELF.final);
}

int Queue::capacity()
{
	return SELF.limit;
}

Item Queue::pop()
{
	assert(SELF.size() >= 1);
	
	Item item = SELF.items[SELF.first];
	
	SELF.first += 1;
	SELF.first %= SELF.limit;
	
	if(SELF.size() == (SELF.limit / 4))
		SELF.resize(SELF.limit / 2);
	
	return item;
}

void Queue::push(Item item)
{
	if(SELF.size() == (SELF.limit - 1))
		SELF.resize(SELF.limit * 2);
	
	SELF.items[SELF.final] = item;
	
	SELF.final += 1;
	SELF.final %= SELF.limit;
}

void Queue::resize(int size)
{
	assert(size >= SELF.size());
	
	Item* aux = SELF.items;
	
	SELF.items = (Item*) malloc(sizeof(Item) * size);
	
	for(int i = 0; i < SELF.size(); i++)
		SELF.items[i] = aux[(i + SELF.first) % SELF.limit];
	
	SELF.final = SELF.size();
	SELF.first = 0;
	
	SELF.limit = size;
	
	delete aux;
}

ostream& operator<<(ostream& stream, const Queue& queue)
{
	for(int i = 0; i < queue.limit; i++)
	{
		bool inRange = (i >= queue.first) && (i < queue.final);
		
		bool aux1 = (queue.first < queue.final) && inRange;
		bool aux2 = (queue.first > queue.final) && !inRange;
		
		if(aux1 || aux2)
			stream << queue.items[i];
		
		else
			stream << "x";
		
		if(i < (queue.limit - 1))
			stream << " ";
	}
	
	return stream;
}