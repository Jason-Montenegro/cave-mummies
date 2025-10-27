// Copyright 2021,2023 Jeisson Hidalgo-Cespedes. ECCI-UCR. CC BY 4.0
// Adapted in 2025 by Jason Montenegro-Navarro

#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

namespace cave_mummies::utils {

/**
 * @brief Thread-safe log manager
 * @author Jeisson Hidalgo-Céspedes
 * @note This class is adapted from a code base made by professor Jeisson
 * Hildago Céspedes, who shared it while teaching the course CI0117
 * "Programación paralela y concurrente".
 */
class Log final {
 private:
  /**
   * @brief Copy constructor disabled.
   * @param other Other log
   */
  Log(const Log& other) = delete;
  
  /**
   * @brief Move constructor disabled.
   * @param other Other log
   */
  Log(Log&& other) = delete;
  
  /**
   * @brief Copy assignment operator disabled.
   * @param other Other log
   */
  Log& operator=(const Log& other) = delete;
  
  /**
   * @brief Move assignment constructor disabled.
   * @param other Other log
   */
  Log& operator=(Log&& other) = delete;

 private:
  std::mutex mutex;  ///< Operations lock
  std::ostream output;  ///< Stream that holds all sent messaged
  std::string filename;  ///< Log file name
  std::ofstream file;  ///< The log file if using named files
  static const char* const MESSAGE_TYPE_LABEL[]; ///< Labels for message types
  static constexpr const char *const defaultLogFilename{"cave_mummies.log"};

 public:
   /**
   * @brief Message types for documenting log messages.
   */
  enum MessageType {
    DEBUGGING,
    INFO,
    WARNING,
    ERROR
  };

  /**
   * @brief Get the singleton Log instance.
   * @return Singleton Log instante
   */
  static Log& getInstance();

  /**
   * @brief Opens the log file for use.
   * @param logFilename Log filename
   * @throw std::runtime_error if passed file name does not match with any file
   */
  void start(const std::string_view logFilename = Log::defaultLogFilename);

  /**
   * @brief Closes the log file.
   */
  void stop();

  /**
   * @brief Appends a record to the log file.
   * @throw std::runtime_error if operation failed
   * @see append()
   */
  void write(Log::MessageType type, const std::string_view category
    , const std::string_view message);

  /**
   * @brief Appends a record to the log file.
   * 
   * @param type @see MessageType
   * @param category A label to recognize where the message comes from
   * @param message Message to log
   * @remark Do not abuse escape characters or the resulting log file may appear
   * malformed.
   * @throw std::runtime_error if operation failed
   */
  static inline void append(Log::MessageType type
    , const std::string_view category, const std::string_view message) {
    return Log::getInstance().write(type, category, message);
  }

 private:
  /**
   * @brief Singleton class. Constructor is hidden.
   */
  Log();

  /**
   * @brief Singleton class. Destructor is hidden.
   */
  ~Log() = default;
};

}  // namespace cave_mummies::utils

#endif  // LOG_HPP
