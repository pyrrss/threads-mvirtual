#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <unordered_map>

#include "Type.hxx"

class Algorithm
{
	public:
		virtual int chooseVirtPage(const int npv, const cpp::unordered_map<int, int>& table) = 0;
		virtual void registerAccess(const int npv) = 0;
};

#endif



