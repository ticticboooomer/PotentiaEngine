#pragma once

class runnable {
  virtual void update() = 0;
  virtual void render() = 0;
  virtual void init() = 0;
  virtual void on_enabled() = 0;
  virtual void on_disabled() = 0;
};
