#ifndef NO_H
#define NO_H

template <typename T>
class No {
 public:
  T dado;
  No<T>* esquerda;
  No<T>* direita;

  No(const T& valor);
};

// A implementação do construtor de template precisa estar no arquivo de cabeçalho
// ou incluída explicitamente se estiver em um .cpp, o que é menos comum para templates.
template <typename T>
No<T>::No(const T& valor) : dado(valor), esquerda(nullptr), direita(nullptr) {}

#endif  // NO_H
