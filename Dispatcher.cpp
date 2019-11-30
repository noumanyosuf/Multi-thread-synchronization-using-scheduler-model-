#include "Dispatcher.h"
#include <iostream>

using namespace std;

queue<AbstractRequest*> Dispatcher:: requests;
queue<Worker*> Dispatcher::workers;
mutex Dispatcher::requestsMutex;
mutex Dispatcher::workersMutex;
vector<Worker*> Dispatcher::allWorkers;
vector<thread*> Dispatcher::threads;


bool Dispatcher::init(int workers) {
	thread* t = 0;
	Worker* w = 0;
	for (int i = 0; i < workers; ++i) {
		w = new Worker();
		allWorkers.push_back(w);
		t = new thread(&Worker::run, w);
		threads.push_back(t);
	}
	return true;
}

bool Dispatcher::stop() {
	for (int i = 0; i < allWorkers.size(); ++i) {
		allWorkers[i]->stop();

	}
	cout << "Stopped workers.\n";
	for (int j = 0; j < threads.size(); ++j) {
		threads[j]->join();
		cout << "Joined threads.\n";
	}

	return true;
}

void Dispatcher::addRequest(AbstractRequest* request) 
{ 
	workersMutex.lock();  
	if (!workers.empty()) 
	{ 
		Worker* worker = workers.front();
		worker->setRequest(request);
		worker->notify();
		workers.pop();
		workersMutex.unlock();
	} 
	else 
	{ 
		workersMutex.unlock();
		requestsMutex.lock();
		requests.push(request);
		requestsMutex.unlock();
	}
}

bool Dispatcher::addWorker(Worker* worker) {
	bool wait = true;
	requestsMutex.lock(); 
	if (!requests.empty()) 
	{ 
		AbstractRequest* request = requests.front();
		worker->setRequest(request);
		requests.pop();
		wait = false;
		requestsMutex.unlock();
	}
	else { 
		requestsMutex.unlock();
		workersMutex.lock();
		workers.push(worker);
		workersMutex.unlock();
	}            
	return wait;
}