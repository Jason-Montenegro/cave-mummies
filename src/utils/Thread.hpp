// Copyright 2025 Jason Montenegro-Navarro

#ifndef THREAD_HPP
#define THREAD_HPP

#include <thread>
#include <memory>
#include <atomic>

/**
 * @brief Status codes for thread operations.
 */
enum class StatusCode {
  THREAD_SUCCESS,
  THREAD_FAILURE
};

/**
 * @brief Wrapper class for handling execution threads.
 * 
 * Inherit from this class and implement the run() method to define
 * the thread's execution routine.
 */
class Thread {
 protected:
  std::unique_ptr<std::thread> thread;  ///< Standard c++ thread wrapper
  std::atomic<bool> running{false};  ///< Thread running status flag

 public:
  /**
   * @brief Construct a new Thread object.
   */
  Thread() = default;

  /**
   * @brief Destroys the Thread object and ensures Thread is joined.
   */
  virtual ~Thread() {
    if (running) {
      this->waitToFinish();
    }
  };

  /**
   * @brief Creates an execution thread, and executes run().
   * @return StatusCode THREAD_SUCCESS on success, THREAD_FAILURE on error.
   */
  StatusCode startThread();

  /**
   * @brief Joins this thread.
   * @return StatusCode THREAD_SUCCESS on success.
   */
  StatusCode waitToFinish();

  /**
   * @brief Check if the thread is currently running.
   * @return true if running, false otherwise.
   */
  inline bool isRunning() const { return this->running; }

 protected:
  /**
   * @brief This is the routine that this thread should execute.
   * @return StatusCode THREAD_SUCCESS on completion, THREAD_FAILURE on error.
   */
  virtual StatusCode run() = 0;
};

#endif  // THREAD_HPP
