# Sistema de Gerenciamento de Registros

## 1. Descrição Curta

Este projeto implementa um sistema básico de gerenciamento de registros de pessoas, utilizando CPFs como identificador único. Ele permite inserir, buscar, remover e listar registros. Os registros são armazenados em uma estrutura de dados linear e indexados por CPF utilizando uma Árvore Binária de Busca para otimizar as operações de busca.

## 2. Estrutura de Módulos/Arquivos

O projeto está organizado nos seguintes módulos e arquivos:

*   **`Makefile`**: Script de compilação para o projeto. Constrói o executável `sistema_registros`.
*   **`main.cpp`**: Contém a função `main`, que serve como ponto de entrada do programa e demonstra as funcionalidades do sistema de registros através de uma série de testes.

*   **`Registro.h` / `Registro.cpp`**:
    *   Define a classe `Registro`, que encapsula os dados de uma pessoa (CPF, Nome, Data de Nascimento) e um status de deleção.
    *   O construtor de `Registro` valida o tamanho do CPF.
    *   Fornece métodos para acessar os dados e marcar um registro como deletado.

*   **`No.h`**:
    *   Define a classe template `No`, utilizada como nó na Árvore Binária de Busca.
    *   Contém um dado e ponteiros para os filhos esquerdo e direito.
    *   Como é uma classe template, a implementação está no arquivo de cabeçalho.

*   **`ArvoreBinariaBusca.h` / `ArvoreBinariaBusca.cpp`**:
    *   Define a classe template `ArvoreBinariaBusca`, uma implementação genérica de uma Árvore Binária de Busca (ABB).
    *   Suporta operações como inserção, remoção, busca e percursos (em ordem, pré-ordem, pós-ordem, em largura).
    *   As implementações dos métodos template estão no arquivo de cabeçalho para evitar problemas de vinculação. O `.cpp` correspondente está mínimo ou vazio.

*   **`ABBIndice.h` / `ABBIndice.cpp`**:
    *   Define a classe template `ABBIndice`, que herda de `ArvoreBinariaBusca`.
    *   É especializada para armazenar pares `ParChaveIndice<Chave>`, onde `Chave` é o tipo do CPF (string) e `indice` é a posição do registro no vetor de dados principal (EDL).
    *   Define a estrutura `ParChaveIndice` para armazenar a chave e o índice associado.
    *   Fornece métodos específicos para buscar e obter índices e chaves de forma ordenada.
    *   As implementações dos métodos template estão no arquivo de cabeçalho.

*   **`SistemaRegistro.h` / `SistemaRegistro.cpp`**:
    *   Define a classe `SistemaArquivosRegistros`, que é o módulo central do sistema.
    *   Utiliza um `std::vector<Registro>` (chamado `edl`) para armazenar os objetos `Registro` de forma contígua.
    *   Utiliza uma `ABBIndice<std::string>` para indexar os registros pelo CPF, mapeando o CPF para a sua posição no `edl`.
    *   Implementa as funcionalidades principais: `inserirRegistro`, `buscarPorCpf`, `removerPorCpf`, `gerarEDLOrdenada`, `imprimirTodos`, `imprimirOrdenados`.
    *   Realiza validações (CPF inválido, CPF duplicado) antes de realizar as operações.

## 3. Como Compilar

O projeto utiliza um `Makefile` para facilitar a compilação. Para compilar, navegue até o diretório raiz do projeto no terminal e execute o comando:

```bash
make
```

Isso irá compilar todos os arquivos fonte e criar o executável `sistema_registros` no diretório raiz. O Makefile também criará um subdiretório `obj/` para armazenar os arquivos objeto intermediários.

Para limpar os arquivos compilados (objetos e o executável), use:
```bash
make clean
```

## 4. Como Executar

Após a compilação bem-sucedida, o executável `sistema_registros` estará disponível no diretório raiz do projeto. Para executá-lo, utilize o seguinte comando no terminal:

```bash
./sistema_registros
```

O programa executará uma série de testes definidos em `main.cpp`, demonstrando as operações de inserção, busca, remoção e listagem de registros, incluindo o tratamento de casos de erro (CPFs inválidos, duplicados, buscas por CPFs inexistentes, etc.). A saída será exibida no console.
