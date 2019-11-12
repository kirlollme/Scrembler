#pragma once
#include "Scrembler.h"
#include <QString>
#include <memory>
#include <vector>

struct ScremblerSettings {
	int word_size{};
	QString polinoms{};
	int type{};
	QString start_pos{};
	QString period{};
};

struct Settings {
  int word_size{};
  size_t scremblers_count{0};
  size_t period{};
  QString path_to_file{};
  std::vector<int> positions_in_code{};
  std::vector<std::shared_ptr<ScremblerSettings>> scremblers{};
};
