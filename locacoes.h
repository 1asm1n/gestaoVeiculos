#ifndef LOCACOES_H
#define LOCACOES_H

#define MAX_LOCACOES 200

typedef struct {
    char cpf_funcionario[15];  // CPF do funcion�rio
    char placa_veiculo[10];    // Placa do ve�culo
    char data_inicio[11];      // Data de in�cio (DD/MM/AAAA)
    char data_fim[11];         // Data de fim (DD/MM/AAAA)
    char status[20];           // "ATIVA", "FINALIZADA", "CANCELADA"
} Locacao;

extern Locacao locacoes[MAX_LOCACOES];
extern int totalLocacoes;

// Fun��es de persist�ncia
void carregarLocacoes();
void salvarLocacoes();

// Fun��es de CRUD
void criarLocacao();
void finalizarLocacao();
void listarLocacoes();

// Fun��es de busca
void listarLocacoesPorFuncionario();
void listarLocacoesPorVeiculo();

// Fun��es de busca sequencial e bin�ria
int buscaSequencialLocacao(const char *cpf, const char *placa);
int buscaBinariaLocacao(const char *cpf, const char *placa);

// Fun��o de ordena��o
void ordenarLocacoesPorData();

#endif // LOCACOES_H
