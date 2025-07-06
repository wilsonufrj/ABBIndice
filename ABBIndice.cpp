#include "ArvoreBinariaBusca.cpp"

template <typename Chave>
struct ParChaveIndice {
  Chave chave;
  size_t indice;

  ParChaveIndice(const Chave& c, size_t i) : chave(c), indice(i) {}

  bool operator<(const ParChaveIndice& outro) const {
    return chave < outro.chave;
  }
  bool operator==(const ParChaveIndice& outro) const {
    return chave == outro.chave;
  }
};

template <typename Chave>
class ABBIndice : public ArvoreBinariaBusca<ParChaveIndice<Chave>> {
 private:
  using Par = ParChaveIndice<Chave>;
  using ArvoreBinariaBusca<Par>::raiz;

  No<Par>* buscarNoPorChave(No<Par>* no, const Chave& chave) const {
    if (no == nullptr) return nullptr;

    if (chave < no->dado.chave) {
      return buscarNoPorChave(no->esquerda, chave);
    } else if (no->dado.chave < chave) {
      return buscarNoPorChave(no->direita, chave);
    } else {
      return no;
    }
  }

 public:
  ABBIndice() : ArvoreBinariaBusca<Par>() {}
  ABBIndice(const ABBIndice& outra) : ArvoreBinariaBusca<Par>(outra) {}

  void inserir(const Chave& chave, size_t indice) {
    ArvoreBinariaBusca<Par>::inserir(Par(chave, indice));
  }

  size_t buscarIndice(const Chave& chave) const {
    No<Par>* no = buscarNoPorChave(raiz, chave);
    if (no == nullptr) {
      throw std::runtime_error("Chave não encontrada na ABB");
    }
    return no->dado.indice;
  }

  bool contemChave(const Chave& chave) const {
    return buscarNoPorChave(raiz, chave) != nullptr;
  }

  void remover(const Chave& chave) {
    ArvoreBinariaBusca<Par>::remover(Par(chave, 0));
  }

  std::vector<Chave> obterChavesOrdenadas() const {
    std::vector<Par> pares = this->obterElementosOrdenados();
    std::vector<Chave> chaves;
    for (const auto& par : pares) {
      chaves.push_back(par.chave);
    }
    return chaves;
  }

  std::vector<size_t> obterIndicesOrdenados() const {
    std::vector<Par> pares = this->obterElementosOrdenados();
    std::vector<size_t> indices;
    for (const auto& par : pares) {
      indices.push_back(par.indice);
    }
    return indices;
  }
};