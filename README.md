# README #
** Visão Geral**
O objetivo do projeto Gremlins é motivar o uso de listas encadeadas em um contexto de aplicação real. A aplicação selecionada
é um gerenciador de memória (GM). Implementar um GM não é uma tarefa trivial porém é importante em situações na qual é necessário
ter total controle sobre a organização de memória e melhorar o desempenho de tempo associado à requisições de memória
pela aplicação-alvo.

### MEMBBROS DA EQUIPE ###
* Igor A. Brandão
* Leandro Antonio F. Silva

### COMO COMPILAR ###
* Use o makefile digitando o comando **'make'** pelo terminal, após ter navegado para a pasta do projeto.

### COMO EXECUTAR O PROGRAMA ###
Para executar o Gremlins é necessário chamar o arquivo executável após compilar com o comando **'make'** pelo terminal,
assim:\n
* ./bin/gremlins\n

### LISTA DE CLASSES ###
As classes utilizadas pelo programa são as seguintes:

**StoragePool.h** => Provê a definição geral dos métodos Allocate() e Free().

**SLPool.h** => Implementa de fatos os métodos Allocate() e Free().

**Event.h** => Manipula o timeStamp e o memoryPtr para ser usado na priority_queue.

**SLPoolTester.h** => Implementa o método StoragePoolTest() para testar a eficiência dos métodos do gerenciador de memória.

Além disso, também criou-se um arquivo **MempoolCommon.h** para que as definições dos operadores "new" e "delete" sejam sobrescritas.
