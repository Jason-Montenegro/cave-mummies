// Copyright 2025 Jason Montenegro-Navarro

#ifndef CAVE_MUMMIES_CORE_APPLICATION_HPP
#define CAVE_MUMMIES_CORE_APPLICATION_HPP

namespace cave_mummies::core {

/**
 * @brief Abstract application interface.
 */
class Application {
  // Public API
 public:
  /**
   * @brief Destroy the Application object.
   */
  virtual ~Application() = default;

  /**
   * @brief Starts application.
   * @return EXIT_SUCCESS on successful run, otherwise EXIT_FAILURE.
   */
  virtual int run() = 0;

  // Protected members
 protected:
  /**
   * @brief Initializes application.
   */
  virtual void init() = 0;

  /**
   * @brief Updates state of application.
   * @return true if an update was possible, otherwise false (close
   * application).
   */
  virtual bool update() = 0;

  /**
   * @brief Draws application to screen.
   */
  virtual void draw() = 0;

  /**
   * @brief Cleans initialized objects of application.
   */
  virtual void cleanup() = 0;
};

}  // namespace cave_mummies::core

#endif  // CAVE_MUMMIES_CORE_APPLICATION_HPP
