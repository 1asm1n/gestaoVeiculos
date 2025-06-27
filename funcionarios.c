#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionarios.h"

typedef struct {
    char cpf_funcionario[15];
    char placa_veiculo[10];
    char data_inicio[11];
    char data_fim[11];
    char status[20];
} Locacao;

Funcionario funcionarios[MAX_FUNCIONARIOS];
int totalFuncionarios = 0;

void carregarFuncionarios() {
    FILE *file = fopen("funcionarios.dat", "rb");
    if (file == NULL) {
        totalFuncionarios = 0;
        return;
    }
    fread(&totalFuncionarios, sizeof(int), 1, file);
    fread(funcionarios, sizeof(Funcionario), totalFuncionarios, file);
    fclose(file);
}

void salvarFuncionarios() {
    FILE *file = fopen("funcionarios.dat", "wb");
    if (file == NULL) {
        printf("Erro ao salvar funcion�rios!\n");
        return;
    }
    fwrite(&totalFuncionarios, sizeof(int), 1, file);
    fwrite(funcionarios, sizeof(Funcionario), totalFuncionarios, file);
    fclose(file);
}

void adicionarFuncionario() {
    if (totalFuncionarios >= MAX_FUNCIONARIOS) {
        printf("Limite de funcion�rios atingido!\n");
        return;
    }
    Funcionario novo;
    printf("\n--- Cadastro de Funcion�rio ---\n");
    printf("CPF: ");
    fgets(novo.cpf, sizeof(novo.cpf), stdin);
    novo.cpf[strcspn(novo.cpf, "\n")] = '\0';
    for (int i = 0; i < totalFuncionarios; i++) {
        if (strcmp(funcionarios[i].cpf, novo.cpf) == 0) {
            printf("J� existe um funcion�rio com este CPF!\n");
            return;
        }
    }
    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Idade: ");
    scanf("%d", &novo.idade);
    getchar();
    funcionarios[totalFuncionarios++] = novo;
    salvarFuncionarios();
    printf("Funcion�rio cadastrado com sucesso!\n");
}

void removerFuncionario() {
    char cpf[15];
    printf("\n--- Remover Funcion�rio ---\n");
    printf("Informe o CPF do funcion�rio a ser removido: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';
    for (int i = 0; i < totalFuncionarios; i++) {
        if (strcmp(funcionarios[i].cpf, cpf) == 0) {
            for (int j = i; j < totalFuncionarios - 1; j++) {
                funcionarios[j] = funcionarios[j + 1];
            }
            totalFuncionarios--;
            salvarFuncionarios();
            printf("Funcion�rio removido com sucesso!\n");
            return;
        }
    }
    printf("Funcion�rio com CPF %s n�o encontrado.\n", cpf);
}

void listarFuncionarios() {
    printf("\n--- Lista de Funcion�rios ---\n");
    if (totalFuncionarios == 0) {
        printf("Nenhum funcion�rio cadastrado.\n");
        return;
    }
    for (int i = 0; i < totalFuncionarios; i++) {
        printf("%d) CPF: %s | Nome: %s | Idade: %d\n", i+1, funcionarios[i].cpf, funcionarios[i].nome, funcionarios[i].idade);
    }
}

int buscaSequencialFuncionario(const char *cpf) {
    for (int i = 0; i < totalFuncionarios; i++) {
        if (strcmp(funcionarios[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1;
}

int buscaBinariaFuncionario(const char *cpf) {
    int ini = 0, fim = totalFuncionarios - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(funcionarios[meio].cpf, cpf);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

void ordenarFuncionariosPorCPF() {
    FILE *file = fopen("funcionarios.dat", "rb");
    if (!file) {
        printf("Arquivo de funcionários não encontrado!\n");
        return;
    }

    // Lê total de funcionários
    int total;
    fread(&total, sizeof(int), 1, file);
    fclose(file);

    // Abre arquivo original para leitura e um arquivo temporário para escrita
    FILE *original = fopen("funcionarios.dat", "rb");
    FILE *ordenado = fopen("ordenado.dat", "wb+");
    if (!original || !ordenado) {
        printf("Erro ao abrir arquivos!\n");
        return;
    }

    fread(&total, sizeof(int), 1, original);
    fwrite(&total, sizeof(int), 1, ordenado); // reserva espaço no novo arquivo

    // Cria vetor para marcar quais posições já foram usadas
    int *usados = calloc(total, sizeof(int));

    for (int i = 0; i < total; i++) {
        Funcionario menor;
        long posMenor = -1;

        for (int j = 0; j < total; j++) {
            if (usados[j]) continue;

            Funcionario atual;
            fseek(original, sizeof(int) + j * sizeof(Funcionario), SEEK_SET);
            fread(&atual, sizeof(Funcionario), 1, original);

            if (posMenor == -1 || strcmp(atual.cpf, menor.cpf) < 0) {
                menor = atual;
                posMenor = j;
            }
        }

        // Escreve o menor funcionário no arquivo ordenado
        fseek(ordenado, sizeof(int) + i * sizeof(Funcionario), SEEK_SET);
        fwrite(&menor, sizeof(Funcionario), 1, ordenado);
        usados[posMenor] = 1;
    }

    free(usados);
    fclose(original);
    fclose(ordenado);

    // Substitui o arquivo original pelo ordenado
    remove("funcionarios.dat");
    rename("ordenado.dat", "funcionarios.dat");

    printf("Funcionários ordenados por CPF 100%% em disco!\n");
}

