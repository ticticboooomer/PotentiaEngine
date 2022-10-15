#pragma once

#include <memory>

template <class T> class global_singleton {
public:
  static std::shared_ptr<T> instance() {
    static std::shared_ptr<T> m_instance{new T};
    return m_instance;
  }

  ;
};
