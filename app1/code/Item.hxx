#ifndef ITEM_H
#define ITEM_H

#include "Type.hxx"

struct Item
{
	Int num;
	
	friend ostream& operator<<(ostream& stream, const Item& item);
};

#endif