#include <functional>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
struct No {
  T dado;
  No<T>* esquerda;
  No<T>* direita;

  No(const T& valor) : dado(valor), esquerda(nullptr), direita(nullptr) {}
};

template <typename T>
class ArvoreBinariaBusca {
 protected:
  No<T>* raiz;

  No<T>* inserirNo(No<T>* no, const T& valor) {
    if (no == nullptr) return new No<T>(valor);

    if (valor < no->dado) {
      no->esquerda = inserirNo(no->esquerda, valor);
    } else if (no->dado < valor) {
      no->direita = inserirNo(no->direita, valor);
    }

    return no;
  }

  No<T>* encontrarMinimo(No<T>* no) const {
    while (no != nullptr && no->esquerda != nullptr) {
      no = no->esquerda;
    }
    return no;
  }

  No<T>* removerNo(No<T>* no, const T& valor) {
    if (no == nullptr) return no;

    if (valor < no->dado) {
      no->esquerda = removerNo(no->esquerda, valor);
    } else if (no->dado < valor) {
      no->direita = removerNo(no->direita, valor);
    } else {
      if (no->esquerda == nullptr) {
        No<T>* temp = no->direita;
        delete no;
        return temp;
      } else if (no->direita == nullptr) {
        No<T>* temp = no->esquerda;
        delete no;
        return temp;
      }

      No<T>* temp = encontrarMinimo(no->direita);
      no->dado = temp->dado;
      no->direita = removerNo(no->direita, temp->dado);
    }
    return no;
  }

  void deletarArvore(No<T>* no) {
    if (no == nullptr) return;

    deletarArvore(no->esquerda);
    deletarArvore(no->direita);
    delete no;
  }

  No<T>* copiarArvore(No<T>* no) const {
    if (no == nullptr) return nullptr;

    No<T>* novoNo = new No<T>(no->dado);
    novoNo->esquerda = copiarArvore(no->esquerda);
    novoNo->direita = copiarArvore(no->direita);

    return novoNo;
  }

  void percursoPreOrdem(No<T>* no, std::function<void(const T&)> funcao) const {
    if (no == nullptr) return;

    funcao(no->dado);
    percursoPreOrdem(no->esquerda, funcao);
    percursoPreOrdem(no->direita, funcao);
  }

  void percursoEmOrdem(No<T>* no, std::function<void(const T&)> funcao) const {
    if (no == nullptr) return;

    percursoEmOrdem(no->esquerda, funcao);
    funcao(no->dado);
    percursoEmOrdem(no->direita, funcao);
  }

  void percursoPosOrdem(No<T>* no, std::function<void(const T&)> funcao) const {
    if (no == nullptr) return;

    percursoPosOrdem(no->esquerda, funcao);
    percursoPosOrdem(no->direita, funcao);
    funcao(no->dado);
  }

  void emLargura(std::function<void(const T&)> funcao) const {
    if (raiz == nullptr) return;

    std::queue<No<T>*> fila;
    fila.push(raiz);

    while (!fila.empty()) {
      No<T>* noAtual = fila.front();
      fila.pop();

      funcao(noAtual->dado);

      if (noAtual->esquerda != nullptr) {
        fila.push(noAtual->esquerda);
      }
      if (noAtual->direita != nullptr) {
        fila.push(noAtual->direita);
      }
    }
  }

  No<T>* buscarNo(No<T>* no, const T& valor) const {
    if (no == nullptr) return nullptr;

    if (valor < no->dado) {
      return buscarNo(no->esquerda, valor);
    } else if (no->dado < valor) {
      return buscarNo(no->direita, valor);
    } else {
      return no;
    }
  }

 public:
  ArvoreBinariaBusca() : raiz(nullptr) {}

  ArvoreBinariaBusca(std::initializer_list<T> lista) : raiz(nullptr) {
    for (const T& valor : lista) {
      inserir(valor);
    }
  }

  ArvoreBinariaBusca(const ArvoreBinariaBusca& outra) {
    raiz = copiarArvore(outra.raiz);
  }

  ArvoreBinariaBusca& operator=(const ArvoreBinariaBusca& outra) {
    if (this != &outra) {
      deletarArvore(raiz);
      raiz = copiarArvore(outra.raiz);
    }
    return *this;
  }

  virtual ~ArvoreBinariaBusca() { deletarArvore(raiz); }

  virtual void inserir(const T& valor) { raiz = inserirNo(raiz, valor); }

  virtual void remover(const T& valor) { raiz = removerNo(raiz, valor); }

  bool contem(const T& valor) const { return buscarNo(raiz, valor) != nullptr; }

  void preOrdem(std::function<void(const T&)> funcao) const {
    percursoPreOrdem(raiz, funcao);
  }

  void emOrdem(std::function<void(const T&)> funcao) const {
    percursoEmOrdem(raiz, funcao);
  }

  std::vector<T> obterElementosOrdenados() const {
    std::vector<T> elementos;
    emOrdem([&elementos](const T& valor) { elementos.push_back(valor); });
    return elementos;
  }

  void posOrdem(std::function<void(const T&)> funcao) const {
    percursoPosOrdem(raiz, funcao);
  }

  void emLargura(void (*funcao)(const T&)) const {
    if (raiz == nullptr) return;

    std::queue<No<T>*> fila;
    fila.push(raiz);

    while (!fila.empty()) {
      No<T>* noAtual = fila.front();
      fila.pop();

      funcao(noAtual->dado);

      if (noAtual->esquerda != nullptr) {
        fila.push(noAtual->esquerda);
      }
      if (noAtual->direita != nullptr) {
        fila.push(noAtual->direita);
      }
    }
  }

  bool vazia() const { return raiz == nullptr; }
};