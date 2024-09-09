# Projeto de Escalonador de Processos

Este projeto simula um escalonador de processos utilizando três algoritmos diferentes: FCFS (First-Come, First-Served), SJF (Shortest Job First) e RR (Round Robin). O projeto foi desenvolvido em C++ e inclui métodos para calcular e exibir métricas de desempenho dos algoritmos.

## Estrutura do Projeto

```
/build            # Contém os arquivos gerados pela compilação
/src              # Código fonte (.cpp e .h)
/instances        # Arquivos de entrada (ex: instancias.txt)
/docs             # Arquivo .pdf com a descrição do projeto
Makefile          # Arquivo Makefile para gerenciar a compilação e execução
build.sh          # Script para compilar o projeto
```

## Pré-requisitos

- **Compilador C++:** O projeto foi desenvolvido e testado com `g++`.
- **make:** Opcional, para usar o `Makefile`. Caso não tenha o `make` instalado, você pode usar os scripts de shell fornecidos.

## Compilação e Execução

### Usando o Makefile

Para compilar o projeto usando o `Makefile`, execute o seguinte comando no diretório principal:

```bash
make
```

Isso irá compilar o código e gerar o executável `avob_scheduler`.

Para limpar os arquivos gerados, use:

```bash
make clean
```

Para compilar e executar o programa com um arquivo de instância específico, use:

```bash
make run INSTANCES_FILE=instances/instance1.txt
```

### Usando Scripts de Shell

Se o `make` não estiver disponível, você pode usar os scripts de shell fornecidos:

- **Compilar o Projeto:**

  ```bash
  ./build.sh
  ```

- **Executar o Projeto:**

  ```bash
  ./build/avob_scheduler instances/instance1.txt
  ```

## Arquivos

- **`src/`**: Contém o código fonte do projeto.
  - `main.cpp`: Ponto de entrada do programa.
  - `Process.cpp` / `Process.h`: Implementação e declaração da classe `Process`.
  - `Scheduler.cpp` / `Scheduler.h`: Implementação e declaração da classe `Scheduler`.
- **`instances/`**: Contém arquivos de entrada no formato `tempo_de_chegada duracao` (ex: `instancia1.txt`).
- **`Makefile`**: Arquivo para gerenciar a compilação usando `make`.
- **`build.sh`**: Script para compilar o projeto.

## Uso

1. **Prepare o Arquivo de Entrada:**
   - Coloque seus arquivos de entrada na pasta `instances/`. O formato do arquivo deve ser:
     ```
     tempo_de_chegada duracao
     ```

2. **Compile o Projeto:**
   - Usando `make` ou o script `build.sh`.

3. **Execute o Programa:**
   - Usando `make run INSTANCE_FILE=path_to_file` ou executando o executável `./build/avob_scheduler path_to_file`.