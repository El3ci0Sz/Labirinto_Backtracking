#ifndef UNTITLED1_BACKTRACKING_H
#define UNTITLED1_BACKTRACKING_H
#include "Labirinto.h"

void backtracking_labirinto(Labirinto* labirinto);

//estrutura pilha
typedef struct Nodo {
    Posicao posicao;
    struct Nodo* proximo;
} Nodo;

typedef struct {
    Nodo* topo;
} Pilha;


//funcoes pilha
Pilha* criar_pilha();
void empilhar(Pilha* pilha, Posicao posicao);
Posicao desempilhar(Pilha* pilha);
int pilha_vazia(Pilha* pilha);
void liberar_pilha(Pilha* pilha);

#endif //UNTITLED1_BACKTRACKING_H
