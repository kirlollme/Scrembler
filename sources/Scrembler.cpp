#include "Scrembler.h"

Scrembler::Scrembler(ScremblerSettings& setup)
{
	word_len_ = setup.word_size;
	polinoms_str_ = setup.polinoms; 
	start_pos_str_ = setup.start_pos; 
	period_str_ = setup.period;
	period_ = period_str_.toULongLong();
	multi = (bool)setup.type;
	Init();
}

uint8_t Scrembler::GetItem()
{
	uint8_t out = items_.back();
	NextItem();
	return out;



}

void Scrembler::Restart()
{
	current_element_ = 0;
	items_ = start_items_;

}

void Scrembler::NextItem()
{
	uint8_t item = items_.back();

	for (int i = 0 ; i + 1 < xor_items_.size() ; i++)
	{
		if (xor_items_[i])
			item = item ^ items_[i];
	}
	items_.pop_back();
	std::vector <uint8_t> new_items;
	new_items.push_back(item);
	for (int i = 0 ; i < items_.size() ; i++)
	{
		new_items.push_back(items_[i]);
	}
	items_ = new_items;
	Counter();
	return;
}

void Scrembler::Init()
{
	auto list_polinoms_str = polinoms_str_.split(",");
	std::vector <int> list_polinoms;

	for (auto item : list_polinoms_str )
	{
		list_polinoms.push_back(item.toInt());
	}

	auto s = std::max_element(list_polinoms.begin(), list_polinoms.end());
	size = *s;	  // длина сремблера
				  // создание списка в каких элементах будет xor
	xor_items_ = std::vector <bool> (size );

	for (int i = 0 ; i < list_polinoms.size(); i++)
	{
		if (size !=list_polinoms[i])
			xor_items_[list_polinoms[i] - 1] = 1;
	}

	for (int i = start_pos_str_.size() - 1  ; i >= 0 ; i--)
	{
		items_.push_back(GetChar(start_pos_str_[i]));
	}
	start_items_ = items_;
}

void Scrembler::Counter()
{
	current_element_+=word_len_;
	if (current_element_ >= period_)
	{
		current_element_ = 0;
		items_ = start_items_;
	}
}

uint8_t Scrembler::GetChar(QChar ch)
{
		if (ch.toLatin1() - '0' >= 0 && ch.toLatin1() - '0' < 10)
			return ch.toLatin1() - '0';

		return ch.toLatin1() - 'A' + 10;

}

uint8_t Scrembler::GetItem(uint8_t ch)
{
	NextItem(ch);
	bool out = items_[0];
	return out;
}
void Scrembler::NextItem(uint8_t ch)
{
	uint8_t item = items_.back();

	for (int i = 0; i < xor_items_.size() - 1; i++)
	{
		if (xor_items_[i])
			item = item ^ items_[i];
	}
	items_.pop_back();
	std::vector <uint8_t> new_items;
	item = item ^ ch;
	new_items.push_back(item);
	for (int i = 0; i < items_.size(); i++)
	{
		new_items.push_back(items_[i]);
	}
	items_ = new_items;
	Counter();
	return;
}