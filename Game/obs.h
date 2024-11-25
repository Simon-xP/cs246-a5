#ifndef _OBS_H_
#define _OBS_H_
#include <vector>
#include "constants.h"
#include <memory>

struct Producer;
struct Hand;
enum class Resource;

class Observer {
 public:
  virtual void notify() = 0;
  virtual ~Observer() = default;
};

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach( Observer* o );
  
  void detach(Observer* o );
  void notifyObservers();
  virtual Producer getStateT() const = 0;
  virtual Hand getStateC() const = 0;
  virtual int getStateD() const = 0;
  virtual ~Subject() = default;
};

#endif
