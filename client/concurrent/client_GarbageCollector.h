#ifndef CLIENT_CLIENT_GARBAGECOLLECTOR_H_
#define CLIENT_CLIENT_GARBAGECOLLECTOR_H_

#include <vector>
#include "client_Runnable.h"
#include "../../common/common_Thread.h"

#define MAX_GC_POOL_SIZE 5000 //Considering 1 Runnable costs us 10kb, this is 50mb

class GarbageCollector : public Thread {
private:
  std::vector<Runnable*> *objects;
  bool *running;
public:
  GarbageCollector(bool *running, std::vector<Runnable*> *objects) : Thread(),
                              objects(objects), running(running) {}
protected:
  virtual void run() {
    while (*running) {
  		if (objects->size() > MAX_GC_POOL_SIZE) {
        int size = objects->size();
        for (int i = 0 ; i < size ; ++i) {
    			delete (*objects->begin());
    			objects->erase(objects->begin());
        }
  		}
    }

    while (objects->size() > 0) {
        delete (*objects->begin());
        objects->erase(objects->begin());
    }

    delete objects;
    delete running;
  }
private:
  GarbageCollector(const GarbageCollector&);
  GarbageCollector& operator=(const GarbageCollector&);
};

#endif /* CLIENT_CLIENT_GARBAGECOLLECTOR_H_ */
