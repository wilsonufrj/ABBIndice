#ifndef ARVOREBINARIABUSCA_H
#define ARVOREBINARIABUSCA_H

#include "No.h"  // Inclui a definição de No
#include <functional>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <vector>

template <typename T>
class ArvoreBinariaBusca {
 protected:
  No<T>* raiz;

  // Métodos auxiliares protegidos
  No<T>* inserirNo(No<T>* no, const T& valor);
  No<T>* encontrarMinimo(No<T>* no) const;
  No<T>* removerNo(No<T>* no, const T& valor);
  void deletarArvore(No<T>* no);
  No<T>* copiarArvore(No<T>* no) const;
  void percursoPreOrdem(No<T>* no, std::function<void(const T&)> funcao) const;
  void percursoEmOrdem(No<T>* no, std::function<void(const T&)> funcao) const;
  void percursoPosOrdem(No<T>* no, std::function<void(const T&)> funcao) const;
  // emLargura com std::function para consistência
  void emLarguraAux(No<T>* no, std::function<void(const T&)> funcao) const;
  No<T>* buscarNo(No<T>* no, const T& valor) const;

 public:
  ArvoreBinariaBusca();
  ArvoreBinariaBusca(std::initializer_list<T> lista);
  ArvoreBinariaBusca(const ArvoreBinariaBusca& outra);
  ArvoreBinariaBusca& operator=(const ArvoreBinariaBusca& outra);
  virtual ~ArvoreBinariaBusca();

  virtual void inserir(const T& valor);
  virtual void remover(const T& valor);
  bool contem(const T& valor) const;

  void preOrdem(std::function<void(const T&)> funcao) const;
  void emOrdem(std::function<void(const T&)> funcao) const;
  std::vector<T> obterElementosOrdenados() const;
  void posOrdem(std::function<void(const T&)> funcao) const;
  // Interface pública para emLargura
  void emLargura(std::function<void(const T&)> funcao) const;
  // Mantendo a sobrecarga original se necessário, mas preferindo std::function
  void emLargura(void (*funcao)(const T&)) const;

  bool vazia() const;
};

// Implementações de template vão aqui ou em um arquivo .tpp/.ipp incluído no final deste header.
// Para simplificar, colocaremos aqui.

template <typename T>
No<T>* ArvoreBinariaBusca<T>::inserirNo(No<T>* no, const T& valor) {
  if (no == nullptr) return new No<T>(valor);
  if (valor < no->dado) {
    no->esquerda = inserirNo(no->esquerda, valor);
  } else if (no->dado < valor) { // Evitar duplicatas, ou tratar como erro/ignorar
    no->direita = inserirNo(no->direita, valor);
  }
  return no;
}

template <typename T>
No<T>* ArvoreBinariaBusca<T>::encontrarMinimo(No<T>* no) const {
  while (no != nullptr && no->esquerda != nullptr) {
    no = no->esquerda;
  }
  return no;
}

template <typename T>
No<T>* ArvoreBinariaBusca<T>::removerNo(No<T>* no, const T& valor) {
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

template <typename T>
void ArvoreBinariaBusca<T>::deletarArvore(No<T>* no) {
  if (no == nullptr) return;
  deletarArvore(no->esquerda);
  deletarArvore(no->direita);
  delete no;
}

template <typename T>
No<T>* ArvoreBinariaBusca<T>::copiarArvore(No<T>* no) const {
  if (no == nullptr) return nullptr;
  No<T>* novoNo = new No<T>(no->dado);
  novoNo->esquerda = copiarArvore(no->esquerda);
  novoNo->direita = copiarArvore(no->direita);
  return novoNo;
}

template <typename T>
void ArvoreBinariaBusca<T>::percursoPreOrdem(No<T>* no, std::function<void(const T&)> funcao) const {
  if (no == nullptr) return;
  funcao(no->dado);
  percursoPreOrdem(no->esquerda, funcao);
  percursoPreOrdem(no->direita, funcao);
}

template <typename T>
void ArvoreBinariaBusca<T>::percursoEmOrdem(No<T>* no, std::function<void(const T&)> funcao) const {
  if (no == nullptr) return;
  percursoEmOrdem(no->esquerda, funcao);
  funcao(no->dado);
  percursoEmOrdem(no->direita, funcao);
}

template <typename T>
void ArvoreBinariaBusca<T>::percursoPosOrdem(No<T>* no, std::function<void(const T&)> funcao) const {
  if (no == nullptr) return;
  percursoPosOrdem(no->esquerda, funcao);
  percursoPosOrdem(no->direita, funcao);
  funcao(no->dado);
}

template <typename T>
void ArvoreBinariaBusca<T>::emLarguraAux(No<T>* no, std::function<void(const T&)> funcao) const {
    if (no == nullptr) return;
    std::queue<No<T>*> fila;
    fila.push(no);
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


template <typename T>
No<T>* ArvoreBinariaBusca<T>::buscarNo(No<T>* no, const T& valor) const {
  if (no == nullptr) return nullptr;
  if (valor < no->dado) {
    return buscarNo(no->esquerda, valor);
  } else if (no->dado < valor) {
    return buscarNo(no->direita, valor);
  } else {
    return no;
  }
}

// Construtores e Destrutor
template <typename T>
ArvoreBinariaBusca<T>::ArvoreBinariaBusca() : raiz(nullptr) {}

template <typename T>
ArvoreBinariaBusca<T>::ArvoreBinariaBusca(std::initializer_list<T> lista) : raiz(nullptr) {
  for (const T& valor : lista) {
    inserir(valor);
  }
}

template <typename T>
ArvoreBinariaBusca<T>::ArvoreBinariaBusca(const ArvoreBinariaBusca& outra) {
  raiz = copiarArvore(outra.raiz);
}

template <typename T>
ArvoreBinariaBusca<T>& ArvoreBinariaBusca<T>::operator=(const ArvoreBinariaBusca& outra) {
  if (this != &outra) {
    deletarArvore(raiz);
    raiz = copiarArvore(outra.raiz);
  }
  return *this;
}

template <typename T>
ArvoreBinariaBusca<T>::~ArvoreBinariaBusca() {
  deletarArvore(raiz);
}

// Métodos Públicos
template <typename T>
void ArvoreBinariaBusca<T>::inserir(const T& valor) {
  raiz = inserirNo(raiz, valor);
}

template <typename T>
void ArvoreBinariaBusca<T>::remover(const T& valor) {
  raiz = removerNo(raiz, valor);
}

template <typename T>
bool ArvoreBinariaBusca<T>::contem(const T& valor) const {
  return buscarNo(raiz, valor) != nullptr;
}

template <typename T>
void ArvoreBinariaBusca<T>::preOrdem(std::function<void(const T&)> funcao) const {
  percursoPreOrdem(raiz, funcao);
}

template <typename T>
void ArvoreBinariaBusca<T>::emOrdem(std::function<void(const T&)> funcao) const {
  percursoEmOrdem(raiz, funcao);
}

template <typename T>
std::vector<T> ArvoreBinariaBusca<T>::obterElementosOrdenados() const {
  std::vector<T> elementos;
  emOrdem([&elementos](const T& valor) { elementos.push_back(valor); });
  return elementos;
}

template <typename T>
void ArvoreBinariaBusca<T>::posOrdem(std::function<void(const T&)> funcao) const {
  percursoPosOrdem(raiz, funcao);
}

template <typename T>
void ArvoreBinariaBusca<T>::emLargura(std::function<void(const T&)> funcao) const {
    emLarguraAux(raiz, funcao);
}

template <typename T>
void ArvoreBinariaBusca<T>::emLargura(void (*funcao)(const T&)) const {
    // Adaptador para ponteiro de função para std::function
    emLarguraAux(raiz, std::function<void(const T&)>(funcao));
}


template <typename T>
bool ArvoreBinariaBusca<T>::vazia() const {
  return raiz == nullptr;
}

#endif  // ARVOREBINARIABUSCA_H
