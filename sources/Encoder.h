#pragma once
#include "Scrembler.h"
#include <vector>

struct Encoder {

  size_t index_ = 0;
  size_t period_index_ = 0;
  size_t scrembler_bytes_ = 0;
  size_t bit_ = 0;

  size_t current_element_ = 0;
							
  std::vector<int> order_;
  size_t period_;
  void Encode(QByteArray &data, std::vector<Scrembler *> &scremblers,
              std::vector<int> const &order, size_t &period);
  void DefaultEncode(QByteArray &data, std::vector<Scrembler *> &scremblers);
  void ThreeBitEncode(QByteArray &data,
                               std::vector<Scrembler *> &scremblers);
};
