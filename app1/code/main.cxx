#include <iostream>
#include <random>
#include <thread>

#include "Logger.hxx"
#include "QueueTS.hxx"

None producer(const Int& ID, QueueTS& queue)
{
	cpp::mt19937 rng(ID);
	cpp::uniform_int_distribution<> distribution(1, 5);
	
	Int amount = distribution(rng);
	
	for(Int i = 0; i < amount; i++)
		queue.push(Item(ID));
}

None consumer(const Int& ID, QueueTS& queue)
{
	while(true)
	{
		try
		{
			queue.pop();
		}
		
		catch(...)
		{
			cpp::cerr << "Consumer " << ID << " exiting\n";
			
			break;
		}
	}
}

int main(int argc, char* args[])
{
	using thread = cpp::thread;
	
	Int size = -1;
	Int time = -1;
	Int countP = -1;
	Int countC = -1;
	{
		try
		{
			for(int i = 1; i < (argc - 1); i++)
			{
				string arg = args[i];
				
				if(arg == "-s")
					size = cpp::stoi(args[++i]);
				
				if(arg == "-t")
					time = cpp::stoi(args[++i]);
				
				if(arg == "-p")
					countP = cpp::stoi(args[++i]);
				
				if(arg == "-c")
					countC = cpp::stoi(args[++i]);
			}
			
			if((size < 0) || (time < 0) || (countP < 0) || (countC < 0))
				throw -1;
		}
		
		catch(...)
		{
			cpp::cerr << "Wrong arguments" << '\n';
			
			return 0;
		}
	}
	
	Logger logger("log.txt");
	QueueTS queue(size, time, &logger);
	
	thread producers[countP];
	thread consumers[countC];
	
	for(Int i = 0; i < countP; i++)
		producers[i] = thread(producer, i, cpp::ref(queue));
	
	for(Int i = 0; i < countC; i++)
		consumers[i] = thread(consumer, i, cpp::ref(queue));
	
	for(thread& producer : producers)
		producer.join();
	
	for(thread& consumer : consumers)
		consumer.join();
}