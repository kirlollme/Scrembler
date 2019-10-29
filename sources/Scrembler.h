#pragma once

#include <vector>
#include <QString>
#include <QStringList>
#include <algorithm>

class Scrembler
{
public:
	size_t size											{ 0 };
	std::vector <uint8_t> items							{   };
	
	std::vector <uint8_t>	start_items					{   };
	std::vector <bool>		xor_items					{   };

	size_t					period						{	};
	int						word_len					{	};
	size_t					current_element				{	};
	QString					polinoms_str				{	};
	QString					start_pos_str				{	};
	QString					period_str					{	};

	bool GetItem();

	void Restart();

	Scrembler(QString polinoms, QString start_pos, QString period,int word_size);

private:
	void Counter();
	uint8_t GetChar(QChar);
	void NextItem();
};
enum size_scemblers : int 
{ 
	bin = 2,
	x4 = 4,
	octal = 8,
	hex = 16
};