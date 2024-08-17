#include "Scheduler.h"

Scheduler::Scheduler()
    : fcfsMetrics{0, 0, 0}, 
      sjfMetrics{0, 0, 0}, 
      rrMetrics{0, 0, 0} 
{
    // Se houver outras inicializações necessárias, você pode adicioná-las aqui.
}



Scheduler::~Scheduler()
{

}

bool Scheduler::addProcess(Process newProcess){
    this->originalProcesses.push_back(newProcess);

    return true;
}

bool Scheduler::cleanAllData(){
    this->originalProcesses.clear();
    this->servedRRProcesses.clear();
    this->servedSJFProcesses.clear();
    this->servedFCFSProcesses.clear();
    
    return true;
}

void Scheduler::printProcesses(){
    for (Process process : originalProcesses) {
        std::cout << "Tempo de chegada: " << process.getArrivalTime() << ", Duração: " << process.getDurationTime() << std::endl;
    }
}

bool Scheduler::sortProcessByArrivialTime(){
    std::stable_sort(originalProcesses.begin(), originalProcesses.end(), [](Process a,  Process b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    return true;
}

bool Scheduler::runFCSF(){
    // Cria um vetor de processos para armazenar os processos que serão atendidos pela FCSF
    std::queue<Process> unservedFCFSProcesses;

    // Copia todos os processos originais
    for (size_t i = 0; i < this->originalProcesses.size(); i++)
    {
        unservedFCFSProcesses.push(originalProcesses[i]);
    }

    // Cria uma fila para escalonar os processos
    std::queue<Process> queue_fcfs;

    int currentTime = 0;

    // Enquanto ainda houver processos para serem servidos ou entrarem na fila, executa
    while (!queue_fcfs.empty() || !unservedFCFSProcesses.empty())
    {
        // Adiciona todos os processos com tempo de chegada menor ou igual ao tempo atual na fila
        while (unservedFCFSProcesses.front().getArrivalTime() <= currentTime && !unservedFCFSProcesses.empty())
        {   
            queue_fcfs.push(unservedFCFSProcesses.front());
            unservedFCFSProcesses.pop();
        }

        // Se a fila estiver vazia, atualiza o tempo atual e passa para a próxima iteração
        if (queue_fcfs.empty())
        {
            currentTime++;
            continue;
        }

        // Servido o processo atual
        queue_fcfs.front().setWasAnswered(true);
        queue_fcfs.front().setResponseTime(currentTime -  queue_fcfs.front().getArrivalTime());
        queue_fcfs.front().addWaitingTime(currentTime -  queue_fcfs.front().getArrivalTime());

        // Atualizando o cuurentTime com o tempo gasto servindo o processo
        currentTime += queue_fcfs.front().getDurationTime();

        // Calculando o tempo de retorno
        queue_fcfs.front().setTurnaroundTime(currentTime - queue_fcfs.front().getArrivalTime());

        // Guardando o processo e retirando da fila
        this->servedFCFSProcesses.push_back(queue_fcfs.front());
        queue_fcfs.pop();
        
    }
    
    return 0;
}

bool Scheduler::runSJF(){
        // Cria um vetor de processos para armazenar os processos que serão atendidos pela FCSF
    std::queue<Process> unservedSJFProcesses;

    // Copia todos os processos originais
    for (size_t i = 0; i < this->originalProcesses.size(); i++)
    {
        unservedSJFProcesses.push(originalProcesses[i]);
    }

    // Cria uma fila para escalonar os processos
    std::queue<Process> queue_sjf;

    int currentTime = 0;

    // Enquanto ainda houver processos para serem servidos ou entrarem na fila, executa
    while (!queue_sjf.empty() || !unservedSJFProcesses.empty())
    {
        // Adiciona todos os processos com tempo de chegada menor ou igual ao tempo atual na fila
        while (unservedSJFProcesses.front().getArrivalTime() <= currentTime && !unservedSJFProcesses.empty())
        {   
            queue_sjf.push(unservedSJFProcesses.front());
            unservedSJFProcesses.pop();
        }

        // Após adicionar os processos na fila, ordena (de forma estável), por tempo de duração
        sortQueueByDurationTime(queue_sjf);

        // Se a fila estiver vazia, atualiza o tempo atual e passa para a próxima iteração
        if (queue_sjf.empty())
        {
            currentTime++;
            continue;
        }

        // Servido o processo atual
        queue_sjf.front().setWasAnswered(true);
        queue_sjf.front().setResponseTime(currentTime -  queue_sjf.front().getArrivalTime());
        queue_sjf.front().addWaitingTime(currentTime -  queue_sjf.front().getArrivalTime());

        // Atualizando o cuurentTime com o tempo gasto servindo o processo
        currentTime += queue_sjf.front().getDurationTime();

        // Calculando o tempo de retorno
        queue_sjf.front().setTurnaroundTime(currentTime - queue_sjf.front().getArrivalTime());

        // Guardando o processo e retirando da fila
        this->servedSJFProcesses.push_back(queue_sjf.front());
        queue_sjf.pop();
        
    }
    
    return 0;
}

bool Scheduler::runRR(){
    // Cria um vetor de processos para armazenar os processos que serão atendidos pela FCSF
    std::queue<Process> unservedRRProcesses;

    // Copia todos os processos originais
    for (size_t i = 0; i < this->originalProcesses.size(); i++)
    {
        unservedRRProcesses.push(originalProcesses[i]);
    }

    // Cria uma fila para escalonar os processos
    std::queue<Process> queue_rr;

    int currentTime = 0;

    // Enquanto ainda houver processos para serem servidos ou entrarem na fila, executa
    while (!queue_rr.empty() || !unservedRRProcesses.empty())
    {
        // Adiciona todos os processos com tempo de chegada menor ou igual ao tempo atual na fila
        while (unservedRRProcesses.front().getArrivalTime() <= currentTime && !unservedRRProcesses.empty())
        {   
            queue_rr.push(unservedRRProcesses.front());
            unservedRRProcesses.pop();
        }

        // Se a fila estiver vazia, atualiza o tempo atual e passa para a próxima iteração
        if (queue_rr.empty())
        {
            currentTime++;
            continue;
        }

        // Servido o processo atual
        if (queue_rr.front().getWasAnswered())
        {   
            // Adiciona o tempo esperando correspondente
            queue_rr.front().addWaitingTime(currentTime -  queue_rr.front().getLastTimeRunning());
        }else{
            queue_rr.front().setWasAnswered(true);
            queue_rr.front().setResponseTime(currentTime -  queue_rr.front().getArrivalTime());
            queue_rr.front().addWaitingTime(currentTime -  queue_rr.front().getArrivalTime());
        }
        
    
        // Calculando tempo gasto com o processo
        if (queue_rr.front().getRemaingDurationTime() >= QUANTUM)
        {
            // Atualiza o tempo atual com o tempo gasto no com o processo
            currentTime += QUANTUM;
            queue_rr.front().decreaseRemainingDurationTime(QUANTUM);
            queue_rr.front().setLastTimeRunning(currentTime);
        }else
        {
            // Atualiza o tempo atual com o tempo gasto no com o processo
            currentTime += queue_rr.front().getRemaingDurationTime();

            queue_rr.front().decreaseRemainingDurationTime(queue_rr.front().getRemaingDurationTime());
            queue_rr.front().setLastTimeRunning(currentTime);
        }
        
        // Verficando se o processo retornará para a fila
        if (queue_rr.front().getRemaingDurationTime() != 0)
        {
            // Antes do processo voltar para a fila, é necessário adicionar os processos com tempo de entrada menor ou igual
            while (unservedRRProcesses.front().getArrivalTime() <= currentTime && !unservedRRProcesses.empty())
            {   
                queue_rr.push(unservedRRProcesses.front());
                unservedRRProcesses.pop();
            }
            // Readiciona no fim da fila
            queue_rr.push(queue_rr.front());

            // Retira do inicio da fila
            queue_rr.pop();

            continue;
        }

        // Calculando o tempo de retorno
        queue_rr.front().setTurnaroundTime(currentTime - queue_rr.front().getArrivalTime());
       
        // Guardando o processo e retirando da fila
        this->servedRRProcesses.push_back(queue_rr.front());
        queue_rr.pop();
        
    }
    
    return 0;
}

bool Scheduler::calculateAllAvarages(){

    // Zera as métricas inicialmente
    fcfsMetrics.averageResponseTime = 0;
    fcfsMetrics.averageTurnaroundTime = 0;
    fcfsMetrics.averageWaitingTime = 0;
    sjfMetrics.averageResponseTime = 0;
    sjfMetrics.averageTurnaroundTime = 0;
    sjfMetrics.averageWaitingTime = 0;
    rrMetrics.averageResponseTime = 0;
    rrMetrics.averageTurnaroundTime = 0;
    rrMetrics.averageWaitingTime = 0;
    
    if (!servedFCFSProcesses.empty())
    {
        // Acumula todas as métricas
        for (size_t i = 0; i < servedFCFSProcesses.size(); i++)
        {
            fcfsMetrics.averageResponseTime += servedFCFSProcesses[i].getResponseTime();
            fcfsMetrics.averageTurnaroundTime += servedFCFSProcesses[i].getTurnaroundTime();
            fcfsMetrics.averageWaitingTime += servedFCFSProcesses[i].getWaitingTime(); 
        }
        // Divide o acumulado pela quantidade de processos
        fcfsMetrics.averageResponseTime = fcfsMetrics.averageResponseTime/servedFCFSProcesses.size();
        fcfsMetrics.averageTurnaroundTime = fcfsMetrics.averageTurnaroundTime/servedFCFSProcesses.size();
        fcfsMetrics.averageWaitingTime = fcfsMetrics.averageWaitingTime/servedFCFSProcesses.size();   
    }
    
    if (!servedSJFProcesses.empty())
    {
        // Acumula todas as métricas
        for (size_t i = 0; i < servedSJFProcesses.size(); i++)
        {
            sjfMetrics.averageResponseTime += servedSJFProcesses[i].getResponseTime();
            sjfMetrics.averageTurnaroundTime += servedSJFProcesses[i].getTurnaroundTime();
            sjfMetrics.averageWaitingTime += servedSJFProcesses[i].getWaitingTime(); 
        }
        // Divide o acumulado pela quantidade de processos
        sjfMetrics.averageResponseTime = sjfMetrics.averageResponseTime/servedSJFProcesses.size();
        sjfMetrics.averageTurnaroundTime = sjfMetrics.averageTurnaroundTime/servedSJFProcesses.size();
        sjfMetrics.averageWaitingTime = sjfMetrics.averageWaitingTime/servedSJFProcesses.size();
    }

    if (!servedRRProcesses.empty())
    {
        // Acumula todas as métricas
        for (size_t i = 0; i < servedRRProcesses.size(); i++)
        {
            rrMetrics.averageResponseTime += servedRRProcesses[i].getResponseTime();
            rrMetrics.averageTurnaroundTime += servedRRProcesses[i].getTurnaroundTime();
            rrMetrics.averageWaitingTime += servedRRProcesses[i].getWaitingTime(); 
        }
        // Divide o acumulado pela quantidade de processos
        rrMetrics.averageResponseTime = rrMetrics.averageResponseTime/servedRRProcesses.size();
        rrMetrics.averageTurnaroundTime = rrMetrics.averageTurnaroundTime/servedRRProcesses.size();
        rrMetrics.averageWaitingTime = rrMetrics.averageWaitingTime/servedRRProcesses.size();
    }
    
    return 0;
}

void Scheduler::printAllAvarages() {
    std::cout << std::fixed << std::setprecision(1);
    
    std::cout << "FCFS " << fcfsMetrics.averageTurnaroundTime << " "
              << fcfsMetrics.averageResponseTime << " "
              << fcfsMetrics.averageWaitingTime << std::endl;
    
    std::cout << "SJF " << sjfMetrics.averageTurnaroundTime << " "
              << sjfMetrics.averageResponseTime << " "
              << sjfMetrics.averageWaitingTime << std::endl;
    
    std::cout << "RR " << rrMetrics.averageTurnaroundTime << " "
              << rrMetrics.averageResponseTime << " "
              << rrMetrics.averageWaitingTime << std::endl;
}

void Scheduler::sortQueueByDurationTime(std::queue<Process>& q) {
    std::vector<Process> vec;

    // Move elementos da fila para o vetor
    while (!q.empty()) {
        vec.push_back(q.front());
        q.pop();
    }

    // Ordena o vetor com base no tempo de duração
    std::sort(vec.begin(), vec.end(), [](Process a, Process b) {
        return a.getDurationTime() < b.getDurationTime();  // Exemplo: ordenar por tempo de chegada
    });

    // Move os elementos ordenados de volta para a fila
    for (const auto& p : vec) {
        q.push(p);
    }
}