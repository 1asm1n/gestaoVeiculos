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

    printf("Placa do veículo: ");
    fgets(nova.placa_veiculo, sizeof(nova.placa_veiculo), stdin);
    nova.placa_veiculo[strcspn(nova.placa_veiculo, "\n")] = '\0';

    int idx_veic = buscaSequencialVeiculo(nova.placa_veiculo);
    if (idx_veic == -1) {
        printf("Veículo não encontrado!\n");
        return;
    }

    for (int i = 0; i < totalLocacoes; i++) {
        if (strcmp(locacoes[i].placa_veiculo, nova.placa_veiculo) == 0 &&
            strcmp(locacoes[i].status, "ATIVA") == 0) {
            printf("Veículo já está em locação ativa!\n");
            return;
        }
    }

    printf("Data de início (DD/MM/AAAA): ");
    fgets(nova.data_inicio, sizeof(nova.data_inicio), stdin);
    nova.data_inicio[strcspn(nova.data_inicio, "\n")] = '\0';

    printf("Data de fim (DD/MM/AAAA): ");
    fgets(nova.data_fim, sizeof(nova.data_fim), stdin);
    nova.data_fim[strcspn(nova.data_fim, "\n")] = '\0';

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
    FILE *file = fopen("locacoes.dat", "rb");
    if (!file) {
        printf("Arquivo de locações não encontrado!\n");
        return;
    }

    int total;
    fread(&total, sizeof(int), 1, file);
    fclose(file);

    FILE *original = fopen("locacoes.dat", "rb");
    FILE *ordenado = fopen("ordenado_locacoes.dat", "wb+");
    if (!original || !ordenado) {
        printf("Erro ao abrir arquivos!\n");
        return;
    }

    fread(&total, sizeof(int), 1, original);
    fwrite(&total, sizeof(int), 1, ordenado); // reserva o espaço inicial com o total

    int *usados = calloc(total, sizeof(int));

    for (int i = 0; i < total; i++) {
        Locacao menor;
        long posMenor = -1;

        for (int j = 0; j < total; j++) {
            if (usados[j]) continue;

            Locacao atual;
            fseek(original, sizeof(int) + j * sizeof(Locacao), SEEK_SET);
            fread(&atual, sizeof(Locacao), 1, original);

            if (posMenor == -1 || strcmp(atual.data_inicio, menor.data_inicio) < 0) {
                menor = atual;
                posMenor = j;
            }
        }

        fseek(ordenado, sizeof(int) + i * sizeof(Locacao), SEEK_SET);
        fwrite(&menor, sizeof(Locacao), 1, ordenado);
        usados[posMenor] = 1;
    }

    free(usados);
    fclose(original);
    fclose(ordenado);

    remove("locacoes.dat");
    rename("ordenado_locacoes.dat", "locacoes.dat");

    printf("Locações ordenadas por data de início 100%% em disco!\n");
}

