#pragma once 
#ifndef REQUEST_H 
#define REQUEST_H
#include "abstract_request.h"
#include <string>
using namespace std;
typedef void (*logFunction)(string text);
class Request : public AbstractRequest 
{ 
int value;    
logFunction outFnc;    
public:    
	int getValue() { return value; }
	void setValue(int value) { this->value = value; }    
	void setOutput(logFunction fnc) { outFnc = fnc; }    
	void process();    
	void finish(); 
}; 
#endif