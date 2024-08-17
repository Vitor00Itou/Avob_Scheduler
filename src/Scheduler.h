#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm> 
#include <iomanip>
#include "Scheduler.h"
#include "Process.h"

#define QUANTUM 2

#pragma once

class Scheduler
{
public:
    Scheduler();
    ~Scheduler();
    bool addProcess(Process newProcess);
    void printProcesses();
    bool sortProcessByArrivialTime();
    bool runFCSF();
    bool runSJF();
    bool runRR();
    bool cleanAllData();
    bool calculateAllAvarages();
    void printAllAvarages();


private:

    struct Metrics {
        double averageTurnaroundTime;
        double averageResponseTime;
        double averageWaitingTime;
    };

    std::vector<Process> originalProcesses;
    std::vector<Process> servedFCFSProcesses;
    std::vector<Process> servedSJFProcesses;
    std::vector<Process> servedRRProcesses;

    Metrics fcfsMetrics;
    Metrics sjfMetrics;
    Metrics rrMetrics;

    void sortQueueByDurationTime(std::queue<Process>& queue);
};

#endif