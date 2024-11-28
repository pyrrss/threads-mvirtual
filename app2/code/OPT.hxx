#ifndef OPT_H
#define OPT_H

#include <vector>

#include "Algorithm.hxx"
#include "Type.hxx"

class OPT : public Algorithm
{
	public:
		OPT(const cpp::vector<int>& references) : references(references)
		{
			SELF.position = 0;
		}
		
		int chooseVirtPage(const int npv, const cpp::unordered_map<int, int>& table) override
		{
			int access = 0;
			int newNpv = -1;
			
			for(const auto& [u, v] : table)
			{
				int firstAccess = SELF.references.size();
				
				for(int i = position; i < SELF.references.size(); i++)
				{
					if(references[i] == u)
					{
						firstAccess = i;
						
						break;
					}
				}
				
				if(firstAccess > access)
				{
					access = firstAccess;
					newNpv = u;
				}
			}
			
			return newNpv;
		}

		void registerAccess(const int npv) override
		{
			SELF.position++;
		}
	
	private:
		int position;
		
		cpp::vector<int> references;
};

#endif