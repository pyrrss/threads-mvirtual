#include <iomanip>

#include "PageTable.hxx"

PageTable::PageTable(const int frameCount, Algorithm* algorithm) : frameCount(frameCount), algorithm(algorithm)
{
	SELF.missCount = 0;
	
	for(int i = 1; i <= frameCount; i++)
		SELF.freeFrames.insert(i);
}

PageTable::~PageTable()
{
	delete SELF.algorithm;
}

int PageTable::getMissCount()
{
	return SELF.missCount;
}

void PageTable::accessPage(const int npv)
{
	if(!SELF.table.contains(npv))
	{
		SELF.missCount++;
		
		int nmp = -1;
		
		if(SELF.table.size() >= SELF.frameCount)
		{
			int npvToRemove = SELF.algorithm -> chooseVirtPage(npv, table);
			
			nmp = SELF.table[npvToRemove];
			
			SELF.table.erase(npvToRemove);
		}
		
		else
		{
			nmp = *SELF.freeFrames.begin();
			
			SELF.freeFrames.erase(nmp);
		}
		
		if(nmp == -1)
			throw -1;
		
		SELF.table[npv] = nmp;
	}
	
	SELF.algorithm -> registerAccess(npv);
}

ostream& operator<<(ostream& stream, const PageTable& pageTable)
{
	stream << "NPV | NMP" << '\n';
	
	for(const auto& [npv, nmp] : pageTable.table)
	{
		stream << cpp::setw(3) << npv;
		stream << " | ";
		stream << cpp::setw(3) << nmp;
		stream << '\n';
	}
	
	return stream;
}