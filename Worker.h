#pragma once
#ifndef WORKER_H
#define	wORKER_H

#include "abstract_request.h"
#include <condition_variable>
#include <mutex>
using namespace std;

class Worker {
	std::condition_variable cv;
	std::mutex mtx;
	std::unique_lock<std::mutex> ulock;
	AbstractRequest* request;
	bool running;
	bool ready;
public:
	Worker() {
		running = true; ready = false; 
		ulock =	std::unique_lock<std::mutex>(mtx);
	}
	void run();
	void stop() { running = false;
	//notify if thread is waiting to be signaled
	//if not done, this will make program to be blocked infinitly
	cv.notify_one(); 
	}
	void setRequest(AbstractRequest* request) {
		this->request = request;
		ready = true;
	}
	void notify() { cv.notify_one();}
};

#endif // !WORKER_H__

