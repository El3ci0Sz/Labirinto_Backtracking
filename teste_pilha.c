#include "include/Labirinto.h"
#include <assert.h>
#include <stdio.h>

void testar_pilha() {
    Pilha* pilha = criar_pilha();
    assert(pilha != NULL);

    Posicao p1 = {1, 2};
    Posicao p2 = {3, 4};
    Posicao p3 = {5, 6};

    // Testa empilhar
    empilhar(pilha, p1);
    empilhar(pilha, p2);
    empilhar(pilha, p3);

    // Verifica desempilhamento
    Posicao desempilhado = desempilhar(pilha);
    assert(desempilhado.linha == 5 && desempilhado.coluna == 6);

    desempilhado = desempilhar(pilha);
    assert(desempilhado.linha == 3 && desempilhado.coluna == 4);

    desempilhado = desempilhar(pilha);
    assert(desempilhado.linha == 1 && desempilhado.coluna == 2);

    // Verifica pilha vazia
    assert(pilha_vazia(pilha));

    liberar_pilha(pilha);
    printf("Testes da pilha passaram com sucesso!\n");
}

int main() {
    testar_pilha();
    return 0;
}
