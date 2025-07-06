#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <iostream>

class Registro {
 private:
  std::string cpf;
  std::string nome;
  std::string dataNasc;
  bool deletado;

 public:
  Registro();
  Registro(std::string c, std::string n, std::string d);

  bool operator<(const Registro& outro) const;
  bool operator==(const Registro& outro) const;

  void marcarDeletado();
  bool estaDeletado() const;

  std::string getCpf() const;
  std::string getNome() const;
  std::string getDataNasc() const;

  void imprimir() const;
};

#endif  // REGISTRO_H
