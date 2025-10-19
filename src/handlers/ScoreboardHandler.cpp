// Copyright 2025 Jason Montenegro-Navarro

#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>

#include "ScoreboardHandler.hpp"
namespace cave_mummies::handlers {

ScoreboardHandler::ScoreboardHandler() {
  this->scoreboardFile.open(ScoreboardHandler::scoreboardFilename
    , std::ios::ate);
}

ScoreboardHandler::~ScoreboardHandler() {
  if (this->scoreboardFile.is_open()) {
    this->scoreboardFile.close();
  }
}

ScoreboardHandler& ScoreboardHandler::getInstance() {
  static ScoreboardHandler handler;
  return handler;
}

bool ScoreboardHandler::postScore(std::string_view label, int64_t score) {
  if (!this->scoreboardFile.is_open()) {
    return false;
  } else {
    const std::string actualLabel =
      label.empty() ? "Unknown" : std::string(label);

    this->scoreboardFile.seekp(0, std::ios::end);
    this->scoreboardFile << actualLabel << "\t" << score << "\n";
  }
  return true;
}

std::string ScoreboardHandler::getScore(std::string_view label) {
  if (!this->scoreboardFile.is_open()) {
    return "";
  } else {
    this->scoreboardFile.seekg(0, std::ios::beg);
    std::string preview{""};
    while (std::getline(this->scoreboardFile, preview)) {
      if (preview.find(label) != std::string::npos) {
        break;
      }
    }
    return preview;
  }
}

bool ScoreboardHandler::clearScoreboard() {
  if (this->scoreboardFile.is_open()) {
    this->scoreboardFile.close();
  }

  this->scoreboardFile.open(ScoreboardHandler::scoreboardFilename,
    std::ios::out | std::ios::trunc);
  this->scoreboardFile.close();
  this->scoreboardFile.open(ScoreboardHandler::scoreboardFilename,
    std::ios::in | std::ios::out | std::ios::ate);
  return this->scoreboardFile.is_open();
}

std::vector<std::string> ScoreboardHandler::getAllScoreboard() {
  if (!this->scoreboardFile.is_open()) {
    return std::vector<std::string>();
  } else {
    std::vector<std::string> scoreboard;
    std::string preview("");
    while (std::getline(this->scoreboardFile, preview)) {
      if (!preview.empty()) {
        scoreboard.push_back(preview);
      }
    }
    return scoreboard;
  }
}

}  // namespace cave_mummies::handlers
