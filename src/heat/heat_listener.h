// heat_listener.h
#ifndef HEAT_LISTENER_H
#define HEAT_LISTENER_H

class HeatListener {
public:
  virtual void onHeatEvent(bool isTurnedOn) = 0;
};

#endif  // HEAT_LISTENER_H