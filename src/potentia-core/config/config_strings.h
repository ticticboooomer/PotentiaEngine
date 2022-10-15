#pragma once

#include "potentia-core/pch.h"
#include "config.h"

enum config_strings_key {
  game_name,
  game_window_title,
  __count
};

class config_strings : public config<config_strings_key, std::string, config_strings, config_strings_key::__count> {
};

