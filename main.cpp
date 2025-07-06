#include "SistemaRegistro.h"
#include "Registro.h"
#include <iostream>
#include <stdexcept>
#include <vector>

void imprimirSeparador() {
    std::cout << "----------------------------------------\n";
}

int main() {
    SistemaArquivosRegistros sistema;

    std::cout << "Sistema de Registros - Demonstração\n";
    imprimirSeparador();

    // Teste 1: Inserir registros válidos
    std::cout << "Tentando inserir registros válidos...\n";
    try {
        sistema.inserirRegistro(Registro("11122233344", "Ana Silva", "01/01/1990"));
        std::cout << "Ana Silva inserida.\n";
        sistema.inserirRegistro(Registro("55566677788", "Carlos Souza", "15/05/1985"));
        std::cout << "Carlos Souza inserido.\n";
        sistema.inserirRegistro(Registro("99900011122", "Beatriz Lima", "20/11/2000"));
        std::cout << "Beatriz Lima inserida.\n";
    } catch (const std::exception& e) {
        std::cerr << "Erro ao inserir registro válido: " << e.what() << '\n';
    }
    sistema.imprimirTodos();
    sistema.imprimirOrdenados();
    imprimirSeparador();

    // Teste 2: Tentar inserir CPF duplicado
    std::cout << "Tentando inserir CPF duplicado (11122233344)...\n";
    try {
        sistema.inserirRegistro(Registro("11122233344", "Ana Silva Duplicada", "02/02/1991"));
    } catch (const std::exception& e) {
        std::cerr << "Erro esperado ao inserir CPF duplicado: " << e.what() << '\n';
    }
    imprimirSeparador();

    // Teste 3: Tentar inserir CPF inválido (curto)
    std::cout << "Tentando inserir CPF inválido (123)...\n";
    try {
        sistema.inserirRegistro(Registro("123", "Curto", "03/03/1992"));
    } catch (const std::exception& e) {
        std::cerr << "Erro esperado ao inserir CPF inválido: " << e.what() << '\n';
    }
    imprimirSeparador();

    // Teste 4: Buscar registro existente
    std::cout << "Buscando Carlos Souza (55566677788)...\n";
    try {
        Registro r = sistema.buscarPorCpf("55566677788");
        std::cout << "Encontrado: ";
        r.imprimir();
    } catch (const std::exception& e) {
        std::cerr << "Erro ao buscar Carlos Souza: " << e.what() << '\n';
    }
    imprimirSeparador();

    // Teste 5: Buscar registro inexistente
    std::cout << "Buscando CPF inexistente (00000000000)...\n";
    try {
        Registro r = sistema.buscarPorCpf("00000000000");
        r.imprimir(); // Não deve chegar aqui
    } catch (const std::exception& e) {
        std::cerr << "Erro esperado ao buscar CPF inexistente: " << e.what() << '\n';
    }
    imprimirSeparador();

    // Teste 6: Remover registro existente
    std::cout << "Removendo Ana Silva (11122233344)...\n";
    try {
        sistema.removerPorCpf("11122233344");
        std::cout << "Ana Silva removida.\n";
    } catch (const std::exception& e) {
        std::cerr << "Erro ao remover Ana Silva: " << e.what() << '\n';
    }
    sistema.imprimirTodos();
    sistema.imprimirOrdenados();
    imprimirSeparador();

    // Teste 7: Tentar buscar registro removido
    std::cout << "Tentando buscar Ana Silva (removida)...\n";
    try {
        Registro r = sistema.buscarPorCpf("11122233344");
        r.imprimir(); // Não deve chegar aqui
    } catch (const std::exception& e) {
        std::cerr << "Erro esperado ao buscar registro removido: " << e.what() << '\n';
    }
    imprimirSeparador();

    // Teste 8: Tentar remover registro já removido
    std::cout << "Tentando remover Ana Silva novamente...\n";
    try {
        sistema.removerPorCpf("11122233344");
    } catch (const std::exception& e) {
        std::cerr << "Erro esperado ao remover registro já removido/inexistente no índice: " << e.what() << '\n';
    }
    imprimirSeparador();

    // Teste 9: Tentar remover registro inexistente
    std::cout << "Tentando remover CPF inexistente (12345678901)...\n";
    try {
        sistema.removerPorCpf("12345678901");
    } catch (const std::exception& e) {
        std::cerr << "Erro esperado ao remover CPF inexistente: " << e.what() << '\n';
    }
    imprimirSeparador();

    // Teste 10: Inserir mais um registro para verificar ordenação e EDL
    std::cout << "Inserindo mais um registro (Pedro Rocha - 00100200304)...\n";
     try {
        sistema.inserirRegistro(Registro("00100200304", "Pedro Rocha", "10/10/1970"));
        std::cout << "Pedro Rocha inserido.\n";
    } catch (const std::exception& e) {
        std::cerr << "Erro ao inserir Pedro Rocha: " << e.what() << '\n';
    }
    sistema.imprimirTodos();
    sistema.imprimirOrdenados();
    imprimirSeparador();

    std::cout << "Demonstração concluída.\n";
    return 0;
}
