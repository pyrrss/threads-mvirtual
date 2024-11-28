#ifndef LRU_H
#define LRU_H

#include <algorithm>
#include <cassert>
#include <list>

#include "Algorithm.hxx"
#include "Type.hxx"

class LRU : public Algorithm
{
	public:
		int chooseVirtPage(const int npv, const cpp::unordered_map<int, int>& table) override
		{
			assert(!SELF.list.empty());
			
			int newNpv = SELF.list.back();
			
			SELF.list.pop_back();
			
			return newNpv;
		}
		
		void registerAccess(const int npv) override
		{
			auto position = cpp::find(SELF.list.begin(), SELF.list.end(), npv);
			
			if(position != SELF.list.end())
				SELF.list.erase(position);
			
			SELF.list.push_front(npv);
		}
	
	private:
		cpp::list<int> list;
};

#endif