#pragma once

#include "potentia-core/base/global_singleton.h"
#include <potentia-core/pch.h>
#include "potentia-hal/interface/device.h"
#include "potentia-hal/interface/surface.h"
#include "potentia-hal/interface/window.h"

template<class TFactory>
class hal_storage : public global_singleton<TFactory> {
  public:
    std::shared_ptr<window> get_window() const { return m_window; };
    std::shared_ptr<surface> get_surface() const { return m_surface; };
    std::shared_ptr<device> get_device() const { return m_device; };
  protected:
    std::shared_ptr<window> m_window;
    std::shared_ptr<surface> m_surface;
    std::shared_ptr<device> m_device;
};
