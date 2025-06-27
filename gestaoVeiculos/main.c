#include <stdio.h>
#include "funcionarios.h"
#include "veiculos.h"
#include "locacoes.h"
#include "ordenacao_disco.h"

void menuPrincipal();
void menuFuncionarios();
void menuVeiculos();
void menuLocacoes();

int main() {
    carregarFuncionarios();
    carregarVeiculos();
    carregarLocacoes();
    menuPrincipal();
    salvarFuncionarios();
    salvarVeiculos();
    salvarLocacoes();
    return 0;
}

void menuPrincipal() {
    int opcao;
    do {
        printf("\n==== Sistema de Gestão de Veículos ====" );
        printf("\n1. Gerenciar Funcionários");
        printf("\n2. Gerenciar Veículos");
        printf("\n3. Gerenciar Locações");
        printf("\n0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao) {
            case 1:
                menuFuncionarios();
                break;
            case 2:
                menuVeiculos();
                break;
            case 3:
                menuLocacoes();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);
}

void menuFuncionarios() {
    int opcao;
    do {
        printf("\n--- Menu Funcionários ---");
        printf("\n1. Adicionar Funcionário");
        printf("\n2. Editar Funcionário");
        printf("\n3. Remover Funcionário");
        printf("\n4. Listar Funcionários");
        printf("\n5. Ordenar Funcionários por CPF (Disco)");
        printf("\n0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao) {
            case 1:
                adicionarFuncionario();
                break;
            case 2:
                editarFuncionario();
                break;
            case 3:
                removerFuncionario();
                break;
            case 4:
                listarFuncionarios();
                break;
            case 5:
                mergeSortExternoFuncionarios();
                carregarFuncionarios();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);
}

void menuVeiculos() {
    int opcao;
    do {
        printf("\n--- Menu Veículos ---");
        printf("\n1. Adicionar Veículo");
        printf("\n2. Editar Veículo");
        printf("\n3. Remover Veículo");
        printf("\n4. Listar Veículos");
        printf("\n5. Buscar Veículo por Placa");
        printf("\n6. Ordenar Veículos por Placa (Disco)");
        printf("\n0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao) {
            case 1:
                adicionarVeiculo();
                break;
            case 2:
                editarVeiculo();
                break;
            case 3:
                removerVeiculo();
                break;
            case 4:
                listarVeiculos();
                break;
            case 5:
                buscarVeiculoPorPlaca();
                break;
            case 6:
                mergeSortExternoVeiculos();
                carregarVeiculos();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);
}

void menuLocacoes() {
    int opcao;
    do {
        printf("\n--- Menu Locações ---");
        printf("\n1. Criar Locação");
        printf("\n2. Finalizar Locação");
        printf("\n3. Cancelar Locação");
        printf("\n4. Listar Todas as Locações");
        printf("\n5. Locações por Funcionário");
        printf("\n6. Locações por Veículo");
        printf("\n7. Locações Ativas");
        printf("\n8. Ordenar Locações por Data (Disco)");
        printf("\n0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao) {
            case 1:
                criarLocacao();
                break;
            case 2:
                finalizarLocacao();
                break;
            case 3:
                cancelarLocacao();
                break;
            case 4:
                listarLocacoes();
                break;
            case 5:
                listarLocacoesPorFuncionario();
                break;
            case 6:
                listarLocacoesPorVeiculo();
                break;
            case 7:
                listarLocacoesAtivas();
                break;
            case 8:
                mergeSortExternoLocacoes();
                carregarLocacoes();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);
} 