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
		QueueTS(Int size, Int maxWait, Logger* logger);
		
		Item pop();
		None push(Item item);
	
	private:
		Int maxWait;
		
		Logger* logger;
		
		cpp::mutex mutex;
		cpp::condition_variable hasItems;
};

#endif