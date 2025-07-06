#include <string>

#include "ABBIndice.cpp"
#include "Registro.cpp"

class SistemaArquivosRegistros {
 private:
  std::vector<Registro> edl;
  ABBIndice<std::string> indice;

 public:
  void inserirRegistro(const Registro& reg) {
    if (reg.getCpf().empty() || reg.getCpf().length() != 11) {
      throw std::invalid_argument("CPF inválido");
    }

    try {
      size_t indiceExistente = indice.buscarIndice(reg.getCpf());
      if (indiceExistente < edl.size() &&
          !edl[indiceExistente].estaDeletado()) {
        throw std::runtime_error("CPF já cadastrado");
      }
    } catch (...) {
    }

    size_t novoIndice = edl.size();
    edl.push_back(reg);

    indice.inserir(reg.getCpf(), novoIndice);
  }

  Registro buscarPorCpf(std::string cpf) const {
    size_t indiceReg = indice.buscarIndice(cpf);
    if (indiceReg >= edl.size()) {
      throw std::runtime_error("Índice inválido");
    }

    const Registro& reg = edl[indiceReg];
    if (reg.estaDeletado()) {
      throw std::runtime_error("Registro foi deletado");
    }

    return reg;
  }

  void removerPorCpf(std::string cpf) {
    size_t indiceReg = indice.buscarIndice(cpf);
    if (indiceReg >= edl.size()) {
      throw std::runtime_error("Índice inválido");
    }

    edl[indiceReg].marcarDeletado();

    indice.remover(cpf);
  }

  std::vector<Registro> gerarEDLOrdenada() const {
    std::vector<Registro> edlOrdenada;
    std::vector<size_t> indicesOrdenados = indice.obterIndicesOrdenados();

    for (size_t indice : indicesOrdenados) {
      if (!edl[indice].estaDeletado()) {
        edlOrdenada.push_back(edl[indice]);
      }
    }

    return edlOrdenada;
  }

  void imprimirTodos() const {
    std::cout << "\nRegistros no sistema:\n";
    for (size_t i = 0; i < edl.size(); ++i) {
      if (!edl[i].estaDeletado()) {
        std::cout << "[" << i << "] ";
        edl[i].imprimir();
      }
    }
  }

  void imprimirOrdenados() const {
    std::vector<Registro> ordenados = gerarEDLOrdenada();
    std::cout << "\nRegistros ordenados por CPF:\n";
    for (size_t i = 0; i < ordenados.size(); ++i) {
      std::cout << "[" << i << "] ";
      ordenados[i].imprimir();
    }
  }
};
