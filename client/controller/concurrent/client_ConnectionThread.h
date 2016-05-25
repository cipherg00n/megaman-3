#ifndef CLIENT_CONNECTIONTHREAD_H_
#define CLIENT_CONNECTIONTHREAD_H_


#include <iostream>
#include "../../../common/common_Socket.h"
#include "../../concurrent/client_Looper.h"
#include "../../../common/common_Thread.h"
#include "../../concurrent/client_Event.h"

#include "event/client_ConnectionEvent.h"
#include "event/client_FlowEvent.h"
#include "client_ReceiverContract.h"

#include <unistd.h>

class ConnectionThread : public Thread {
private:
  ReceiverContract *listener;
  Looper *handlerLooper;
  Socket *socket;

  void dispatchEvent(Event *event) {
    if (listener) {
      if (handlerLooper)
        handlerLooper->put(event);
      else Looper::getMainLooper().put(event);

      listener->onDataReceived();
    }
  }

protected:
  virtual void run() {
    //TODO DO THE CONNECTION WITH THE SV
    usleep(1000 * 1000 * 3);

    //This should be the last line of the run, so that we receive this event, (immediatly a join is called on the connection) and we
    //dont loose main ui time
    dispatchEvent(new ConnectionEvent(RESULT_OK));
  }

public:
  ConnectionThread(Looper *handlerLooper = NULL) : handlerLooper(handlerLooper) { }
  ~ConnectionThread() {
  };

  void setListener(ReceiverContract *listener) {
    this->listener = listener;
  }

  void setSocket(Socket *socket) {
    this->socket = socket;
  }
};

#endif
