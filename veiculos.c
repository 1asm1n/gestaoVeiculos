#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veiculos.h"
#include "funcionarios.h"

Veiculo veiculos[MAX_VEICULOS];
int totalVeiculos = 0;

void carregarVeiculos() {
    FILE *file = fopen("veiculos.dat", "rb");
    if (file == NULL) {
        totalVeiculos = 0;
        return;
    }
    fread(&totalVeiculos, sizeof(int), 1, file);
    fread(veiculos, sizeof(Veiculo), totalVeiculos, file);
    fclose(file);
}

void salvarVeiculos() {
    FILE *file = fopen("veiculos.dat", "wb");
    if (file == NULL) {
        printf("Erro ao salvar veículos!\n");
        return;
    }
    fwrite(&totalVeiculos, sizeof(int), 1, file);
    fwrite(veiculos, sizeof(Veiculo), totalVeiculos, file);
    fclose(file);
}

void adicionarVeiculo() {
    if (totalVeiculos >= MAX_VEICULOS) {
        printf("Limite de veículos atingido!\n");
        return;
    }
    Veiculo novo;
    printf("\n--- Cadastro de Veículo ---\n");
    printf("Placa: ");
    fgets(novo.placa, sizeof(novo.placa), stdin);
    novo.placa[strcspn(novo.placa, "\n")] = '\0';
    for (int i = 0; i < totalVeiculos; i++) {
        if (strcmp(veiculos[i].placa, novo.placa) == 0) {
            printf("Já existe um veículo com esta placa!\n");
            return;
        }
    }
    printf("Modelo: ");
    fgets(novo.modelo, sizeof(novo.modelo), stdin);
    novo.modelo[strcspn(novo.modelo, "\n")] = '\0';
    printf("Marca: ");
    fgets(novo.marca, sizeof(novo.marca), stdin);
    novo.marca[strcspn(novo.marca, "\n")] = '\0';
    printf("Ano: ");
    scanf("%d", &novo.ano);
    getchar();
    printf("Cor: ");
    fgets(novo.cor, sizeof(novo.cor), stdin);
    novo.cor[strcspn(novo.cor, "\n")] = '\0';
    printf("CPF do funcionário responsável: ");
    fgets(novo.cpf_funcionario, sizeof(novo.cpf_funcionario), stdin);
    novo.cpf_funcionario[strcspn(novo.cpf_funcionario, "\n")] = '\0';
    int funcionarioExiste = 0;
    for (int i = 0; i < totalFuncionarios; i++) {
        if (strcmp(funcionarios[i].cpf, novo.cpf_funcionario) == 0) {
            funcionarioExiste = 1;
            break;
        }
    }
    if (!funcionarioExiste) {
        printf("Funcionário com este CPF não encontrado!\n");
        return;
    }
    veiculos[totalVeiculos++] = novo;
    salvarVeiculos();
    printf("Veículo cadastrado com sucesso!\n");
}

void editarVeiculo() {}
void removerVeiculo() {}
void listarVeiculos() {
    printf("\n--- Lista de Veículos ---\n");
    if (totalVeiculos == 0) {
        printf("Nenhum veículo cadastrado.\n");
        return;
    }
    for (int i = 0; i < totalVeiculos; i++) {
        printf("%d) Placa: %s | Modelo: %s | Marca: %s | Ano: %d | Cor: %s | CPF Resp.: %s\n",
            i+1,
            veiculos[i].placa,
            veiculos[i].modelo,
            veiculos[i].marca,
            veiculos[i].ano,
            veiculos[i].cor,
            veiculos[i].cpf_funcionario);
    }
}
void buscarVeiculoPorPlaca() {
    char placa[10];
    printf("\n--- Buscar Veículo por Placa ---\n");
    printf("Informe a placa: ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0';
    for (int i = 0; i < totalVeiculos; i++) {
        if (strcmp(veiculos[i].placa, placa) == 0) {
            printf("Placa: %s\nModelo: %s\nMarca: %s\nAno: %d\nCor: %s\nCPF do Responsável: %s\n",
                veiculos[i].placa,
                veiculos[i].modelo,
                veiculos[i].marca,
                veiculos[i].ano,
                veiculos[i].cor,
                veiculos[i].cpf_funcionario);
            return;
        }
    }
    printf("Veículo com placa %s não encontrado.\n", placa);
}
void associarVeiculoFuncionario() {}
int buscaSequencialVeiculo(const char *placa) {
    for (int i = 0; i < totalVeiculos; i++) {
        if (strcmp(veiculos[i].placa, placa) == 0) {
            return i;
        }
    }
    return -1;
}
int buscaBinariaVeiculo(const char *placa) {
    int ini = 0, fim = totalVeiculos - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(veiculos[meio].placa, placa);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}
void ordenarVeiculosPorPlaca() {
    FILE *file = fopen("veiculos.dat", "rb");
    if (!file) {
        printf("Arquivo de veículos não encontrado!\n");
        return;
    }

    int total;
    fread(&total, sizeof(int), 1, file);
    fclose(file);

    FILE *original = fopen("veiculos.dat", "rb");
    FILE *ordenado = fopen("ordenado_veiculos.dat", "wb+");
    if (!original || !ordenado) {
        printf("Erro ao abrir arquivos!\n");
        return;
    }

    fread(&total, sizeof(int), 1, original);
    fwrite(&total, sizeof(int), 1, ordenado);

    int *usados = calloc(total, sizeof(int));

    for (int i = 0; i < total; i++) {
        Veiculo menor;
        long posMenor = -1;

        for (int j = 0; j < total; j++) {
            if (usados[j]) continue;

            Veiculo atual;
            fseek(original, sizeof(int) + j * sizeof(Veiculo), SEEK_SET);
            fread(&atual, sizeof(Veiculo), 1, original);

            if (posMenor == -1 || strcmp(atual.placa, menor.placa) < 0) {
                menor = atual;
                posMenor = j;
            }
        }

        fseek(ordenado, sizeof(int) + i * sizeof(Veiculo), SEEK_SET);
        fwrite(&menor, sizeof(Veiculo), 1, ordenado);
        usados[posMenor] = 1;
    }

    free(usados);
    fclose(original);
    fclose(ordenado);

    remove("veiculos.dat");
    rename("ordenado_veiculos.dat", "veiculos.dat");

    printf("Veículos ordenados por placa 100%% em disco!\n");
}

