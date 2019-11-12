#pragma once
#include <QString>
#include <vector>
#include "Scrembler.h"


struct Settings
{
	 size_t scremblers_count	{ 0 };

	 QString path_to_file		{	};

	 std::vector <Scrembler*> scremblers{  };

	 std::vector <int> positions_in_code {};

	 size_t period; 

	 int word_size;
	
};