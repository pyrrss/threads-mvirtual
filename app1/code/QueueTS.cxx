#include <chrono>
#include <iostream>
#include <sstream>

#include "QueueTS.hxx"

using ulock = cpp::unique_lock<cpp::mutex>;

QueueTS::QueueTS(int size, int maxWait, Logger* logger) : Queue(size), maxWait(maxWait), logger(logger)
{
}

Item QueueTS::pop()
{
	ulock lock(SELF.mutex);
	
	while(SELF.size() == 0)
	{
		SELF.hasItems.wait_for(lock, SELF.maxWait * cpp::chrono::seconds(1));
		
		if(SELF.size() == 0)
			throw -1;
	}
	
	int capacity1 = SELF.capacity();
	Item item = Queue::pop();
	int capacity2 = SELF.capacity();
	
	if(SELF.logger != NULLPTR)
	{
		cpp::stringstream message;
		
		message << "POPPED: " << item;
		
		if(capacity1 != capacity2)
		{
			message << " ";
			message << "[" << capacity1 << " -> " << capacity2 << "]";
		}
		
		SELF.logger -> print(message.str());
	}
	
	cpp::cerr << SELF << '\n';
	
	lock.unlock();
	
	return item;
}

void QueueTS::push(Item item)
{
	ulock lock(SELF.mutex);
	
	int capacity1 = SELF.capacity();
	Queue::push(item);
	int capacity2 = SELF.capacity();
	
	if(SELF.logger != NULLPTR)
	{
		cpp::stringstream message;
		
		message << "PUSHED: " << item;
		
		if(capacity1 != capacity2)
		{
			message << " ";
			message << "[" << capacity1 << " -> " << capacity2 << "]";
		}
		
		SELF.logger -> print(message.str());
	}
	
	cpp::cerr << SELF << '\n';
	
	lock.unlock();
	
	SELF.hasItems.notify_one();
}