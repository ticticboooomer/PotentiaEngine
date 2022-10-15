#pragma once

#include "potentia-core/base/global_singleton.h"
#include "potentia-core/error.h"
#include <array>
#include <potentia-core/pch.h>
#include <type_traits>

template<typename TKey, typename TValue, class TClass, size_t count>
class config : public global_singleton<TClass> { 
  static_assert(std::is_enum<TKey>::value, "Config key type must be enum");
  public:
    config();
    TValue get_value(TKey k);
    void set_value(TKey k, TValue v);
    void lock_values();
    void unlock_values();
  protected:
    size_t index(TKey k);
    void throw_on_locked();
    std::array<TValue, count> m_values;
    bool m_locked;
};


template<typename TKey, typename TValue, class TClass, size_t count>
size_t config<TKey, TValue, TClass, count>::index(TKey k) {
  return static_cast<size_t>(k);
}


template<typename TKey, typename TValue, class TClass, size_t count>
TValue config<TKey, TValue, TClass, count>::get_value(TKey k) {
  throw_on_locked();
  return m_values[index(k)];
}


template<typename TKey, typename TValue, class TClass, size_t count>
void config<TKey, TValue, TClass, count>::set_value(TKey k, TValue v) {
  throw_on_locked();
  m_values[index(k)] = v;
}


template<typename TKey, typename TValue, class TClass, size_t count>
void config<TKey, TValue, TClass, count>::lock_values() {
  m_locked = true;
}


template<typename TKey, typename TValue, class TClass, size_t count>
void config<TKey, TValue, TClass, count>::unlock_values() {
  m_locked = false;
}

template<typename TKey, typename TValue, class TClass, size_t count>
void config<TKey, TValue, TClass, count>::throw_on_locked() {
  if (m_locked) {
    THROW_P000001;
  }
}


template<typename TKey, typename TValue, class TClass, size_t count>
config<TKey, TValue, TClass, count>::config() : m_values(), m_locked(false) {

}

