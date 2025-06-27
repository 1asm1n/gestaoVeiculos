#ifndef VEICULOS_H
#define VEICULOS_H

#define MAX_VEICULOS 100

typedef struct {
    char placa[10];
    char modelo[50];
    char marca[50];
    int ano;
    char cor[20];
    char cpf_funcionario[15];
} Veiculo;

extern Veiculo veiculos[MAX_VEICULOS];
extern int totalVeiculos;

void carregarVeiculos();
void salvarVeiculos();
void adicionarVeiculo();
void removerVeiculo();
void listarVeiculos();
void buscarVeiculoPorPlaca();
void associarVeiculoFuncionario();
int buscaSequencialVeiculo(const char *placa);
int buscaBinariaVeiculo(const char *placa);
void ordenarVeiculosPorPlaca();

#endif // VEICULOS_H
