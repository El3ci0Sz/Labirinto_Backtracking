#include "../include/Labirinto.h"
#include "../include/Menu.h"
#include "../include/Backtracking.h"
#include "../include/LabirintoTeste.h"

void menu() {
    Labirinto* labirinto = NULL;
    int opcao;

    do {
        printf("-----------------------------------------------------------\n");
        printf("|  VOCE ESTÁ PRESO NO PRÉDIO DO SAPIENS, FUJA SE FOR CAPAZ!|\n");
        printf("|  1) Carregar novo arquivo de dados                       |\n");
        printf("|  2) Processar e exibir resposta                          |\n");
        printf("|  3) Gerar labirinto de teste                             |\n");
        printf("|  4) Sair do programa                                     |\n");
        printf("-----------------------------------------------------------\n");
        printf("Digite sua escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char nome_arquivo[100];
                printf("Digite o nome do arquivo: ");
                scanf("%s", nome_arquivo);

                if (labirinto != NULL) {
                    liberar_labirinto(labirinto);
                }

                labirinto = carregar_labirinto(nome_arquivo);
                if (labirinto != NULL) {
                    printf("Labirinto carregado com sucesso!\n");
                    exibir_labirinto_visual(labirinto);
                } else {
                    printf("Erro ao carregar o arquivo.\n");
                }
                break;
            }
            case 2: {
                if (labirinto != NULL) {
                    printf("Processando o labirinto...\n");
                    backtracking_labirinto(labirinto);
                } else {
                    printf("Nenhum labirinto carregado. Por favor, carregue ou gere um labirinto primeiro.\n");
                }
                break;
            }
            case 3: {
                if (labirinto != NULL) {
                    liberar_labirinto(labirinto);
                }

                labirinto = gerar_labirinto_aleatorio(10, 10, 5, 3, 80);
                if (labirinto != NULL) {
                    printf("Labirinto de teste gerado com sucesso!\n");
                    exibir_labirinto_visual(labirinto);
                } else {
                    printf("Erro ao gerar o labirinto de teste.\n");
                }
                break;
            }
            case 4:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    if (labirinto != NULL) {
        liberar_labirinto(labirinto);
    }
}
