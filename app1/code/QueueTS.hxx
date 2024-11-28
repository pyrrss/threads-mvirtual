#ifndef MONITOR_H
#define MONITOR_H

#include <mutex>
#include <condition_variable>

#include "Item.hxx"
#include "Logger.hxx"
#include "Queue.hxx"
#include "Type.hxx"

class QueueTS : public Queue
{
	public:
		QueueTS(int size, int maxWait, Logger* logger);
		
		Item pop();
		void push(Item item);
	
	private:
		int maxWait;
		
		Logger* logger;
		
		cpp::mutex mutex;
		cpp::condition_variable hasItems;
};

#endif