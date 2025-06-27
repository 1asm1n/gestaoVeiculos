#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "locacoes.h"
#include "funcionarios.h"
#include "veiculos.h"

Locacao locacoes[MAX_LOCACOES];
int totalLocacoes = 0;

void carregarLocacoes() {
    FILE *file = fopen("locacoes.dat", "rb");
    if (file == NULL) {
        totalLocacoes = 0;
        return;
    }
    fread(&totalLocacoes, sizeof(int), 1, file);
    fread(locacoes, sizeof(Locacao), totalLocacoes, file);
    fclose(file);
}

void salvarLocacoes() {
    FILE *file = fopen("locacoes.dat", "wb");
    if (file == NULL) {
        printf("Erro ao salvar locações!\n");
        return;
    }
    fwrite(&totalLocacoes, sizeof(int), 1, file);
    fwrite(locacoes, sizeof(Locacao), totalLocacoes, file);
    fclose(file);
}

void criarLocacao() {
    if (totalLocacoes >= MAX_LOCACOES) {
        printf("Limite de locações atingido!\n");
        return;
    }
    
    Locacao nova;
    printf("\n--- Criar Nova Locação ---\n");
    
    // Solicitar CPF do funcionário
    printf("CPF do funcionário: ");
    fgets(nova.cpf_funcionario, sizeof(nova.cpf_funcionario), stdin);
    nova.cpf_funcionario[strcspn(nova.cpf_funcionario, "\n")] = '\0';
    
    // Verificar se funcionário existe
    int idx_func = buscaSequencialFuncionario(nova.cpf_funcionario);
    if (idx_func == -1) {
        printf("Funcionário não encontrado!\n");
        return;
    }
    
    // Solicitar placa do veículo
    printf("Placa do veículo: ");
    fgets(nova.placa_veiculo, sizeof(nova.placa_veiculo), stdin);
    nova.placa_veiculo[strcspn(nova.placa_veiculo, "\n")] = '\0';
    
    // Verificar se veículo existe
    int idx_veic = buscaSequencialVeiculo(nova.placa_veiculo);
    if (idx_veic == -1) {
        printf("Veículo não encontrado!\n");
        return;
    }
    
    // Verificar se veículo já está em locação ativa
    for (int i = 0; i < totalLocacoes; i++) {
        if (strcmp(locacoes[i].placa_veiculo, nova.placa_veiculo) == 0 && 
            strcmp(locacoes[i].status, "ATIVA") == 0) {
            printf("Veículo já está em locação ativa!\n");
            return;
        }
    }
    
    // Solicitar datas
    printf("Data de início (DD/MM/AAAA): ");
    fgets(nova.data_inicio, sizeof(nova.data_inicio), stdin);
    nova.data_inicio[strcspn(nova.data_inicio, "\n")] = '\0';
    
    printf("Data de fim (DD/MM/AAAA): ");
    fgets(nova.data_fim, sizeof(nova.data_fim), stdin);
    nova.data_fim[strcspn(nova.data_fim, "\n")] = '\0';
    
    // Definir status como ATIVA
    strcpy(nova.status, "ATIVA");
    
    locacoes[totalLocacoes++] = nova;
    salvarLocacoes();
    printf("Locação criada com sucesso!\n");
}

void finalizarLocacao() {
    char cpf[15], placa[10];
    printf("\n--- Finalizar Locação ---\n");
    printf("CPF do funcionário: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';
    
    printf("Placa do veículo: ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0';
    
    for (int i = 0; i < totalLocacoes; i++) {
        if (strcmp(locacoes[i].cpf_funcionario, cpf) == 0 && 
            strcmp(locacoes[i].placa_veiculo, placa) == 0 &&
            strcmp(locacoes[i].status, "ATIVA") == 0) {
            strcpy(locacoes[i].status, "FINALIZADA");
            salvarLocacoes();
            printf("Locação finalizada com sucesso!\n");
            return;
        }
    }
    printf("Locação ativa não encontrada!\n");
}

void cancelarLocacao() {
    char cpf[15], placa[10];
    printf("\n--- Cancelar Locação ---\n");
    printf("CPF do funcionário: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';
    
    printf("Placa do veículo: ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0';
    
    for (int i = 0; i < totalLocacoes; i++) {
        if (strcmp(locacoes[i].cpf_funcionario, cpf) == 0 && 
            strcmp(locacoes[i].placa_veiculo, placa) == 0 &&
            strcmp(locacoes[i].status, "ATIVA") == 0) {
            strcpy(locacoes[i].status, "CANCELADA");
            salvarLocacoes();
            printf("Locação cancelada com sucesso!\n");
            return;
        }
    }
    printf("Locação ativa não encontrada!\n");
}

void listarLocacoes() {
    printf("\n--- Lista de Todas as Locações ---\n");
    if (totalLocacoes == 0) {
        printf("Nenhuma locação cadastrada.\n");
        return;
    }
    for (int i = 0; i < totalLocacoes; i++) {
        printf("%d) CPF: %s | Placa: %s | Início: %s | Fim: %s | Status: %s\n",
            i+1,
            locacoes[i].cpf_funcionario,
            locacoes[i].placa_veiculo,
            locacoes[i].data_inicio,
            locacoes[i].data_fim,
            locacoes[i].status);
    }
}

void listarLocacoesPorFuncionario() {
    char cpf[15];
    printf("\n--- Locações por Funcionário ---\n");
    printf("CPF do funcionário: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';
    
    int encontrou = 0;
    for (int i = 0; i < totalLocacoes; i++) {
        if (strcmp(locacoes[i].cpf_funcionario, cpf) == 0) {
            if (!encontrou) {
                printf("Locações do funcionário %s:\n", cpf);
                encontrou = 1;
            }
            printf("- Placa: %s | Início: %s | Fim: %s | Status: %s\n",
                locacoes[i].placa_veiculo,
                locacoes[i].data_inicio,
                locacoes[i].data_fim,
                locacoes[i].status);
        }
    }
    if (!encontrou) {
        printf("Nenhuma locação encontrada para este funcionário.\n");
    }
}

void listarLocacoesPorVeiculo() {
    char placa[10];
    printf("\n--- Locações por Veículo ---\n");
    printf("Placa do veículo: ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0';
    
    int encontrou = 0;
    for (int i = 0; i < totalLocacoes; i++) {
        if (strcmp(locacoes[i].placa_veiculo, placa) == 0) {
            if (!encontrou) {
                printf("Locações do veículo %s:\n", placa);
                encontrou = 1;
            }
            printf("- CPF: %s | Início: %s | Fim: %s | Status: %s\n",
                locacoes[i].cpf_funcionario,
                locacoes[i].data_inicio,
                locacoes[i].data_fim,
                locacoes[i].status);
        }
    }
    if (!encontrou) {
        printf("Nenhuma locação encontrada para este veículo.\n");
    }
}

void listarLocacoesAtivas() {
    printf("\n--- Locações Ativas ---\n");
    int encontrou = 0;
    for (int i = 0; i < totalLocacoes; i++) {
        if (strcmp(locacoes[i].status, "ATIVA") == 0) {
            if (!encontrou) {
                encontrou = 1;
            }
            printf("- CPF: %s | Placa: %s | Início: %s | Fim: %s\n",
                locacoes[i].cpf_funcionario,
                locacoes[i].placa_veiculo,
                locacoes[i].data_inicio,
                locacoes[i].data_fim);
        }
    }
    if (!encontrou) {
        printf("Nenhuma locação ativa encontrada.\n");
    }
}

int buscaSequencialLocacao(const char *cpf, const char *placa) {
    for (int i = 0; i < totalLocacoes; i++) {
        if (strcmp(locacoes[i].cpf_funcionario, cpf) == 0 && 
            strcmp(locacoes[i].placa_veiculo, placa) == 0) {
            return i;
        }
    }
    return -1;
}

int buscaBinariaLocacao(const char *cpf, const char *placa) {
    int ini = 0, fim = totalLocacoes - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp_cpf = strcmp(locacoes[meio].cpf_funcionario, cpf);
        if (cmp_cpf == 0) {
            int cmp_placa = strcmp(locacoes[meio].placa_veiculo, placa);
            if (cmp_placa == 0) return meio;
            else if (cmp_placa < 0) ini = meio + 1;
            else fim = meio - 1;
        }
        else if (cmp_cpf < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

void ordenarLocacoesPorData() {
    FILE *file = fopen("locacoes.dat", "rb+");
    if (!file) {
        printf("Arquivo de locações não encontrado!\n");
        return;
    }
    int n;
    fread(&n, sizeof(int), 1, file);
    Locacao *arr = malloc(n * sizeof(Locacao));
    fread(arr, sizeof(Locacao), n, file);
    
    // Bubble Sort por data de início
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].data_inicio, arr[j+1].data_inicio) > 0) {
                Locacao tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
    
    rewind(file);
    fwrite(&n, sizeof(int), 1, file);
    fwrite(arr, sizeof(Locacao), n, file);
    fclose(file);
    free(arr);
    printf("Locações ordenadas por data!\n");
} 