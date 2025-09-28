// Copyright 2025 Jason Montenegro-Navarro

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>

#include "Thread.hpp"

StatusCode Thread::startThread() {
  assert(!this->thread);
  try {
    // Creates thread in lambda function, and fetches the result of this->run().
    this->thread = std::make_unique<std::thread>([this]() -> void {
      this->running = true;
      const StatusCode result = this->run();
      if (result == StatusCode::THREAD_FAILURE) {
        // TODO(jmn): Change std::cerr for Log singleton class.
        std::cerr << "Thread finished with thread failure." << std::endl;
      }
      this->running = false;
    });
  } catch (const std::exception& e) {
    // TODO(jmn): Change std::cerr for Log singleton class.
    std::cerr << "Thread start failed: " << e.what() << std::endl;
    return StatusCode::THREAD_FAILURE;
  }
  return StatusCode::THREAD_SUCCESS;
}

StatusCode Thread::waitToFinish() {
  if (this->thread && this->thread->joinable()) {
    this->thread->join();
    this->thread.reset();
    this->running = false;
  }
  return StatusCode::THREAD_SUCCESS;
}
