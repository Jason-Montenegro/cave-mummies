// Copyright 2025 Jason Montenegro-Navarro

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

/**
 * @brief Abstract application interface. Sets window application API.
 */
class Application {
 public:
  /**
   * @brief Deleted copy constructor.
   * @param other Other app
   */
  Application(const Application &other) = delete;

  /**
   * @brief Deleted move constructor.
   * @param other Other app
   */
  Application(const Application &&other) = delete;

  /**
   * @brief Deleted copy-assignment operator.
   * @param other Other app
   */
  const Application& operator=(const Application &other) = delete;

  /**
   * @brief Deleted move-assignment operator.
   * @param other Other app
   */
  const Application& operator=(const Application &&other) = delete;

  /**
   * @brief Constructor
   */
  Application() = default;

  /**
   * @brief Destructor
   */
  virtual ~Application() = default;

  /**
   * @brief Starts running application.
   * @return EXIT_SUCCESS on successful run, EXIT_FAILURE otherwise
   */
  virtual int run() = 0;

 protected:
  /**
   * @brief Initializes application configuration.
   */
  virtual void init() = 0;

  /**
   * @brief Updates state of application.
   * @return true if an update was possible, false otherwise (program close)
   */
  virtual bool update() = 0;

  /**
   * @brief Draws application to screen.
   */
  virtual void draw() = 0;

  /**
   * @brief Cleans application configuration.
   */
  virtual void cleanup() = 0;
};

#endif  // APPLICATION_HPP
