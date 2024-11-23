#include "Item.hxx"

ostream& operator<<(ostream& stream, const Item& item)
{
	stream << item.num;
	
	return stream;
}