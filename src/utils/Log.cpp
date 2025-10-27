// Copyright 2021,2023 Jeisson Hidalgo-Cespedes. ECCI-UCR. CC BY 4.0
// Adapted in 2025 by Jason Montenegro-Navarro

#include <exception>
#include <iostream>
#include <string>

#include "Log.hpp"

namespace cave_mummies::utils {

/// @brief Labels for message types.
const char* const Log::MESSAGE_TYPE_LABEL[] = {
  "Debug",
  "Info",
  "Warning",
  "Error",
};

Log& Log::getInstance() {
  static Log log;
  return log;
}

Log::Log()
: output{std::cout.rdbuf()} {}

void Log::start(const std::string_view logFilename) {
  const std::lock_guard<std::mutex> lock(this->mutex);
  // If filename is empty, use stdout
  if (logFilename.empty()) {
    // Adapted from https://stackoverflow.com/a/366969
    this->output.rdbuf(std::cout.rdbuf());
    this->filename = "(stdout)";
  } else {
    this->file.open(logFilename.data(), std::ios::app);
    if (!this->file) {
      throw std::runtime_error("could not open log file: " +
        std::string(logFilename));
    }
    this->filename = logFilename;
    this->output.rdbuf(this->file.rdbuf());
  }
}

void Log::stop() {
  const std::lock_guard<std::mutex> lock(this->mutex);
  if (this->file.is_open()) {
    this->file.close();
  }
}

void Log::write(Log::MessageType type, const std::string_view category
  , const std::string_view message) {
  const std::lock_guard<std::mutex> lock(this->mutex);
  this->output << MESSAGE_TYPE_LABEL[type] << '\t' << category << '\t'
               << message << std::endl;

  if (!this->output) {
    throw std::runtime_error("could not write log file: " + this->filename);
  }
}

}  // namespace cave_mummies::utils
