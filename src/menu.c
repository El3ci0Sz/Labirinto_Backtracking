//
// Created by rangi on 20/11/2024.
//
#include "../include/Labirinto.h"
#include "../include/Menu.h"
#include "../include/Backtracking.h"

void menu() {
    Labirinto* labirinto = NULL; // Ponteiro para armazenar o labirinto carregado
    int opcao;
    
    do {
        // Exibe o menu principal
        printf("\nVOCE ESTÁ PRESO NO PRÉDIO DO SAPIENS, FUJA SE FOR CAPAZ!\n");
        printf("1) Carregar novo arquivo de dados\n");
        printf("2) Processar e exibir resposta\n");
        printf("3) Sair do programa\n");
        printf("Digite sua escolha: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char nome_arquivo[100];
                printf("Digite o nome do arquivo: ");
                scanf("%s", nome_arquivo);

                // Libera o labirinto anterior se já existir
                if (labirinto != NULL) {
                    liberar_labirinto(labirinto);
                }

                // Carrega o novo labirinto
                labirinto = carregar_labirinto(nome_arquivo);
                if (labirinto != NULL) {
                    printf("Labirinto carregado com sucesso!\n");
                } else {    
                    printf("Erro ao carregar o arquivo.\n");
                }
                break;
            }
            case 2:
            //resolve por backtracking usando pilha
                backtracking_labirinto(labirinto);
                break;
            case 3:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 3);

    // Libera memória antes de sair, se necessário
    if (labirinto != NULL) {
        liberar_labirinto(labirinto);
    }
}