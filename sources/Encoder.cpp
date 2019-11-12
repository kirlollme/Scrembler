#include "Encoder.h"

void Encoder::Encode(QByteArray & data, std::vector<Scrembler*>& scremblers, std::vector<int> const & order, size_t& period)
{
	order_ = order;
	period_ = period;
	for (size_t i = 0 ; i < period; i++)
	{
		current_element_ = i;
		bit_ = 0;
		scrembler_bytes_ = 0;
		if (scremblers[0]->word_len_ != 3)
			DefaultEncode(data,scremblers);
		else 
			ThreeBitEncode(data,scremblers);
	}
}


void Encoder::DefaultEncode(QByteArray & data, std::vector<Scrembler*>& scremblers)
{
	auto word_size = scremblers[0]->word_len_;
	for (int j = 0; j < CHAR_BIT / word_size; j++)
	{
		bit_ = scremblers[order_[index_]]->GetItem();
		uint32_t bit_char(bit_);
		bit_char = bit_char << j* word_size;
		scrembler_bytes_ |= bit_char;

		index_++;
		if (index_ == scremblers.size())
			index_ = 0;

		period_index_+=scremblers[order_[index_]]->word_len_;
		if (period_ == period_index_)
		{
			period_index_ = 0;
			for (auto scr : scremblers)
				scr->Restart();
		}

	}

	for (uint pos = current_element_ ; pos < data.size(); pos +=period_)
	{
		data[pos] = data[pos] ^ scrembler_bytes_;
	}
}

void Encoder::ThreeBitEncode(QByteArray & data, std::vector<Scrembler*>& scremblers)
{
	for (int j = 0; j < 8; j++)
	{
		bit_ = scremblers[order_[index_]]->GetItem();
		uint32_t bit_char(bit_);
		bit_char = bit_char << j * 3;
		scrembler_bytes_ |= bit_char;

		index_++;
		if (index_ == scremblers.size())
			index_ = 0;


		period_index_ += scremblers[order_[index_]]->word_len_;
		if (period_ == period_index_)
		{
			period_index_ = 0;
			for (auto scr : scremblers)
				scr->Restart();
		}

	}

	for (uint pos = current_element_; pos < data.size(); pos += period_)
	{
		int current = 0;
		if (current == 0)
		{
			data[pos] = data[pos] ^ (scrembler_bytes_ >> 16);
			current++;
		}
		else if (current = 1)
		{
			current++;
			data[pos] = data[pos] ^ (scrembler_bytes_ >> 8 & (255));

		}
		else
		{
			data[pos] = data[pos] ^ (scrembler_bytes_ & (255));
			current = 0;
		}
	}
}