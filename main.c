#include <stdio.h>
#include "funcionarios.h"
#include "veiculos.h"
#include "locacoes.h"

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
        printf("\n==== Sistema de Gestao de Veiculos ====" );
        printf("\n1. Gerenciar Funcionarios");
        printf("\n2. Gerenciar Veiculos");
        printf("\n3. Gerenciar Locacoes");
        printf("\n0. Sair\n");
        printf("Escolha uma opcao: ");
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
                printf("Opção invalida!\n");
        }
    } while(opcao != 0);
}

void menuFuncionarios() {
    int opcao;
    do {
        printf("\n--- Menu Funcionarios ---");
        printf("\n1. Adicionar Funcionario");
        printf("\n2. Remover Funcionario");
        printf("\n3. Listar Funcionarios");
        printf("\n4. Ordenar Funcionarios por CPF");
        printf("\n0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao) {
            case 1:
                adicionarFuncionario();
                break;
            case 2:
                removerFuncionario();
                break;
            case 3:
                listarFuncionarios();
                break;
            case 4:
                ordenarFuncionariosPorCPF();
                carregarFuncionarios();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

void menuVeiculos() {
    int opcao;
    do {
        printf("\n--- Menu Veiculos ---");
        printf("\n1. Adicionar Veiculo");
        printf("\n2. Remover Veiculo");
        printf("\n3. Listar Veiculos");
        printf("\n4. Buscar Veiculo por Placa");
        printf("\n5. Ordenar Veiculos por Placa");
        printf("\n0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao) {
            case 1:
                adicionarVeiculo();
                break;
            case 2:
                removerVeiculo();
                break;
            case 3:
                listarVeiculos();
                break;
            case 4:
                buscarVeiculoPorPlaca();
                break;
            case 5:
                ordenarVeiculosPorPlaca();
                carregarVeiculos();
                break;
            case 0:
                break;
            default:
                printf("Opção invalida!\n");
        }
    } while(opcao != 0);
}

void menuLocacoes() {
    int opcao;
    do {
        printf("\n--- Menu Locacoes ---");
        printf("\n1. Criar Locacao");
        printf("\n2. Finalizar Locacao");
        printf("\n4. Listar Todas as Locacoes");
        printf("\n5. Locacoes por Funcionario");
        printf("\n6. Locacoes por Veiculo");
        printf("\n8. Ordenar Locacoes por Data");
        printf("\n0. Voltar\n");
        printf("Escolha uma opcao: ");
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
                listarLocacoes();
                break;
            case 4:
                listarLocacoesPorFuncionario();
                break;
            case 5:
                listarLocacoesPorVeiculo();
                break;
            case 6:
                ordenarLocacoesPorData();
                carregarLocacoes();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}
