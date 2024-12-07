#ifndef UNTITLED1_BACKTRACKING_H
#define UNTITLED1_BACKTRACKING_H

#include "Labirinto.h"

// Funções principais
void resolverLabirinto(Labirinto* labirinto);
bool buscarCaminhoBT(Labirinto* labirinto, int linha, int coluna, int* movimentos_totais);

// Estrutura da Pilha
typedef struct Nodo {
    Posicao posicao;
    struct Nodo* proximo;
} Nodo;

typedef struct {
    Nodo* topo;
} Pilha;

Pilha* criarPilha();
void empilhar(Pilha* pilha, Posicao posicao);
Posicao desempilhar(Pilha* pilha);
int pilhaVazia(Pilha* pilha);
void liberarPilha(Pilha* pilha);


#endif // UNTITLED1_BACKTRACKING_H
