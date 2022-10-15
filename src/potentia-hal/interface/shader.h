#pragma once

#include <potentia-core/pch.h>
class shader {
public:
	enum type { fragment, vertex, mesh };
  virtual void init_from_file(const std::string& path) = 0;
  virtual void destroy() = 0;
  virtual type get_type() = 0;
  virtual void set_type(type type) = 0;
};
