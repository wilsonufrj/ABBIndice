#ifndef ABBINDICE_H
#define ABBINDICE_H

#include "ArvoreBinariaBusca.h" // Inclui a classe base
#include "No.h" // Para No<Par>
#include <string>
#include <vector>
#include <stdexcept> // Para std::runtime_error

// Definição da estrutura ParChaveIndice (pode ser colocada aqui ou em seu próprio header se usada em outros lugares)
template <typename Chave>
struct ParChaveIndice {
  Chave chave;
  size_t indice;

  ParChaveIndice(const Chave& c, size_t i) : chave(c), indice(i) {}

  // Operadores necessários para ArvoreBinariaBusca
  bool operator<(const ParChaveIndice& outro) const {
    return chave < outro.chave;
  }
  bool operator==(const ParChaveIndice& outro) const { // Usado para remoção e busca exata
    return chave == outro.chave;
  }
  // Adicionando operador > para consistência, embora ArvoreBinariaBusca use <
   bool operator>(const ParChaveIndice& outro) const {
    return chave > outro.chave;
  }
};


template <typename Chave>
class ABBIndice : public ArvoreBinariaBusca<ParChaveIndice<Chave>> {
 private:
  using Par = ParChaveIndice<Chave>;
  // Usando this->raiz para acessar o membro da classe base template
  // No<Par>* buscarNoPorChave(No<Par>* no, const Chave& chave) const; // Implementação movida para baixo

 public:
  ABBIndice();
  // O construtor de cópia padrão e operador de atribuição gerados pelo compilador
  // devem funcionar bem aqui, pois ArvoreBinariaBusca tem os seus próprios.
  // Se necessário, podem ser definidos explicitamente.
  // ABBIndice(const ABBIndice& outra);
  // ABBIndice& operator=(const ABBIndice& outra);

  void inserir(const Chave& chave, size_t indice);
  size_t buscarIndice(const Chave& chave) const;
  bool contemChave(const Chave& chave) const;
  void remover(const Chave& chave); // Remove pela chave

  std::vector<Chave> obterChavesOrdenadas() const;
  std::vector<size_t> obterIndicesOrdenados() const;

 protected: // Mudado para protected para permitir acesso na implementação abaixo
  // Helper para buscar Nó por chave, similar ao buscarNo da classe base mas compara só a chave.
  // Precisa acessar this->raiz.
  No<Par>* buscarNoPorChave(No<Par>* no, const Chave& chave) const {
    if (no == nullptr) return nullptr;

    if (chave < no->dado.chave) {
      return buscarNoPorChave(no->esquerda, chave);
    } else if (no->dado.chave < chave) { // Assumindo que Chave suporta operador <
      return buscarNoPorChave(no->direita, chave);
    } else { // chaves são iguais
      return no;
    }
  }
};

// Implementações de template

template <typename Chave>
ABBIndice<Chave>::ABBIndice() : ArvoreBinariaBusca<Par>() {}

// Se definidos explicitamente:
// template <typename Chave>
// ABBIndice<Chave>::ABBIndice(const ABBIndice& outra) : ArvoreBinariaBusca<Par>(outra) {}

// template <typename Chave>
// ABBIndice<Chave>& ABBIndice<Chave>::operator=(const ABBIndice& outra) {
//   ArvoreBinariaBusca<Par>::operator=(outra);
//   return *this;
// }

template <typename Chave>
void ABBIndice<Chave>::inserir(const Chave& chave, size_t indice) {
  // A classe base ArvoreBinariaBusca::inserir espera um Par.
  this->inserirNo(this->raiz, Par(chave, indice)); // Chamando o método protegido da classe base
                                                  // ou this->raiz = this->inserirNo(this->raiz, Par(chave, indice));
                                                  // dependendo de como inserir é implementado na base.
                                                  // Assumindo que ArvoreBinariaBusca::inserir(const T& valor)
                                                  // chama o inserirNo protegido.
  ArvoreBinariaBusca<Par>::inserir(Par(chave, indice));
}

template <typename Chave>
size_t ABBIndice<Chave>::buscarIndice(const Chave& chave) const {
  No<Par>* no = buscarNoPorChave(this->raiz, chave);
  if (no == nullptr) {
    throw std::runtime_error("Chave não encontrada na ABBIndice");
  }
  return no->dado.indice;
}

template <typename Chave>
bool ABBIndice<Chave>::contemChave(const Chave& chave) const {
  return buscarNoPorChave(this->raiz, chave) != nullptr;
}

template <typename Chave>
void ABBIndice<Chave>::remover(const Chave& chave) {
  // Para remover, precisamos de um Par. O índice não importa para a comparação na árvore,
  // apenas a chave. Usamos um índice dummy (ex: 0).
  // A lógica de remoção da ArvoreBinariaBusca usará operator< e operator== de ParChaveIndice.
  ArvoreBinariaBusca<Par>::remover(Par(chave, 0));
}

template <typename Chave>
std::vector<Chave> ABBIndice<Chave>::obterChavesOrdenadas() const {
  std::vector<Par> pares = this->obterElementosOrdenados(); // Da classe base
  std::vector<Chave> chaves;
  chaves.reserve(pares.size()); // Otimização
  for (const auto& par : pares) {
    chaves.push_back(par.chave);
  }
  return chaves;
}

template <typename Chave>
std::vector<size_t> ABBIndice<Chave>::obterIndicesOrdenados() const {
  std::vector<Par> pares = this->obterElementosOrdenados(); // Da classe base
  std::vector<size_t> indices;
  indices.reserve(pares.size()); // Otimização
  for (const auto& par : pares) {
    indices.push_back(par.indice);
  }
  return indices;
}

#endif  // ABBINDICE_H
