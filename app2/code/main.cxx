#include <iostream>

#include <set>
#include <vector>

#include "CLK.hxx"
#include "FIFO.hxx"
#include "LRU.hxx"
#include "OPT.hxx"
#include "PageTable.hxx"
#include "Type.hxx"

int main(int argc, char* args[])
{
	int frames = -1;
	
	cpp::string name;
	cpp::fstream file;
	{
		try
		{
			for(int i = 1; i < (argc - 1); i++)
			{
				string arg = args[i];
				
				if(arg == "-m")
					frames = cpp::stoi(args[++i]);
				
				if(arg == "-a")
					name = args[++i];
				
				if(arg == "-f")
					file = cpp::fstream(args[++i]);
			}
			
			if((frames < 0) || (!file.is_open()))
				throw -1;
			
			if((name != "CLK") && (name != "FIFO") && (name != "LRU") && (name != "OPT"))
				throw -1;
		}
		
		catch(...)
		{
			cpp::cerr << "Wrong arguments" << '\n';
			
			return 0;
		}
	}
	
	cpp::set<int> uniqueNPVs;
	cpp::vector<int> references;
	{
		while(!file.eof())
		{
			int npv; file >> npv;
			
			uniqueNPVs.insert(npv);
			references.push_back(npv);
		}
	}
	
	Algorithm* algorithm = NULLPTR;
	{
		if(name == "CLK")
			algorithm = new CLK(uniqueNPVs.size());
		
		if(name == "FIFO")
			algorithm = new FIFO();
		
		if(name == "LRU")
			algorithm = new LRU();
		
		if(name == "OPT")
			algorithm = new OPT(references);
	}
	
	PageTable pageTable(frames, algorithm);
	
	for(int npv : references)
	{
		pageTable.accessPage(npv);
		
		cpp::cerr << npv << ":\n";
		cpp::cerr << pageTable;
		cpp::cerr << "\n";
	}
	
	cpp::cout << pageTable << '\n';
	cpp::cout << pageTable.getMissCount() << '\n';
}