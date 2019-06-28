#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;


// Tabuleiro para representação do jog da velha
 static char tabuleiro[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

// Imprime o tabuleiro
void printTabuleiro(){
    cout << "\n  " <<  tabuleiro[0][0] << " | " << tabuleiro[0][1] << " | " << tabuleiro[0][2] << endl << "  ----------\n"
    << "  " << tabuleiro[1][0] << " | " << tabuleiro[1][1] << " | " << tabuleiro[1][2] << endl << "  ----------\n"
    <<"  "<< tabuleiro[2][0] << " | " << tabuleiro[2][1] << " | " << tabuleiro[2][2] << endl;

}

class Jogada{
    public:
    int numVitorias;
    int numEmpates;
    int jog[9][2];
    int numJogadas;
    
    Jogada() {
        numVitorias = 0;
        numEmpates = 0;
        for (int i = 0; i < 9; i++) {
            jog[i][0] = -1;
            jog[i][1] = -1;
        } 
        numJogadas = 0;
        
    }

    int getVitorias(){
        return numVitorias;
    }

    int getEmpates(){
        return numVitorias;
    }

    void setVitorias(int v){
        numVitorias = v;
    }

    void setEmpates(int e){
        numVitorias = e;
    }

    void incrementaNumVitorias(){
        numVitorias++;
    }

    void incrementaNumEmpates(){
        numEmpates++;
    }

    void printJogada(){
        for (int i = 0; i < numJogadas; i++){
            cout << jog[i][0]  << " : " << jog[i][1] << endl;
            tabuleiro[jog[i][0]][jog[i][1]] = 'X';
        }
        printTabuleiro();
    }
};


/*
A estrutura de dados deve ser obrigatoriamente um vetor alocado dinamicamente iniciado com o tamanho 10 e expandido de 10 em 10 elementos
O vetor deve conter uma estrutura denominada Jogada que deve conter as jogadas e o número de vezes que ela foi vencedora, sugiro usar um vetor para armazenar as jogadas
A estrura básica do código deverá ser alterada para possibilitar que seja selecionado um número de jogadas máxima para o modo CC
*/





void loadDataFile(fstream *arquivo, Jogada jog) {
    arquivo->seekg(0);
    arquivo->read((char*)&jog, sizeof(Jogada)); 
    jog.printJogada();
}

void storeDataFile(fstream *arquivo, Jogada jog){
    //if (jogada existe), entao apenas incrementa o numero de vitorias ou empates.
    //else{  grava a nova jogada no arquivo com o numero de vitorias ou empates a ser visto no resultado
    arquivo->write((char*) &jog, sizeof(Jogada));
}

void storeCase(int x, int y, Jogada jog) {
    jog.jog[jog.numJogadas][0] = x;
    jog.jog[jog.numJogadas][1] = y;
}

void userPlay(string currentPlayer, Jogada jog) {
    int x, y;
    bool deu = false;
    while(!deu){
        cout << "\nPosição(x/y): ";
        cin  >> x >> y;
        if (tabuleiro[x][y] == ' '){
            jog.jog[jog.numJogadas][0] = x;
            jog.jog[jog.numJogadas][1] = y;
            
            deu = true;
            if (currentPlayer == "U1"){
                tabuleiro[x][y] = 'U';
            }else{
                tabuleiro[x][y] = 'K';
            }
        }
    }
    storeCase(x, y, jog);
}

bool lookSolution() {
    srand(time(0)*rand());
    int num = rand();
    num = (num % 6)+1;
    if (num >= 3) {
        cout << "[Looking for Solution .. Found]\n";
        return true;
    }
    cout << "[Looking for Solution .. Random]\n";
    return false;
}

void computerPlay(string currentPlayer, Jogada jog) {
    //lookSolution();
    int x, y;
    bool deu = false;
    while(!deu){
        srand(time(0)*rand());
        x = rand()%3;
        srand(time(0)*rand());
        y = rand()%3;
        if (tabuleiro[x][y] == ' '){
            deu = true;
            jog.jog[jog.numJogadas][0] = x;
            jog.jog[jog.numJogadas][1] = y;
            if (currentPlayer == "C1"){
                tabuleiro[x][y] = 'C';
            }else{
                tabuleiro[x][y] = 'K';
            }
        }
        
    }
}


bool gameOver(int step, string currentUser) {
    //linha completa e coluna completa
    for (int i = 0; i < 3; i++){
        if ((tabuleiro[i][0] == tabuleiro[i][1]) and (tabuleiro[i][1] == tabuleiro[i][2]) and tabuleiro[i][2] != ' ') {
            cout << "Winner is " << currentUser << endl;
            return true;
        }
        if ((tabuleiro[0][i] == tabuleiro[1][i]) and (tabuleiro[1][i] == tabuleiro[2][i]) and tabuleiro[2][i] != ' ') {
            cout << "Winner is " << currentUser << endl;
            return true;
        }
    }

    //diagonal principal completa
    if((tabuleiro[0][0] == tabuleiro[1][1]) and (tabuleiro[1][1] == tabuleiro[2][2]) and tabuleiro[1][1] != ' ') {
        cout << "Winner is " << currentUser << endl;
        return true;
    }
    //diagonal secundaria completa
    if((tabuleiro[2][0] == tabuleiro[1][1]) and (tabuleiro[1][1] == tabuleiro[0][2]) and tabuleiro[1][1] != ' ') {
        cout << "Winner is " << currentUser << endl;
        return true;
    }
    //deu velha
    if (step >= 9) {
        return true;
    }
    return false;
}

string changeUser(string currentPlayer, string mode) {
    if (mode == "CC" and currentPlayer == "C1") {
        return "C2";
    }else if(mode == "CC" and currentPlayer == "C2"){
        return "C1";
    }
    
    if (mode == "UU" and currentPlayer == "U2") {
        return "U1";
    }else if(mode == "UU" and currentPlayer == "U1"){
        return "U2";
    }
    
    if (mode == "UC" and currentPlayer == "C1") {
        return "U1";
    }else if (mode == "UC" and currentPlayer == "U1"){
        return "C1";
    }
    return "C1";
}

void gameLoop(string mode, fstream *arquivo, Jogada jog){
    int step = 0;
    string currentPlayer = "C1";
    if (mode == "UC"){
        cout << "Who starts (U/C):\n";
        cin >> currentPlayer;
    }
    if (mode == "UU"){
        currentPlayer = "U";
    }
    currentPlayer+="1";
    bool over = false;
    printTabuleiro();
    while (!over) {
        if (currentPlayer == "U1" or currentPlayer == "U2") {
            userPlay(currentPlayer,jog);
        }else {
            computerPlay(currentPlayer, jog);
        }
        step=step+1;
        printTabuleiro();
        over = gameOver(step, currentPlayer);
        currentPlayer = changeUser(currentPlayer, mode);
        jog.numJogadas++;
    }
    storeDataFile(arquivo, jog);
    cout << jog.numJogadas << endl;
    
    
    cout << "Game is Over\n";
}

int main(){
    fstream arquivo;
    arquivo.open("jogadas.bin", ios::app | ios::binary | ios::in | ios::out);
    string mode;
    cin >> mode;
   // Jogada *jogAux = new Jogada;
    while (mode != "END") {
        if (mode == "CC" or mode == "UC" or mode == "UU") {
            
            Jogada jog;            
            gameLoop(mode, &arquivo, jog);
        }
        else {
            cout << "Incorrect Mode\n";
        }
        cin >> mode;
    }
    //loadDataFile(&arquivo,jog);
    
    return 0;
}
