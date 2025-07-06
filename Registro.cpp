#include "Registro.h"

#include <iostream>
#include <string>
#include <vector> // Adicionado para std::vector, embora não usado diretamente aqui, pode ser útil no futuro ou em outros contextos.
#include <stdexcept> // Para std::invalid_argument e std::runtime_error, se necessário.

Registro::Registro()
    : cpf(11, ' '), nome(50, ' '), dataNasc(10, ' '), deletado(false) {}

Registro::Registro(std::string c, std::string n, std::string d)
    : deletado(false) { // Inicializar outros membros depois da validação do CPF
  if (c.length() != 11) {
    // Lançar uma exceção aqui. Para consistência com SistemaRegistro, usamos invalid_argument.
    // Adicionamos uma mensagem de debug para clareza, embora em produção possa ser removida.
    std::cerr << "[DEBUG REGISTRO] Tentativa de criar Registro com CPF de tamanho inválido: '" << c << "', Tamanho: " << c.length() << std::endl;
    throw std::invalid_argument("CPF fornecido ao construtor de Registro deve ter exatamente 11 caracteres. Recebido: '" + c + "'");
  }
  cpf = c; // Atribui o CPF validado.

  // Mantém o redimensionamento para nome e dataNasc como campos de tamanho fixo.
  nome = n;
  nome.resize(50, ' ');
  dataNasc = d;
  dataNasc.resize(10, ' ');
}

bool Registro::operator<(const Registro& outro) const {
  return cpf < outro.cpf;
}

bool Registro::operator==(const Registro& outro) const {
  return cpf == outro.cpf;
}

void Registro::marcarDeletado() {
  deletado = true;
  // Limpar os campos pode ser opcional, dependendo da lógica de "deletado"
  // cpf = std::string(11, ' ');
  // nome = std::string(50, ' ');
  // dataNasc = std::string(10, ' ');
}

bool Registro::estaDeletado() const { return deletado; }

std::string Registro::getCpf() const { return cpf; }

std::string Registro::getNome() const { return nome; }

std::string Registro::getDataNasc() const { return dataNasc; }

void Registro::imprimir() const {
  if (!deletado) {
    std::cout << "CPF: " << cpf << ", Nome: " << nome
              << ", Nascimento: " << dataNasc << std::endl;
  } else {
    std::cout << "[REGISTRO DELETADO]" << std::endl;
  }
}