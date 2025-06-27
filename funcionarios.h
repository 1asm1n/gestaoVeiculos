#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#define MAX_FUNCIONARIOS 100

typedef struct {
    char cpf[15];
    char nome[100];
    int idade;
} Funcionario;

extern Funcionario funcionarios[MAX_FUNCIONARIOS];
extern int totalFuncionarios;

void carregarFuncionarios();
void salvarFuncionarios();
void adicionarFuncionario();
void removerFuncionario();
void listarFuncionarios();
int buscaSequencialFuncionario(const char *cpf);
int buscaBinariaFuncionario(const char *cpf);
void ordenarFuncionariosPorCPF();

#endif // FUNCIONARIOS_H
