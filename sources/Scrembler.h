#pragma once

#include "defs.h"
#include <QString>
#include <QStringList>
#include <algorithm>
#include <vector>
class Scrembler {
public:
  size_t size{0};
  std::vector<uint8_t> items_{};

  std::vector<uint8_t> start_items_{};
  std::vector<bool> xor_items_{};

  size_t period_{};
  int word_len_{};
  size_t current_element_{};
  QString polinoms_str_{};
  QString start_pos_str_{};
  QString period_str_{};
  bool multi{};
  uint8_t GetItem();

  void Restart();

  Scrembler(ScremblerSettings&);

private:
  void Init();
  void Counter();
  uint8_t GetChar(QChar);
  void NextItem();
  void NextItem(uint8_t ch);
  uint8_t GetItem(uint8_t ch);
};
