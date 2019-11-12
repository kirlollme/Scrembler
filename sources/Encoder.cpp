#include "Encoder.h"
void Encode(QByteArray & data, std::vector<Scrembler*>& scremblers, std::vector<int> const & order, size_t& period)
{
	uint64_t index = 0;
	size_t period_index = 0;

	for (uint64_t i = 0 ; i < period; i++)
	{
		uint64_t scrembler_bytes = 0;
		uint64_t bit = 0;
		scrembler_bytes = 0;
		if (scremblers[0]->word_len != 3) {
			auto word_size = scremblers[0]->word_len;
			for (int j = 0; j < CHAR_BIT / word_size; j++)
			{
				bit = scremblers[order[index]]->GetItem();
				uint32_t bit_char(bit);
				bit_char = bit_char << j* word_size;
				scrembler_bytes |= bit_char;

				index++;
				if (index == scremblers.size())
					index = 0;

				period_index+=scremblers[order[index]]->word_len;
				if (period == period_index)
				{
					period_index = 0;
					for (auto scr : scremblers)
						scr->Restart();
				}

			}

			for (uint pos = i ; pos < data.size(); pos +=period)
			{
				data[pos] = data[pos] ^ scrembler_bytes;
			}
		}
		else {
			// для длины равной 3 
			for (int j = 0; j < 8; j++)
			{
				bit = scremblers[order[index]]->GetItem();
				uint32_t bit_char(bit);
				bit_char = bit_char << j * 3;
				scrembler_bytes |= bit_char;

				index++;
				if (index == scremblers.size())
					index = 0;

				
				period_index+=scremblers[order[index]]->word_len;
				if (period == period_index)
				{
					period_index = 0;
					for (auto scr : scremblers)
						scr->Restart();
				}

			}

			for (uint pos = i ; pos < data.size(); pos +=period)
			{	
				int current = 0;
				if (current == 0) 
				{
					data[pos] = data[pos] ^ (scrembler_bytes >> 16);
					current++;
				}
				else if(current = 1)
				{
					current++;
					data[pos] = data[pos] ^ (scrembler_bytes >> 8 & (255));
				
				}
				else 
				{
					data[pos] = data[pos] ^ (scrembler_bytes & (255));
					current = 0;
				}
			}
		}
	}

}
