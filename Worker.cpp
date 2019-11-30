
#include "Worker.h"
#include "Dispatcher.h"
#include<iostream>
#include <chrono>

void Worker::run() {
	while (running) {
		if (ready) {
			ready = false;
			request->process();
			request->finish(); 
		} 
		//check if thread is still running, before adding to the dispatcher worker thread pool
		if (running && Dispatcher::addWorker(this))
		{            
			// Use the ready loop to deal with spurious wake-ups. 
			while (!ready && running) 
			{
				//Better to wait for condition to wake thread up rather than pooling for some seconds,
				//as pooling on some vaiable takes CPU cycle and can reduce CPU performance
				cv.wait(ulock, [&]() {return ready || !running; });
			}       
		}    
	}
}