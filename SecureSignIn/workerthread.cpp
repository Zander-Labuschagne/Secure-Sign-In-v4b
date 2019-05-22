#include "workerthread.hpp"

WorkerThread::WorkerThread(QWidget *parent) : QThread()
{

}

void WorkerThread::run()
{
       QString result;
       /* ... here is the expensive or blocking operation ... */
       sleep(8);
       emit resultReady();
}
