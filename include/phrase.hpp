#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"

class Phrase {
protected:
  std::vector<std::vector<unsigned int>> m_params;
  nlohmann::json m_tree;
  unsigned int m_speed_factor = 8;

public:
  Phrase();

  void populate();
  void set_speed(unsigned int);
  std::vector<std::vector<unsigned int>> generate_phrase();
};