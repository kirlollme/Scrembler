#pragma once
#include <vector>
#include "Scrembler.h"

void Encode( QByteArray& data, std::vector <Scrembler*>& scremblers, std::vector <int> const&  order, size_t &period);
