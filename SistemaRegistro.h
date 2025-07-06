#ifndef SISTEMAREGISTRO_H
#define SISTEMAREGISTRO_H

#include "ABBIndice.h" // Para ABBIndice<std::string>
#include "Registro.h"  // Para a classe Registro
#include <string>
#include <vector>
#include <stdexcept> // Para std::invalid_argument, std::runtime_error
#include <iostream>  // Para imprimirTodos, imprimirOrdenados

class SistemaArquivosRegistros {
 private:
  std::vector<Registro> edl; // Estrutura de Dados Linear para armazenar os registros
  ABBIndice<std::string> indice; // Índice para CPFs usando ABBIndice

 public:
  SistemaArquivosRegistros(); // Construtor, se necessário

  void inserirRegistro(const Registro& reg);
  Registro buscarPorCpf(std::string cpf) const;
  void removerPorCpf(std::string cpf);
  std::vector<Registro> gerarEDLOrdenada() const;

  void imprimirTodos() const;
  void imprimirOrdenados() const;

  // Métodos adicionais podem ser declarados aqui, se necessário
};

#endif  // SISTEMAREGISTRO_H
