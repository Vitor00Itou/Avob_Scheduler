#include "Process.h"

Process::Process(int arrivalTime, int durationTime)
    : lastTimeRunning(0)

{
    this->arrivalTime = arrivalTime;
    this->durationTime = durationTime;
    this->remainingDurationTime = durationTime;
    this->wasAnswered = false;
    this->turnaroundTime = 0;
    this->responseTime = 0;
    this->waitingTime = 0;
}

Process::~Process()
{

}

int Process::getArrivalTime(){
    return this->arrivalTime;
}
int Process::getDurationTime(){
    return this->durationTime;
}

bool Process::getWasAnswered(){
    return this->wasAnswered;
}

int Process::getTurnaroundTime(){
    return this->turnaroundTime;
}
int Process::getResponseTime(){
    return this->responseTime;
}
int Process::getWaitingTime(){
    return this->waitingTime;
}

void Process::setWasAnswered(bool wasAnswered){
    this->wasAnswered = wasAnswered;
}

void Process::setTurnaroundTime(int turnaroundTime){
    this->turnaroundTime = turnaroundTime;
}
void Process::setResponseTime(int responseTime){
    this->responseTime = responseTime;
}
void Process::addWaitingTime(int waitingTime){
    this->waitingTime += waitingTime;
}

void Process::setLastTimeRunning(int lastTimeRunning){
    this->lastTimeRunning = lastTimeRunning;
}

int Process::getLastTimeRunning(){
    return this->lastTimeRunning;
}

int Process::getRemaingDurationTime(){
    return this->remainingDurationTime;
}

void Process::decreaseRemainingDurationTime(int decrementTime){
    this->remainingDurationTime -= decrementTime;
}
