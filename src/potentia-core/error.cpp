#include "error.h"

potentia_error_code::potentia_error_code(const std::string &id) : m_id(id) {}

const char *potentia_error_code::what() const noexcept { return m_id.c_str(); }
