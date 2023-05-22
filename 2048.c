#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMBER2 1
#define NUMBER4 2
#define NUMBER8 3
#define NUMBER16 4
#define NUMBER32 5
#define NUMBER64 6
#define NUMBER128 7
#define NUMBER256 8 
#define NUMBER512 9
#define NUMBER1024 10
#define NUMBER2048 11
#define BACKGROUND 12

#define BOARDSIZE 16 /*numero de posições possíveis dentro do tabuleiro*/
#define SIZE 4 /*define apenas o tamanho da matriz,

Tanto as linhas como as colunas são numeradas de 0 a 3*/

void printboard(int board[SIZE][SIZE]){ 
    int i, j;
    clear();
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            if (board[i][j] == 0 ){
                attron(COLOR_PAIR(BACKGROUND));
                printw("      ");
                attroff(COLOR_PAIR(BACKGROUND));
            }
            else{
                if (board[i][j] == 2){
                    attron(COLOR_PAIR(NUMBER2));
                    printw(" %4d ", board[i][j]);
                    attroff(COLOR_PAIR(NUMBER2));
                }
                else if (board[i][j] == 4){
                    attron(COLOR_PAIR(NUMBER4));
                    printw(" %4d ", board[i][j]);
                    attroff(COLOR_PAIR(NUMBER4));
                }
                else if (board[i][j] == 8){
                    attron(COLOR_PAIR(NUMBER8));
                    printw(" %4d ", board[i][j]);
                    attroff(COLOR_PAIR(NUMBER8));
                }
                else if (board[i][j] == 16){
                    attron(COLOR_PAIR(NUMBER16));
                    printw(" %4d ", board[i][j]);
                    attroff(COLOR_PAIR(NUMBER16));
                }
                else if (board[i][j] == 32){
                    attron(COLOR_PAIR(NUMBER32));
                    printw(" %4d ", board[i][j]);
                    attroff(COLOR_PAIR(NUMBER32));
                }
                else if (board[i][j] == 64){
                    attron(COLOR_PAIR(NUMBER64));
                    printw(" %4d ", board[i][j]);
                    attroff(COLOR_PAIR(NUMBER64));
                }
                else if (board[i][j] == 128){
                    attron(COLOR_PAIR(NUMBER128));
                    printw(" %4d ", board[i][j]);
                    attroff(COLOR_PAIR(NUMBER128));
                }
                else if (board[i][j] == 256){
                    attron(COLOR_PAIR(NUMBER256));
                    printw(" %4d ", board[i][j]);
                    attroff(COLOR_PAIR(NUMBER256));
                }
                else if (board[i][j] == 512){
                    attron(COLOR_PAIR(NUMBER512));
                    printw(" %4d ", board[i][j]);
                    attroff(COLOR_PAIR(NUMBER512));
                }
                else if (board[i][j] == 1024){
                    attron(COLOR_PAIR(NUMBER1024));
                    printw(" %4d ", board[i][j]);
                    attroff(COLOR_PAIR(NUMBER1024));
                }
                else if (board[i][j] == 2048){
                    attron(COLOR_PAIR(NUMBER2048));
                    printw(" %4d ", board[i][j]);
                    attroff(COLOR_PAIR(NUMBER2048));
                }
            }
        }
        printw("\n");
    }
}

/*randomizando as posições em que o 2 ou o 4 irão aparecer
retorna true se foi gerado*/
int randomize(int board[SIZE][SIZE]){
    int i, j, temp, 
        irand = rand()%SIZE, 
        jrand = rand()%SIZE, 
        v2ou4[2] = {2, 4}, 
        randomicnumber = rand()%2;

    /* garantir que vai sortear um */
    for (i=0; i<SIZE; i++){
        for (j=0; j<SIZE; j++){
            if (board[irand][jrand] == 0){
                temp = v2ou4[randomicnumber];
                board[irand][jrand] = temp;
                return(true);
            }else{
                jrand = rand()%SIZE;
                irand = rand()%SIZE;
                randomicnumber = rand() %2;
            }
        }
    }
    return(false);
}

/*cria o quadro do jogo com todos os valores 0 
e gera o primeiro numero 2 em posição aleatória*/
void setupgame (int board[SIZE][SIZE]){ 
    int i, j, irandom = rand()%SIZE, jrandom = rand()%SIZE;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            board[i][j] = 0;
    
    board[irandom][jrandom] = 2;
}

/*faz a movimentacao para cima
retorna true se o movimento foi feito*/
int moveup (int board[SIZE][SIZE]){
    int position, i, j, moved = false;
    for (j=0; j<SIZE; j++){
        position = 0;
        for (i=0; i<SIZE; i++){
            if (board[i][j] != 0){
                board[position][j] = board[i][j];
                position++;
                moved = true;
            }
        }
        for(i=position; i < SIZE; i++) 
            board[i][j] = 0;
    }
    /* Agrupamento */
    for (j = 0; j < SIZE ; j++) {
        position = 0;
        for (i = 0; i < SIZE ; i++) {
            if (board[i][j] == board[i + 1][j]) {
                board[position][j] = 2 * board[i][j];
                i++;
                moved = true;
            }
            else {
                board[position][j] =  board[i][j];
            }
            position++;
        }
        for (i = position; i < SIZE ; i++)
            board[i][j] = 0;
    }
    return (moved);
}

/*faz a movimentacao para baixo
retorna true se o movimento foi feito*/
int movedown (int board[SIZE][SIZE]){
    int position, i, j, moved = false;
    for (j=0; j<SIZE; j++){
        position = 3;
        for (i=3; i >= 0; i--){
            if (board[i][j] != 0){
                board[position][j] = board[i][j];
                position--;
                moved = true;
            }
        }
        for(i=position; i >= 0; i--) 
            board[i][j] = 0;
    }
    /* Agrupamento */
    for (j = 0; j < SIZE ; j++) {
        position = SIZE-1;
        for (i = SIZE-1; i >=0 ; i--) {
            if (board[i][j] == board[i - 1][j]) {
                board[position][j] = 2 * board[i][j];
                i--;
                moved = true;
            }
            else {
                board[position][j] = board[i][j];
            }
            position--;
        }
        for (i = position; i >=0; i--)
            board[i][j] = 0;
    }
    return (moved);
}

/*faz a movimentacao para a esquerda
retorna true se o movimento foi feito*/
int moveleft(int board[SIZE][SIZE]){
    int position, i, j, moved=false;
    for (i=0; i<SIZE; i++){
        position = 0;
        for (j = 0; j < SIZE; j++){
            if (board[i][j] != 0){
                board[i][position] = board[i][j];
                position++;
                moved=true;
            }
        }
        for(j=position; j < SIZE; j++) 
            board[i][j] = 0;
    }
    /* Agrupamento */
    for (i = 0; i < SIZE ; i++) {
        position = 0;
        for (j = 0; j < SIZE ; j++) {
            if (board[i][j] == board[i][j+1]) {
                board[i][position] = 2 * board[i][j];
                j++;
                moved=true;
            }
            else {
                board[i][position] = board[i][j];
            }
            position++;
        }
        for (j = position; j < SIZE ; j++)
            board[i][j] = 0;
    }
    return ( moved );
}

/*faz a movimentacao para a direita
retorna true se o movimento foi feito*/
int moveright(int board[SIZE][SIZE]){
    int position, i, j, moved=false;
    for (i=0; i<SIZE; i++){
        position = SIZE-1;
        for (j=SIZE-1; j>=0; j--){
            if (board[i][j] != 0){
                board[i][position] = board[i][j];
                position--;
                moved = true;
            }
        }
        for(j = position; j >= 0; j--) 
            board[i][j] = 0;
    }
    /* Agrupamento */
    for (i = 0; i < SIZE ; i++) {
        position = SIZE-1;
        for (j=SIZE-1; j>=0; j--) {
            if (board[i][j] == board[i][j-1]) {
                board[i][position] = 2 * board[i][j];
                j--;
                moved = true;
            }
            else {
                board[i][position] = board[i][j];
            }
            position--;
        }
        for (j = position; j >= 0 ; j--)
            board[i][j] = 0;
    }
    return (moved);
}

/*retorna true se ainda não chegou em 2048*/
int not2048 (int board[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            if (board[i][j] == 2048){
                return (false);
            }
        }
    }
    return (true);
}

/*retorna true se o board não está cheio*/
int notfilled (int board[SIZE][SIZE]){ 
    int sumposition, i, j;
    sumposition=0;
    for (i = 0; i < SIZE; i++){
        for (j=0; j<SIZE; j++){
            if (board[i][j] != 0){
                sumposition++;
            }
        }
    }

    if (sumposition == BOARDSIZE){
        return (false);
    }

    return (true);
}
/*retorna true se ainda existe posição valida*/
int canmerge (int board[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < SIZE ; i++){
        for (j = 0; j < SIZE; j++){
            if ( (board[i][j] == board[i+1][j]) || (board[i][j] == board[i][j+1]) )
                return(true);
        }
    }
    return(false);
}

int main(){
    int board[SIZE][SIZE], direction, changed = false;
    /*inicializando a ncurses*/
    initscr();
    cbreak();
    raw();
    curs_set(0);
    keypad(stdscr, true);

    start_color();

    if ( has_colors() == FALSE ){	/* testa se o terminal suporta cor */
        printw("Esse terminal não suporta cor!");
        endwin();
        return (false);
	}

    init_pair(NUMBER2, COLOR_WHITE, COLOR_YELLOW); /*COR DO NUMERO 2*/
    init_pair(NUMBER4, COLOR_WHITE, COLOR_BLUE); /*COR DO NUMERO 4*/
    init_pair(NUMBER8, COLOR_WHITE, COLOR_RED); /*COR DO NUMERO 8*/
    init_pair(NUMBER16, COLOR_WHITE, COLOR_MAGENTA); /*COR DO NUMERO 16*/
    init_pair(NUMBER32, COLOR_WHITE, COLOR_GREEN); /*COR DO NUMERO 32*/
    init_pair(NUMBER64, COLOR_WHITE, COLOR_CYAN); /*COR DO NUMERO 64*/
    init_pair(NUMBER128, COLOR_WHITE, COLOR_YELLOW); /*COR DO NUMERO 128*/
    init_pair(NUMBER256, COLOR_WHITE, COLOR_BLUE);/*COR DO NUMERO 256*/
    init_pair(NUMBER512, COLOR_WHITE, COLOR_GREEN); /*COR DO NUMERO 512*/
    init_pair(NUMBER1024, COLOR_BLACK, COLOR_WHITE); /*COR DO NUMERO 1024*/
    init_pair(NUMBER2048, COLOR_WHITE, COLOR_BLACK); /*COR DO NUMERO 2048*/
    init_pair(BACKGROUND, COLOR_BLACK, COLOR_WHITE); /*COR DE FUNDO*/

    /*preparando o tabuleiro*/
    setupgame(board);

    /*começando o jogo*/
    while ( not2048(board) ){
        printboard(board);
        direction = getch();

        /*movendo todos para*/
        if ( direction == 10 ) 
            break;

        else if ( notfilled(board) || canmerge(board) ){
            if(direction == KEY_UP)
                changed = moveup(board);
            
            else if (direction == KEY_DOWN)
                changed = movedown(board);

            else if (direction == KEY_RIGHT)
                changed = moveright(board);
            
            else if (direction == KEY_LEFT)
                changed = moveleft(board);

            if ( changed )
                randomize(board);

        }
        else { 
            printw ("GAME OVER\n");
            refresh();
            getch();
            break;
        }
        refresh();
    }
    endwin();
    exit(0);
}
