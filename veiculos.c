#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veiculos.h"
#include "funcionarios.h"

void adicionarVeiculo() {
    Veiculo novo;
    printf("\n--- cadastro de veiculo ---\n");
    printf("placa: ");
    fgets(novo.placa, sizeof(novo.placa), stdin);
    novo.placa[strcspn(novo.placa, "\n")] = '\0';

    FILE *file = fopen("veiculos.dat", "rb");
    if (file) {
        Veiculo temp;
        while (fread(&temp, sizeof(Veiculo), 1, file)) {
            if (strcmp(temp.placa, novo.placa) == 0) {
                printf("já existe um veiculo com essa placa :/\n");
                fclose(file);
                return;
            }
        }
        fclose(file);
    }

    printf("modelo: ");
    fgets(novo.modelo, sizeof(novo.modelo), stdin);
    novo.modelo[strcspn(novo.modelo, "\n")] = '\0';
    printf("marca: ");
    fgets(novo.marca, sizeof(novo.marca), stdin);
    novo.marca[strcspn(novo.marca, "\n")] = '\0';
    printf("ano: ");
    scanf("%d", &novo.ano);
    getchar();
    printf("cor: ");
    fgets(novo.cor, sizeof(novo.cor), stdin);
    novo.cor[strcspn(novo.cor, "\n")] = '\0';
    printf("cpf do funcionario responsavel: ");
    fgets(novo.cpf_funcionario, sizeof(novo.cpf_funcionario), stdin);
    novo.cpf_funcionario[strcspn(novo.cpf_funcionario, "\n")] = '\0';

    FILE *fFunc = fopen("funcionarios.dat", "rb");
    int funcionarioExiste = 0;
    if (fFunc) {
        Funcionario f;
        while (fread(&f, sizeof(Funcionario), 1, fFunc)) {
            if (strcmp(f.cpf, novo.cpf_funcionario) == 0) {
                funcionarioExiste = 1;
                break;
            }
        }
        fclose(fFunc);
    }
    if (!funcionarioExiste) {
        printf("funcionário com esse cpf não achado!\n");
        return;
    }

    file = fopen("veiculos.dat", "ab");
    if (!file) {
        printf("erro ao salvar veiculo :(\n");
        return;
    }
    fwrite(&novo, sizeof(Veiculo), 1, file);
    fclose(file);
    printf("veiculo salvo, ufa\n");
}

void listarVeiculos() {
    printf("\n--- lista de veiculos ---\n");
    FILE *file = fopen("veiculos.dat", "rb");
    if (!file) {
        printf("ninguém por aqui ainda.\n");
        return;
    }

    Veiculo v;
    int i = 1;
    while (fread(&v, sizeof(Veiculo), 1, file)) {
        printf("%d) placa: %s | modelo: %s | marca: %s | ano: %d | cor: %s | cpf resp.: %s\n",
               i++, v.placa, v.modelo, v.marca, v.ano, v.cor, v.cpf_funcionario);
    }
    fclose(file);
}

void buscarVeiculoPorPlaca() {
    char placa[10];
    printf("\n--- busca por placa ---\n");
    printf("qual placa vc quer? ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0';

    FILE *file = fopen("veiculos.dat", "rb");
    if (!file) {
        printf("nao achei o arquivo :c\n");
        return;
    }

    Veiculo v;
    int encontrado = 0;
    while (fread(&v, sizeof(Veiculo), 1, file)) {
        if (strcmp(v.placa, placa) == 0) {
            printf("placa: %s\nmodelo: %s\nmarca: %s\nano: %d\ncor: %s\ncpf do responsavel: %s\n",
                   v.placa, v.modelo, v.marca, v.ano, v.cor, v.cpf_funcionario);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("placa %s nao foi encontrada em lugar nenhum kkk\n", placa);
    }
    fclose(file);
}

void removerVeiculo() {
    char placa[10];
    printf("\n--- remover veiculo ---\n");
    printf("digita a placa q quer tirar: ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0';

    FILE *original = fopen("veiculos.dat", "rb");
    FILE *temp = fopen("temp_veiculos.dat", "wb");
    if (!original || !temp) {
        printf("erro abrindo os arquivos :(");
        return;
    }

    Veiculo v;
    int removido = 0;
    while (fread(&v, sizeof(Veiculo), 1, original)) {
        if (strcmp(v.placa, placa) == 0) {
            removido = 1;
            continue;
        }
        fwrite(&v, sizeof(Veiculo), 1, temp);
    }
    fclose(original);
    fclose(temp);

    if (removido) {
        remove("veiculos.dat");
        rename("temp_veiculos.dat", "veiculos.dat");
        printf("foi com deus o veiculo\n");
    } else {
        remove("temp_veiculos.dat");
        printf("placa %s nao apareceu aqui nao viu\n", placa);
    }
}

void editarVeiculo() {
    char placa[10];
    printf("\n--- editar veiculo ---\n");
    printf("placa do bicho q vc quer mudar: ");
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0';

    FILE *original = fopen("veiculos.dat", "rb");
    FILE *temp = fopen("temp_veiculos.dat", "wb");
    if (!original || !temp) {
        printf("deu ruim abrindo os arquivos\n");
        return;
    }

    Veiculo v;
    int encontrado = 0;
    while (fread(&v, sizeof(Veiculo), 1, original)) {
        if (strcmp(v.placa, placa) == 0) {
            encontrado = 1;
            printf("modelo: ");
            fgets(v.modelo, sizeof(v.modelo), stdin);
            v.modelo[strcspn(v.modelo, "\n")] = '\0';
            printf("marca: ");
            fgets(v.marca, sizeof(v.marca), stdin);
            v.marca[strcspn(v.marca, "\n")] = '\0';
            printf("ano: ");
            scanf("%d", &v.ano);
            getchar();
            printf("cor: ");
            fgets(v.cor, sizeof(v.cor), stdin);
            v.cor[strcspn(v.cor, "\n")] = '\0';
            printf("cpf do responsavel: ");
            fgets(v.cpf_funcionario, sizeof(v.cpf_funcionario), stdin);
            v.cpf_funcionario[strcspn(v.cpf_funcionario, "\n")] = '\0';
        }
        fwrite(&v, sizeof(Veiculo), 1, temp);
    }
    fclose(original);
    fclose(temp);

    if (encontrado) {
        remove("veiculos.dat");
        rename("temp_veiculos.dat", "veiculos.dat");
        printf("mudou tudo, prontinho\n");
    } else {
        remove("temp_veiculos.dat");
        printf("placa %s nao encontrada...\n", placa);
    }
}

void ordenarVeiculosPorPlaca() {
    FILE *file = fopen("veiculos.dat", "rb");
    if (!file) {
        printf("arquivo de veiculos sumiu!\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long tamanho = ftell(file);
    int total = tamanho / sizeof(Veiculo);
    fclose(file);

    FILE *original = fopen("veiculos.dat", "rb");
    FILE *ordenado = fopen("ordenado_veiculos.dat", "wb+");
    int *usados = calloc(total, sizeof(int));

    for (int i = 0; i < total; i++) {
        Veiculo menor;
        long posMenor = -1;

        for (int j = 0; j < total; j++) {
            if (usados[j]) continue;

            Veiculo atual;
            fseek(original, j * sizeof(Veiculo), SEEK_SET);
            fread(&atual, sizeof(Veiculo), 1, original);

            if (posMenor == -1 || strcmp(atual.placa, menor.placa) < 0) {
                menor = atual;
                posMenor = j;
            }
        }
        usados[posMenor] = 1;
        fseek(ordenado, i * sizeof(Veiculo), SEEK_SET);
        fwrite(&menor, sizeof(Veiculo), 1, ordenado);
    }

    free(usados);
    fclose(original);
    fclose(ordenado);
    remove("veiculos.dat");
    rename("ordenado_veiculos.dat", "veiculos.dat");
    printf("ordenei tudo por placa (foi um trampo)\n");
}
