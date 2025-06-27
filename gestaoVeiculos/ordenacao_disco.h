#ifndef ORDENACAO_DISCO_H
#define ORDENACAO_DISCO_H

#include "funcionarios.h"
#include "veiculos.h"
#include "locacoes.h"

// Ordenação em disco verdadeira - Merge Sort Externo
void mergeSortExternoFuncionarios();
void mergeSortExternoVeiculos();
void mergeSortExternoLocacoes();

// Funções auxiliares para Merge Sort Externo
void dividirArquivoFuncionarios(const char* arquivo_entrada, const char* arquivo_temp1, const char* arquivo_temp2, int tamanho_bloco);
void mergeBlocosFuncionarios(const char* arquivo_temp1, const char* arquivo_temp2, const char* arquivo_saida, int tamanho_bloco);
void ordenarBlocoFuncionarios(Funcionario* bloco, int tamanho);

void dividirArquivoVeiculos(const char* arquivo_entrada, const char* arquivo_temp1, const char* arquivo_temp2, int tamanho_bloco);
void mergeBlocosVeiculos(const char* arquivo_temp1, const char* arquivo_temp2, const char* arquivo_saida, int tamanho_bloco);
void ordenarBlocoVeiculos(Veiculo* bloco, int tamanho);

void dividirArquivoLocacoes(const char* arquivo_entrada, const char* arquivo_temp1, const char* arquivo_temp2, int tamanho_bloco);
void mergeBlocosLocacoes(const char* arquivo_temp1, const char* arquivo_temp2, const char* arquivo_saida, int tamanho_bloco);
void ordenarBlocoLocacoes(Locacao* bloco, int tamanho);

#endif // ORDENACAO_DISCO_H 