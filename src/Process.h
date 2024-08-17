#ifndef Process_H
#define Process_H

#pragma once

class Process
{
public:
    Process(int arrivalTime, int durationTime);
    ~Process();

    int getArrivalTime();
    int getDurationTime();

    bool getWasAnswered();

    int getLastTimeRunning();
    int getRemaingDurationTime();

    int getTurnaroundTime();
    int getResponseTime();
    int getWaitingTime();

    void setWasAnswered(bool wasAnswered);

    void setLastTimeRunning(int lastTimeRunning);


    void setTurnaroundTime(int turnaroundTime);
    void setResponseTime(int responseTime);


    void addWaitingTime(int waitingTime);
    void decreaseRemainingDurationTime(int decrementTime);
    

private:
    int arrivalTime;
    int durationTime;

    bool wasAnswered;

    int lastTimeRunning;
    int remainingDurationTime;

    int turnaroundTime;
    int responseTime;
    int waitingTime;
};

#endif