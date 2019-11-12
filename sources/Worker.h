#pragma once
#include "Encoder.h"
#include "Scrembler.h"
#include "defs.h"
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QString>
#include <vector>
struct Worker {
  QString file_name_;
  QString base_name_;
  QString dir_path_;
  QString suffix_;
  QString path_to_file_;

  bool new_file_ = true;
  size_t period{};
  size_t processed_bytes_{0};
  size_t const buffer_size_{128 * 1024 * 1024};
  std::vector<Scrembler *> scremblers_{};
  std::vector<int> positions_in_code_{};

  Encoder encoder_ =  Encoder();

  Worker::Worker(Settings &);
  void StartEncode();
  void CreateConfig();
  void EncodeFile(QFile &file);
  void Save(QByteArray &buffer);
  void GetFileConfig(QFile &file);
};
