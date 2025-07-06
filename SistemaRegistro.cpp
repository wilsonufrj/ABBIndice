#include "SistemaRegistro.h"
#include <iostream> // Para std::cout
#include <stdexcept> // Para std::invalid_argument, std::runtime_error
#include <algorithm> // Para std::find_if, se necessário para verificações mais complexas

// Construtor (opcional, pode ser vazio se nenhuma inicialização especial for necessária)
SistemaArquivosRegistros::SistemaArquivosRegistros() {
    // Inicializações, se houver.
    // Por exemplo, `edl` e `indice` já são inicializados por seus construtores padrão.
}

void SistemaArquivosRegistros::inserirRegistro(const Registro& reg) {
    if (reg.getCpf().empty() || reg.getCpf().length() != 11) {
        // A validação primária do tamanho do CPF agora é feita no construtor de Registro.
        // Esta checagem aqui em SistemaArquivosRegistros torna-se uma defesa adicional,
        // caso um Registro seja criado de alguma outra forma (improvável no design atual)
        // ou se quisermos ser extra cuidadosos.
        // A exceção lançada pelo construtor de Registro (se o CPF for inválido)
        // já impedirá a execução de continuar.
        throw std::invalid_argument("CPF inválido. Deve ter 11 caracteres.");
    }

    // Verifica se o CPF já existe e não está deletado
    // A busca no índice pode lançar uma exceção se a chave não for encontrada.
    // Se a chave for encontrada, verificamos se o registro correspondente está ativo.
    //
    // Verifica se o CPF já existe e está ativo.
    // indice.contemChave deve retornar true se a chave existe, false caso contrário.
    // Não se espera que lance exceção por chave não encontrada.
    if (indice.contemChave(reg.getCpf())) {
        // Se chegou aqui, a chave (CPF) já existe no índice.
        // Poderíamos, opcionalmente, verificar se o registro em edl[indice.buscarIndice(reg.getCpf())]
        // está deletado, caso quiséssemos permitir re-inserção em CPFs "deletados logicamente".
        // Mas a lógica atual é mais simples: se está no índice, está ativo.
        throw std::runtime_error("CPF já cadastrado e ativo no sistema.");
    }

    // Se passou pelas verificações, pode inserir.
    size_t novoIndice = edl.size(); // O novo registro será adicionado no final do vetor EDL
    edl.push_back(reg);             // Adiciona o registro ao EDL

    try {
        indice.inserir(reg.getCpf(), novoIndice); // Insere o CPF e o índice no EDL na árvore de índice
    } catch (...) {
        // Se a inserção no índice falhar, precisamos reverter a adição ao EDL para manter a consistência.
        edl.pop_back();
        throw; // Relança a exceção original da falha de inserção no índice
    }
}

Registro SistemaArquivosRegistros::buscarPorCpf(std::string cpf) const {
    if (cpf.empty() || cpf.length() != 11) {
        throw std::invalid_argument("CPF para busca é inválido.");
    }
    size_t indiceReg = indice.buscarIndice(cpf); // Lança exceção se não encontrar

    // Não é necessário verificar `indiceReg >= edl.size()` se o índice está correto,
    // mas é uma boa salvaguarda.
    if (indiceReg >= edl.size()) {
        // Isso indicaria um estado inconsistente entre o índice e o EDL.
        throw std::runtime_error("Erro interno: Índice aponta para fora dos limites do EDL.");
    }

    const Registro& reg = edl[indiceReg];
    // Se a remoção do índice funciona corretamente, um registro deletado não deveria ser encontrado aqui.
    // Mas se por acaso o índice ainda existir e o registro estiver marcado como deletado:
    if (reg.estaDeletado()) {
        // Isso também pode indicar uma inconsistência se `indice.remover` deveria ter tirado esta chave.
        throw std::runtime_error("Registro encontrado mas está marcado como deletado.");
    }

    return reg;
}

void SistemaArquivosRegistros::removerPorCpf(std::string cpf) {
    if (cpf.empty() || cpf.length() != 11) {
        throw std::invalid_argument("CPF para remoção é inválido.");
    }
    size_t indiceReg = indice.buscarIndice(cpf); // Lança exceção se não encontrar

    if (indiceReg >= edl.size()) {
        throw std::runtime_error("Erro interno: Índice para remoção aponta para fora dos limites do EDL.");
    }

    if (edl[indiceReg].estaDeletado()) {
        // Tentativa de remover um registro já marcado como deletado (e possivelmente já removido do índice).
        // Isso pode ser um erro ou apenas uma operação redundante, dependendo da política.
        // Se `buscarIndice` encontrou, significa que ainda está no índice.
        throw std::runtime_error("Registro já está marcado como deletado.");
    }

    edl[indiceReg].marcarDeletado(); // Marca o registro como deletado no EDL

    try {
        indice.remover(cpf); // Remove o CPF da árvore de índice
    } catch (...) {
        // Se a remoção do índice falhar, idealmente deveríamos reverter marcarDeletado,
        // mas Registro não tem um `desmarcarDeletado`. Isso indica uma possível necessidade de transação.
        // Por enquanto, apenas relançamos.
        // edl[indiceReg].desmarcarDeletado(); // Se existisse
        throw;
    }
}

std::vector<Registro> SistemaArquivosRegistros::gerarEDLOrdenada() const {
    std::vector<Registro> edlOrdenada;
    std::vector<size_t> indicesOrdenados = indice.obterIndicesOrdenados();

    edlOrdenada.reserve(indicesOrdenados.size());
    for (size_t idx : indicesOrdenados) {
        if (idx < edl.size() && !edl[idx].estaDeletado()) {
            edlOrdenada.push_back(edl[idx]);
        }
        // Se idx >= edl.size() ou edl[idx].estaDeletado(), algo está inconsistente
        // se o índice deveria apenas conter referências a registros válidos e ativos.
        // A lógica atual de `indice.remover` e `edl[idx].marcarDeletado` deve prevenir isso.
    }
    return edlOrdenada;
}

void SistemaArquivosRegistros::imprimirTodos() const {
    std::cout << "\nRegistros no sistema (ordem de inserção, apenas ativos):\n";
    bool encontrouAtivo = false;
    for (size_t i = 0; i < edl.size(); ++i) {
        if (!edl[i].estaDeletado()) {
            std::cout << "EDL[" << i << "]: "; // Mostra o índice físico no EDL
            edl[i].imprimir();
            encontrouAtivo = true;
        }
    }
    if (!encontrouAtivo) {
        std::cout << "Nenhum registro ativo no sistema.\n";
    }
}

void SistemaArquivosRegistros::imprimirOrdenados() const {
    std::vector<Registro> ordenados = gerarEDLOrdenada();
    std::cout << "\nRegistros ordenados por CPF:\n";
    if (ordenados.empty()) {
        std::cout << "Nenhum registro para exibir ou todos estão deletados.\n";
        return;
    }
    for (size_t i = 0; i < ordenados.size(); ++i) {
        // Não temos o índice original do EDL aqui, apenas a ordem.
        // Se precisar do índice do EDL, teria que buscá-lo ou armazená-lo de outra forma.
        std::cout << "Ordenado[" << i << "]: ";
        ordenados[i].imprimir();
    }
}
