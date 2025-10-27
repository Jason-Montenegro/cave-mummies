// Copyright 2025 Jason Montenegro-Navarro

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

namespace cave_mummies::core {

/**
 * @brief Abstract application interface. Sets window application API.
 */
class Application {
 public:
  /**
   * @brief Destructor
   */
  virtual ~Application() = default;

  /**
   * @brief Starts running application
   * @return EXIT_SUCCESS on successful run, otherwise EXIT_FAILURE
   */
  virtual int run() = 0;

 protected:
  /**
   * @brief Initializes application
   */
  virtual void init() = 0;

  /**
   * @brief Updates state of application
   * @return true if an update was possible, otherwise false (close program)
   */
  virtual bool update() = 0;

  /**
   * @brief Draws application to screen
   */
  virtual void draw() = 0;

  /**
   * @brief Cleans initialized objects of application
   */
  virtual void cleanup() = 0;
};

}  // namespace cavemummies::core

#endif  // APPLICATION_HPP
