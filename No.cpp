template <typename T>
class No {
 public:
  T dado;
  No<T>* esquerda;
  No<T>* direita;

  No(const T& valor) : dado(valor), esquerda(nullptr), direita(nullptr) {}
};