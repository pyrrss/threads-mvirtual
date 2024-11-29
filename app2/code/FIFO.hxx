#ifndef FIFO_H
#define FIFO_H

#include <cassert>
#include <queue>
#include <set>

#include "Algorithm.hxx"
#include "Type.hxx"

class FIFO : public Algorithm
{
	public:
		int chooseVirtPage(const int npv, const cpp::unordered_map<int, int>& table) override
		{
			assert(!SELF.queue.empty());
			
			int newNpv = SELF.queue.front();
			
			SELF.queue.pop();
			
			return newNpv;
		}

		void registerAccess(const int npv) override
		{
			if(!SELF.npvsInQueue.contains(npv))
			{
				npvsInQueue.insert(npv);
				SELF.queue.push(npv);
			}
		}

	private:
		cpp::set<int> npvsInQueue;
		cpp::queue<int> queue;


#endif



