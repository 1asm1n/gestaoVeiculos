#ifndef LOCACOES_H
#define LOCACOES_H

#define MAX_LOCACOES 200

typedef struct {
    char cpf_funcionario[15];  // CPF do funcionário
    char placa_veiculo[10];    // Placa do veículo
    char data_inicio[11];      // Data de início (DD/MM/AAAA)
    char data_fim[11];         // Data de fim (DD/MM/AAAA)
    char status[20];           // "ATIVA", "FINALIZADA", "CANCELADA"
} Locacao;

extern Locacao locacoes[MAX_LOCACOES];
extern int totalLocacoes;

// Funções de persistência
void carregarLocacoes();
void salvarLocacoes();

// Funções de CRUD
void criarLocacao();
void finalizarLocacao();
void listarLocacoes();

// Funções de busca
void listarLocacoesPorFuncionario();
void listarLocacoesPorVeiculo();

// Funções de busca sequencial e binária
int buscaSequencialLocacao(const char *cpf, const char *placa);
int buscaBinariaLocacao(const char *cpf, const char *placa);

// Função de ordenação
void ordenarLocacoesPorData();

#endif // LOCACOES_H
