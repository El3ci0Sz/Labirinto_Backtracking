#include "../include/Labirinto.h"
#include "../include/Menu.h"
#include "../include/LabirintoTeste.h"
#include "../include/Backtracking.h"

#define ModoAnalise 0 //0 para desligado, 1 para ligado

void menu() {
    Labirinto* labirinto = NULL; // Ponteiro para armazenar o labirinto carregado
    Labirinto* solucao = NULL;
    int opcao;
    
    do {
        // Exibe o menu principal
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

                Labirinto * solucao = cria_labirinto_vazio(labirinto->linhas,labirinto->colunas);
                break;
            }
            case 2: {
                movimenta_estudante(labirinto, labirinto->posicao_inicial[0], labirinto->posicao_inicial[1], solucao);
                break;
            }
            case 3: {
                printf("Gerar labirinto de testes.\n");
                int linhas = 10, colunas = 10, num_portas = 5, num_chaves = 2, dificuldade = 70;

            // Gera o labirinto
                Labirinto* labirinto = gerar_labirinto_aleatorio(linhas, colunas, num_portas, num_chaves, dificuldade);

            // Imprime o labirinto gerado
                exibir_labirinto_visual(labirinto);

            // Libera a memória alocada
            liberar_labirinto(labirinto);
                break;
            }
            case 4: {
                printf("Saindo do programa.\n");
                break;
            }
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    // Libera memória antes de sair, se necessário
    if (labirinto != NULL) {
        liberar_labirinto(labirinto);
    }
}
