#include "Scrembler.h"

Scrembler::Scrembler(QString polinoms, QString start_pos, QString prd,int word_size)
{
	// перевод строки с полиномами в инт список
	auto list_polinoms_str = polinoms.split(",");
	std::vector <int> list_polinoms;
	polinoms_str = polinoms; 
	start_pos_str = start_pos; 
	period_str = prd;

	for (auto item : list_polinoms_str )
	{
		list_polinoms.push_back(item.toInt());
	}
	
	auto s = std::max_element(list_polinoms.begin(), list_polinoms.end());
	size = *s;	  // длина сремблера
	// создание списка в каких элементах будет xor
	xor_items = std::vector <bool> (size );

	for (int i = 0 ; i < list_polinoms.size(); i++)
	{
		if (size !=list_polinoms[i])
			xor_items[list_polinoms[i] - 1] = 1;
	}

	for (int i = start_pos.size() - 1  ; i >= 0 ; i--)
	{
		items.push_back(GetChar(start_pos[i]));
	}
	start_items = items;
	period = prd.toULongLong();
}

bool Scrembler::GetItem()
{
	bool out = items[items.size()-1];
	NextItem();
	return out;



}

void Scrembler::Restart()
{
	current_element = 0;
	items = start_items;

}

void Scrembler::NextItem()
{
	bool item = items.back();

	for (int i = 0 ; i < xor_items.size() - 1 ; i++)
	{
		if (xor_items[i])
			item = item ^ items[i];
	}
	items.pop_back();
	std::vector <uint8_t> new_items;
	new_items.push_back(item);
	for (int i = 0 ; i < items.size() ; i++)
	{
		new_items.push_back(items[i]);
	}
	items = new_items;
	Counter();
	return;
}

void Scrembler::Counter()
{
	current_element++;
	if (current_element == period)
	{
		current_element = 0;
		items = start_items;
	}
}

uint8_t Scrembler::GetChar(QChar ch)
{
		QString a = "21";
		auto b = a[0];
		if (ch.toLatin1() - '0' >= 0 && ch.toLatin1() - '0' < 10)
			return ch.toLatin1() - '0';

		return ch.toLatin1() - 'A' + 10;

}

