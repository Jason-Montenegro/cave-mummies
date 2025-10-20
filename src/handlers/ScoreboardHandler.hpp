// Copyright 2025 Jason Montenegro-Navarro

#ifndef SCOREBOARD_HANDLER_HPP
#define SCOREBOARD_HANDLER_HPP

#include <fstream>
#include <string>
#include <vector>

namespace cave_mummies::handlers {

class ScoreboardHandler {
 private:
  /**
   * @brief Score entry for file storage
   */
  struct ScoreEntry {
      std::string label;
      int64_t score;
  };

  std::fstream scoreboardFile;
  static constexpr const char* const scoreboardFilename{"scoreboard.log"};

  /**
   * @brief Constructtor
   */
  ScoreboardHandler();

  /**
   * @brief Destructor
   */
  ~ScoreboardHandler();

 public:
  /**
   * @brief Get the Instance object
   * 
   * @return ScoreboardHandler singleton
   */
  static ScoreboardHandler& getInstance();

  /**
   * @brief Copy constructor disabled
   */
  ScoreboardHandler(const ScoreboardHandler&) = delete;

  /**
   * @brief Assignment operator disabled
   * @return this ScoreboardHandler
   */
  ScoreboardHandler& operator=(const ScoreboardHandler&) = delete;

  /**
   * @brief Posts a score to the scoreboard file. If name is empty, the score
   * label will be "Unknown".
   * 
   * @param label 
   * @param score 
   * @return true on post success, false otherwise
   */
  bool postScore(std::string_view label, int64_t score);

  /**
   * @brief Get the Score from the scoreboard file in the following format:
   * [label] [score]
   * @param label Score label
   * @return Formatted score string if the score exists, if not an empty string
   * is returned.
   */
  std::string getScore(std::string_view label);

  /**
   * @brief Clears all scoreboard logs.
   * @return true on success, false on failure
   */
  bool clearScoreboard();

  /**
   * @brief Gets the whole scoreboard contents.
   * @return std::vector<std::string> containing all posted scores
   */
  std::vector<std::string> getAllScoreboard();
};

}

#endif  // SCOREBOARD_HANDLER_HPP
