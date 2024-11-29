#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <fstream>
#include <set>
#include <unordered_map>

#include "Algorithm.hxx"
#include "Type.hxx"

class PageTable
{
	public:
		PageTable(const int frameCount, Algorithm* algorithm);
		~PageTable();
		
		int getMissCount();
		
		void accessPage(const int npv);
	
	private:
		int missCount;
		int frameCount;
		
		Algorithm* algorithm;
		
		cpp::set<int> freeFrames;
		cpp::unordered_map<int, int> table;
		
		friend ostream& operator<<(ostream& stream, const PageTable& pageTable);
};

#endif


