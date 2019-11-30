#include "Request.h"

void Request::process() 
{    outFnc("Starting processing request " + std::to_string(value) + "...");    
} 
void Request::finish() 
{    outFnc("Finished request " + std::to_string(value)); 
}