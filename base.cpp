#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>0
#include <cstdlib>

using namespace std;


void printTabuleiro(char tabuleiro[3][3]){
    cout << "\n  " <<  tabuleiro[0][0] << " | " << tabuleiro[0][1] << " | " << tabuleiro[0][2] << endl << "  ----------" << endl << "  " 
    << tabuleiro[1][0] << " | " << tabuleiro[1][1] << " | " << tabuleiro[1][2] << endl << "  ----------" << endl 
    <<"  "<< tabuleiro[2][0] << " | " << tabuleiro[2][1] << " | " << tabuleiro[2][2] << endl;

}

class Jogada{
    public:
    int numVencedora;
    int numEmpates;
    int jog[9][2];
    int numJogadas;
    char tabuleiro[3][3];
    
    void printJ(){
        for (int i = 0; i < numJogadas; i++){
            cout << jog[i][0]  << " : " << jog[i][1] << endl;
            tabuleiro[jog[i][0]][jog[i][1]] = 'X';
        }
        printTabuleiro(tabuleiro);
        
    }
    
    int getVencedora(){
        return numVencedora;
    }
    void setVencedora(int v){
        numVencedora = v;
    }
    
    int getEmpates(){
        return numVencedora;
    }
    void setEmpates(int e){
        numVencedora = e;
    }
    void incrementaNumVencedora(){
        numVencedora++;
    }
    void incrementaNumEmpates(){
        numEmpates++;
    }
};

Jogada j1;
fstream fgrava;
/*
A estrutura de dados deve ser obrigatoriamente um vetor alocado dinamicamente iniciado com o tamanho 10 e expandido de 10 em 10 elementos
O vetor deve conter uma estrutura denominada Jogada que deve conter as jogadas e o número de vezes que ela foi vencedora, sugiro usar um vetor para armazenar as jogadas
A estrura básica do código deverá ser alterada para possibilitar que seja selecionado um número de jogadas máxima para o modo CC
*/





void loadDataFile() {
    fgrava.seekg(0);
    for 
    fgrava.read((char*)&j1, sizeof(Jogada)); 
    j1.printJ();
}

void storeDataFile(){
    //if (jogada existe), entao apenas incrementa o numero de vitorias ou empates.
    //else{  grava a nova jogada no arquivo com o numero de vitorias ou empates a ser visto no resultado
        fgrava.write((char*) &j1, sizeof(Jogada));
}

void storeCase(int x, int y) {
    j1.jog[j1.numJogadas][0] = x;
    j1.jog[j1.numJogadas][1] = y;
}

void userPlay(string currentPlayer,char tabuleiro[3][3]) {
    int x, y;
    bool deu = false;
    while(!deu){
        cin  >> x >> y;
        if (tabuleiro[x][y] == ' '){
            j1.jog[j1.numJogadas][0] = x;
            j1.jog[j1.numJogadas][1] = y;
            
            deu = true;
            if (currentPlayer == "U1"){
                tabuleiro[x][y] = 'U';
            }else{
                tabuleiro[x][y] = 'K';
            }
        }
    }
    storeCase(x, y);
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

void computerPlay(char tabuleiro[3][3], string currentPlayer) {
    lookSolution();
    int x, y;
    bool deu = false;
    while(!deu){
        srand(time(0)*rand());
        x = rand()%3;
        srand(time(0)*rand());
        y = rand()%3;
        if (tabuleiro[x][y] == ' '){
            deu = true;
            j1.jog[j1.numJogadas][0] = x;
            j1.jog[j1.numJogadas][1] = y;
            if (currentPlayer == "C1"){
                tabuleiro[x][y] = 'C';
            }else{
                tabuleiro[x][y] = 'K';
            }
        }
        
    }
}


bool gameOver(int step, string currentUser, char tabuleiro[3][3]) {
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

void gameLoop(string mode){
    char tabuleiro[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
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
    printTabuleiro(tabuleiro);
    while (!over) {
        if (currentPlayer == "U1" or currentPlayer == "U2") {
            userPlay(currentPlayer, tabuleiro);
        }else {
            computerPlay(tabuleiro, currentPlayer);
        }
        step=step+1;
        printTabuleiro(tabuleiro);
        over = gameOver(step, currentPlayer, tabuleiro);
        currentPlayer = changeUser(currentPlayer, mode);
        j1.numJogadas++;
    }
    storeDataFile();
    cout << j1.numJogadas << endl;
    
    
    cout << "Game is Over\n";
}

int main(){
    fgrava.open("jogadas.bin", ios::app | ios::binary | ios::in | ios::out);
    string mode;
    cin >> mode;
    while (mode != "END") {
        if (mode == "CC" or mode == "UC" or mode == "UU") {
            
            j1.numJogadas = 0;
            for (int i = 0; i < 9; i++)
            {
                j1.jog[i][0] = -1;
                j1.jog[i][1] = -1;
            }
            
            gameLoop(mode);
        }
        else {
            cout << "Incorrect Mode\n";
        }
        cin >> mode;
    }
    loadDataFile();
    return 0;
}
