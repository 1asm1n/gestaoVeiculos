#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordenacao_disco.h"

#define TAMANHO_BLOCO 10  // Número de registros por bloco

// Ordenação em disco verdadeira para Funcionários
void mergeSortExternoFuncionarios() {
    printf("Iniciando ordenação em disco para funcionários...\n");
    
    // Arquivos temporários
    const char* temp1 = "temp_func1.dat";
    const char* temp2 = "temp_func2.dat";
    const char* temp3 = "temp_func3.dat";
    const char* temp4 = "temp_func4.dat";
    
    // Primeira passada: dividir em blocos ordenados
    dividirArquivoFuncionarios("funcionarios.dat", temp1, temp2, TAMANHO_BLOCO);
    
    // Passadas subsequentes: merge dos blocos
    int tamanho_bloco = TAMANHO_BLOCO;
    int total_registros = totalFuncionarios;
    
    while (tamanho_bloco < total_registros) {
        mergeBlocosFuncionarios(temp1, temp2, temp3, tamanho_bloco);
        mergeBlocosFuncionarios(temp3, temp4, temp1, tamanho_bloco * 2);
        tamanho_bloco *= 4;
    }
    
    // Copiar resultado final
    FILE *origem = fopen(temp1, "rb");
    FILE *destino = fopen("funcionarios.dat", "wb");
    if (origem && destino) {
        fwrite(&totalFuncionarios, sizeof(int), 1, destino);
        Funcionario func;
        while (fread(&func, sizeof(Funcionario), 1, origem) == 1) {
            fwrite(&func, sizeof(Funcionario), 1, destino);
        }
        fclose(origem);
        fclose(destino);
    }
    
    // Limpar arquivos temporários
    remove(temp1);
    remove(temp2);
    remove(temp3);
    remove(temp4);
    
    printf("Funcionários ordenados em disco por CPF!\n");
}

void dividirArquivoFuncionarios(const char* arquivo_entrada, const char* arquivo_temp1, const char* arquivo_temp2, int tamanho_bloco) {
    FILE *entrada = fopen(arquivo_entrada, "rb");
    FILE *temp1 = fopen(arquivo_temp1, "wb");
    FILE *temp2 = fopen(arquivo_temp2, "wb");
    
    if (!entrada || !temp1 || !temp2) {
        printf("Erro ao abrir arquivos para divisão!\n");
        return;
    }
    
    int n;
    fread(&n, sizeof(int), 1, entrada);
    
    Funcionario *bloco = malloc(tamanho_bloco * sizeof(Funcionario));
    int alternar = 0;
    int registros_lidos = 0;
    
    while (registros_lidos < n) {
        int registros_no_bloco = 0;
        
        // Ler bloco
        while (registros_no_bloco < tamanho_bloco && registros_lidos < n) {
            if (fread(&bloco[registros_no_bloco], sizeof(Funcionario), 1, entrada) == 1) {
                registros_no_bloco++;
                registros_lidos++;
            } else {
                break;
            }
        }
        
        // Ordenar bloco
        ordenarBlocoFuncionarios(bloco, registros_no_bloco);
        
        // Escrever em arquivo alternado
        FILE *destino = alternar ? temp1 : temp2;
        for (int i = 0; i < registros_no_bloco; i++) {
            fwrite(&bloco[i], sizeof(Funcionario), 1, destino);
        }
        
        alternar = !alternar;
    }
    
    free(bloco);
    fclose(entrada);
    fclose(temp1);
    fclose(temp2);
}

void mergeBlocosFuncionarios(const char* arquivo_temp1, const char* arquivo_temp2, const char* arquivo_saida, int tamanho_bloco) {
    FILE *temp1 = fopen(arquivo_temp1, "rb");
    FILE *temp2 = fopen(arquivo_temp2, "rb");
    FILE *saida = fopen(arquivo_saida, "wb");
    
    if (!temp1 || !temp2 || !saida) {
        printf("Erro ao abrir arquivos para merge!\n");
        return;
    }
    
    Funcionario *bloco1 = malloc(tamanho_bloco * sizeof(Funcionario));
    Funcionario *bloco2 = malloc(tamanho_bloco * sizeof(Funcionario));
    
    int i1 = 0, i2 = 0;
    int registros1 = 0, registros2 = 0;
    
    while (1) {
        // Recarregar blocos se necessário
        if (i1 >= registros1) {
            registros1 = fread(bloco1, sizeof(Funcionario), tamanho_bloco, temp1);
            i1 = 0;
        }
        if (i2 >= registros2) {
            registros2 = fread(bloco2, sizeof(Funcionario), tamanho_bloco, temp2);
            i2 = 0;
        }
        
        // Se ambos os blocos estão vazios, terminar
        if (registros1 == 0 && registros2 == 0) break;
        
        // Merge dos blocos
        while (i1 < registros1 && i2 < registros2) {
            if (strcmp(bloco1[i1].cpf, bloco2[i2].cpf) <= 0) {
                fwrite(&bloco1[i1], sizeof(Funcionario), 1, saida);
                i1++;
            } else {
                fwrite(&bloco2[i2], sizeof(Funcionario), 1, saida);
                i2++;
            }
        }
        
        // Escrever registros restantes
        while (i1 < registros1) {
            fwrite(&bloco1[i1], sizeof(Funcionario), 1, saida);
            i1++;
        }
        while (i2 < registros2) {
            fwrite(&bloco2[i2], sizeof(Funcionario), 1, saida);
            i2++;
        }
    }
    
    free(bloco1);
    free(bloco2);
    fclose(temp1);
    fclose(temp2);
    fclose(saida);
}

void ordenarBlocoFuncionarios(Funcionario* bloco, int tamanho) {
    // Bubble Sort para o bloco em memória
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (strcmp(bloco[j].cpf, bloco[j+1].cpf) > 0) {
                Funcionario temp = bloco[j];
                bloco[j] = bloco[j+1];
                bloco[j+1] = temp;
            }
        }
    }
}

// Ordenação em disco verdadeira para Veículos
void mergeSortExternoVeiculos() {
    printf("Iniciando ordenação em disco para veículos...\n");
    
    const char* temp1 = "temp_veic1.dat";
    const char* temp2 = "temp_veic2.dat";
    const char* temp3 = "temp_veic3.dat";
    const char* temp4 = "temp_veic4.dat";
    
    dividirArquivoVeiculos("veiculos.dat", temp1, temp2, TAMANHO_BLOCO);
    
    int tamanho_bloco = TAMANHO_BLOCO;
    int total_registros = totalVeiculos;
    
    while (tamanho_bloco < total_registros) {
        mergeBlocosVeiculos(temp1, temp2, temp3, tamanho_bloco);
        mergeBlocosVeiculos(temp3, temp4, temp1, tamanho_bloco * 2);
        tamanho_bloco *= 4;
    }
    
    FILE *origem = fopen(temp1, "rb");
    FILE *destino = fopen("veiculos.dat", "wb");
    if (origem && destino) {
        fwrite(&totalVeiculos, sizeof(int), 1, destino);
        Veiculo veic;
        while (fread(&veic, sizeof(Veiculo), 1, origem) == 1) {
            fwrite(&veic, sizeof(Veiculo), 1, destino);
        }
        fclose(origem);
        fclose(destino);
    }
    
    remove(temp1);
    remove(temp2);
    remove(temp3);
    remove(temp4);
    
    printf("Veículos ordenados em disco por placa!\n");
}

void dividirArquivoVeiculos(const char* arquivo_entrada, const char* arquivo_temp1, const char* arquivo_temp2, int tamanho_bloco) {
    FILE *entrada = fopen(arquivo_entrada, "rb");
    FILE *temp1 = fopen(arquivo_temp1, "wb");
    FILE *temp2 = fopen(arquivo_temp2, "wb");
    
    if (!entrada || !temp1 || !temp2) return;
    
    int n;
    fread(&n, sizeof(int), 1, entrada);
    
    Veiculo *bloco = malloc(tamanho_bloco * sizeof(Veiculo));
    int alternar = 0;
    int registros_lidos = 0;
    
    while (registros_lidos < n) {
        int registros_no_bloco = 0;
        
        while (registros_no_bloco < tamanho_bloco && registros_lidos < n) {
            if (fread(&bloco[registros_no_bloco], sizeof(Veiculo), 1, entrada) == 1) {
                registros_no_bloco++;
                registros_lidos++;
            } else {
                break;
            }
        }
        
        ordenarBlocoVeiculos(bloco, registros_no_bloco);
        
        FILE *destino = alternar ? temp1 : temp2;
        for (int i = 0; i < registros_no_bloco; i++) {
            fwrite(&bloco[i], sizeof(Veiculo), 1, destino);
        }
        
        alternar = !alternar;
    }
    
    free(bloco);
    fclose(entrada);
    fclose(temp1);
    fclose(temp2);
}

void mergeBlocosVeiculos(const char* arquivo_temp1, const char* arquivo_temp2, const char* arquivo_saida, int tamanho_bloco) {
    FILE *temp1 = fopen(arquivo_temp1, "rb");
    FILE *temp2 = fopen(arquivo_temp2, "rb");
    FILE *saida = fopen(arquivo_saida, "wb");
    
    if (!temp1 || !temp2 || !saida) return;
    
    Veiculo *bloco1 = malloc(tamanho_bloco * sizeof(Veiculo));
    Veiculo *bloco2 = malloc(tamanho_bloco * sizeof(Veiculo));
    
    int i1 = 0, i2 = 0;
    int registros1 = 0, registros2 = 0;
    
    while (1) {
        if (i1 >= registros1) {
            registros1 = fread(bloco1, sizeof(Veiculo), tamanho_bloco, temp1);
            i1 = 0;
        }
        if (i2 >= registros2) {
            registros2 = fread(bloco2, sizeof(Veiculo), tamanho_bloco, temp2);
            i2 = 0;
        }
        
        if (registros1 == 0 && registros2 == 0) break;
        
        while (i1 < registros1 && i2 < registros2) {
            if (strcmp(bloco1[i1].placa, bloco2[i2].placa) <= 0) {
                fwrite(&bloco1[i1], sizeof(Veiculo), 1, saida);
                i1++;
            } else {
                fwrite(&bloco2[i2], sizeof(Veiculo), 1, saida);
                i2++;
            }
        }
        
        while (i1 < registros1) {
            fwrite(&bloco1[i1], sizeof(Veiculo), 1, saida);
            i1++;
        }
        while (i2 < registros2) {
            fwrite(&bloco2[i2], sizeof(Veiculo), 1, saida);
            i2++;
        }
    }
    
    free(bloco1);
    free(bloco2);
    fclose(temp1);
    fclose(temp2);
    fclose(saida);
}

void ordenarBlocoVeiculos(Veiculo* bloco, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (strcmp(bloco[j].placa, bloco[j+1].placa) > 0) {
                Veiculo temp = bloco[j];
                bloco[j] = bloco[j+1];
                bloco[j+1] = temp;
            }
        }
    }
}

// Ordenação em disco verdadeira para Locações
void mergeSortExternoLocacoes() {
    printf("Iniciando ordenação em disco para locações...\n");
    
    const char* temp1 = "temp_loc1.dat";
    const char* temp2 = "temp_loc2.dat";
    const char* temp3 = "temp_loc3.dat";
    const char* temp4 = "temp_loc4.dat";
    
    dividirArquivoLocacoes("locacoes.dat", temp1, temp2, TAMANHO_BLOCO);
    
    int tamanho_bloco = TAMANHO_BLOCO;
    int total_registros = totalLocacoes;
    
    while (tamanho_bloco < total_registros) {
        mergeBlocosLocacoes(temp1, temp2, temp3, tamanho_bloco);
        mergeBlocosLocacoes(temp3, temp4, temp1, tamanho_bloco * 2);
        tamanho_bloco *= 4;
    }
    
    FILE *origem = fopen(temp1, "rb");
    FILE *destino = fopen("locacoes.dat", "wb");
    if (origem && destino) {
        fwrite(&totalLocacoes, sizeof(int), 1, destino);
        Locacao loc;
        while (fread(&loc, sizeof(Locacao), 1, origem) == 1) {
            fwrite(&loc, sizeof(Locacao), 1, destino);
        }
        fclose(origem);
        fclose(destino);
    }
    
    remove(temp1);
    remove(temp2);
    remove(temp3);
    remove(temp4);
    
    printf("Locações ordenadas em disco por data!\n");
}

void dividirArquivoLocacoes(const char* arquivo_entrada, const char* arquivo_temp1, const char* arquivo_temp2, int tamanho_bloco) {
    FILE *entrada = fopen(arquivo_entrada, "rb");
    FILE *temp1 = fopen(arquivo_temp1, "wb");
    FILE *temp2 = fopen(arquivo_temp2, "wb");
    
    if (!entrada || !temp1 || !temp2) return;
    
    int n;
    fread(&n, sizeof(int), 1, entrada);
    
    Locacao *bloco = malloc(tamanho_bloco * sizeof(Locacao));
    int alternar = 0;
    int registros_lidos = 0;
    
    while (registros_lidos < n) {
        int registros_no_bloco = 0;
        
        while (registros_no_bloco < tamanho_bloco && registros_lidos < n) {
            if (fread(&bloco[registros_no_bloco], sizeof(Locacao), 1, entrada) == 1) {
                registros_no_bloco++;
                registros_lidos++;
            } else {
                break;
            }
        }
        
        ordenarBlocoLocacoes(bloco, registros_no_bloco);
        
        FILE *destino = alternar ? temp1 : temp2;
        for (int i = 0; i < registros_no_bloco; i++) {
            fwrite(&bloco[i], sizeof(Locacao), 1, destino);
        }
        
        alternar = !alternar;
    }
    
    free(bloco);
    fclose(entrada);
    fclose(temp1);
    fclose(temp2);
}

void mergeBlocosLocacoes(const char* arquivo_temp1, const char* arquivo_temp2, const char* arquivo_saida, int tamanho_bloco) {
    FILE *temp1 = fopen(arquivo_temp1, "rb");
    FILE *temp2 = fopen(arquivo_temp2, "rb");
    FILE *saida = fopen(arquivo_saida, "wb");
    
    if (!temp1 || !temp2 || !saida) return;
    
    Locacao *bloco1 = malloc(tamanho_bloco * sizeof(Locacao));
    Locacao *bloco2 = malloc(tamanho_bloco * sizeof(Locacao));
    
    int i1 = 0, i2 = 0;
    int registros1 = 0, registros2 = 0;
    
    while (1) {
        if (i1 >= registros1) {
            registros1 = fread(bloco1, sizeof(Locacao), tamanho_bloco, temp1);
            i1 = 0;
        }
        if (i2 >= registros2) {
            registros2 = fread(bloco2, sizeof(Locacao), tamanho_bloco, temp2);
            i2 = 0;
        }
        
        if (registros1 == 0 && registros2 == 0) break;
        
        while (i1 < registros1 && i2 < registros2) {
            if (strcmp(bloco1[i1].data_inicio, bloco2[i2].data_inicio) <= 0) {
                fwrite(&bloco1[i1], sizeof(Locacao), 1, saida);
                i1++;
            } else {
                fwrite(&bloco2[i2], sizeof(Locacao), 1, saida);
                i2++;
            }
        }
        
        while (i1 < registros1) {
            fwrite(&bloco1[i1], sizeof(Locacao), 1, saida);
            i1++;
        }
        while (i2 < registros2) {
            fwrite(&bloco2[i2], sizeof(Locacao), 1, saida);
            i2++;
        }
    }
    
    free(bloco1);
    free(bloco2);
    fclose(temp1);
    fclose(temp2);
    fclose(saida);
}

void ordenarBlocoLocacoes(Locacao* bloco, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (strcmp(bloco[j].data_inicio, bloco[j+1].data_inicio) > 0) {
                Locacao temp = bloco[j];
                bloco[j] = bloco[j+1];
                bloco[j+1] = temp;
            }
        }
    }
} 