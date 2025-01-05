#pragma once

class Device {
  public:
    virtual void setup() = 0;
    virtual void action() = 0;
};
