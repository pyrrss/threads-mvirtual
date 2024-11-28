#ifndef CLK_H
#define CLK_H

#include <vector>

#include "Algorithm.hxx"
#include "Type.hxx"

class CLK : public Algorithm
{
	public:
		CLK(const int size) : accessed(size, false)
		{
		}
		
		int chooseVirtPage(const int npv, const cpp::unordered_map<int, int>& table) override
		{
			int newNpv = -1;
			
			while(newNpv == -1)
			{
				if(table.contains(SELF.position))
				{
					if(SELF.accessed[SELF.position])
						SELF.accessed[SELF.position] = false;
					
					else
					{
						newNpv = SELF.position;
						SELF.position = npv;
						
						break;
					}
				}
				
				SELF.position += 1;
				SELF.position %= accessed.size();
			}
			
			return newNpv;
		}

		void registerAccess(const int npv) override
		{
			SELF.accessed[npv] = true;
		}

	private:
		int position = 0;
		
		cpp::vector<bool> accessed;
};

#endif
