#include <iostream>
#include <fstream>
#include <vector>
#include "Process.h"
#include "Scheduler.h"

int main(int argc, char* argv[]) {
    // Verifica se o número de argumentos está correto
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <caminho_da_instância>" << std::endl;
        return 1;
    }
    std::ifstream arquivo(argv[1]);
    int tempo_chegada, duracao;
    Scheduler scheduler;

    if (arquivo.is_open()) {
        while (arquivo >> tempo_chegada >> duracao) {
            Process process(tempo_chegada, duracao);
            scheduler.addProcess(process);
        }
        arquivo.close();
    } else {
        std::cerr << "Não foi possível abrir o arquivo!" << std::endl;
        return 1;
    }

    // Ordena os processos por tempo de chegada, cado o arquivo venha com processos fora de ordem
    scheduler.sortProcessByArrivialTime();

    // Executando os escalonamento nas filas
    scheduler.runFCSF();
    scheduler.runSJF();
    scheduler.runRR();


    scheduler.calculateAllAvarages();
    scheduler.printAllAvarages();
    return 0;
}