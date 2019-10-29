#include "Encoder.h"
void Encode(QByteArray & data, std::vector<Scrembler*>& scremblers, std::vector<int> const & order, size_t& period)
{
	int index = 0;
	size_t period_index = 0;
	for (uint i = 0 ; i < period; i++)
	{
		uint8_t scrembler_bytes = 0;
		bool bit = false;
		for (int j = 0 ; j < 8 ; j++)
		{  
			scrembler_bytes = scrembler_bytes;
			bit = scremblers[order[index]]->GetItem();
			uint8_t bit_char(bit);
			bit_char = bit_char << j;
			scrembler_bytes |= bit_char;
			
			index++;
			if (index == scremblers.size())
				index = 0;

			period_index++;
			if (period == period_index)
			{
				period_index = 0;
				for (auto scr:scremblers)
					scr->Restart();
			}

		}
		for (uint pos = i ; pos < data.size(); pos +=period)
		{
			data[pos] = data[pos] ^ scrembler_bytes;
		}
	}

}

