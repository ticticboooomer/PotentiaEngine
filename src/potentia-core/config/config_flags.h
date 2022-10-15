#pragma once

#include "potentia-core/base/global_singleton.h"
#include "potentia-core/config/config.h"
#include <array>
#include <potentia-core/pch.h>

#define NUM_KEYS 3

enum config_flags_key {
  __count
};

class config_flags : config<config_flags_key, bool, config_flags, config_flags_key::__count> {
  
};
