#include "../include/Labirinto.h"

//Definições dos movimentos que podem ser dados, para cima, para baixo, para esquerda, para direita
int dx[] = {0, 0, -1, +1};
int dy[] = {-1, +1, 0, 0};

int movimenta_estudante(Labirinto *labirinto, int x, int y, Labirinto *solucao){

    //Verifica se chegou ao final do labirinto (escapou)
    if(x == 0 && labirinto->matriz[x][y] == 1){
        printf("Escapou com sucesso");
        return 0;
    }

    solucao->matriz[x][y] = 0;  //Marca a celula como visitada e soma 1 na soma total de movimentos
    solucao->movimentos++;

    for(int i = 0; i < 4; i++){ //Itera para poder testar cada um dos 4 movimentos
        int nx = x + dx[i]; //nx = indice do eixo x + o valor para se movimentar para algum lugar
        int ny = y + dy[i];

        if (nx >= 0 && ny >= 0 && solucao->matriz[nx][ny] != 1 && nx < labirinto->linhas && ny < labirinto->colunas){
            if(labirinto->matriz[nx][ny] == 1 || labirinto->matriz[nx][ny] == 0){  //Verifica se a celula esta disponivel
                if (movimenta_estudante(labirinto,nx, ny, solucao)) return 1;    
            } 
            else if(labirinto->matriz[nx][ny] == 3 && labirinto->chaves > 0){
                 if(solucao->matriz[nx][ny] != 1){
                    labirinto->chaves--;
                    if (movimenta_estudante(labirinto,nx, ny, solucao)) return 1;
                }
                else{
                    labirinto->chaves ++;
                    if (movimenta_estudante(labirinto ,nx, ny, solucao)) return 1;
                }
            }
            else if(labirinto->matriz[nx][ny] == 4){
                if(solucao->matriz[nx][ny] != 1){
                    labirinto->chaves++;
                }
                else{
                    labirinto->chaves --;
                }
            }

        }
}
    solucao->matriz[x][y] = 0;
    return 1; //Retrocede caso os movimentos nao possam ser dados

}

// int verifica_se_seguro(Labirinto Labirinto, int x, int y){
//     if
// }