#include <initializer_list>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

class Registro {
 private:
  std::string cpf;
  std::string nome;
  std::string dataNasc;
  bool deletado;

 public:
  Registro()
      : cpf(11, ' '), nome(50, ' '), dataNasc(10, ' '), deletado(false) {}
  Registro(std::string c, std::string n, std::string d)
      : cpf(c), nome(n), dataNasc(d), deletado(false) {
    cpf.resize(11, ' ');
    nome.resize(50, ' ');
    dataNasc.resize(10, ' ');
  }

  bool operator<(const Registro& outro) const { return cpf < outro.cpf; }
  bool operator==(const Registro& outro) const { return cpf == outro.cpf; }

  void marcarDeletado() {
    deletado = true;
    cpf = std::string(11, ' ');
    nome = std::string(50, ' ');
    dataNasc = std::string(10, ' ');
  }
  bool estaDeletado() const { return deletado; }

  std::string getCpf() const { return cpf; }
  std::string getNome() const { return nome; }
  std::string getDataNasc() const { return dataNasc; }

  void imprimir() const {
    if (!deletado) {
      std::cout << "CPF: " << cpf << ", Nome: " << nome
                << ", Nascimento: " << dataNasc << std::endl;
    } else {
      std::cout << "[REGISTRO DELETADO]" << std::endl;
    }
  }
};