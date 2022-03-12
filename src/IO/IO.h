#pragma once
#include "common/pch.h"

class IO
{
  public:
    IO() = default;

    virtual void initialize();
    virtual void run() = 0;
    virtual bool isInitialized() = 0;
    enum InitStatus
    {
        INIT,
        READY
    };

  protected:
    /** Must be set before initialize is called */
    bool createThread = true;
    std::mutex mutex;

  private:
    std::thread thisThread;
};
