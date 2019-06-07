#include <iostream>

#include <cstdlib>
using namespace std;

struct jogada{
    int numVencedora;
    int numEmpates;
    int jog[9][2];
};

/*
A estrutura de dados deve ser obrigatoriamente um vetor alocado dinamicamente iniciado com o tamanho 10 e expandido de 10 em 10 elementos
O vetor deve conter uma estrutura denominada Jogada que deve conter as jogadas e o número de vezes que ela foi vencedora, sugiro usar um vetor para armazenar as jogadas
A estrura básica do código deverá ser alterada para possibilitar que seja selecionado um número de jogadas máxima para o modo CC
*/

void loadDataFile() {
    cout << "Loading Data\n";
}

void storeDataFile() {
    cout << "Storing Data\n";
}

void userPlay() {
    cout << "[User play]\n";
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

void computerPlay() {
    lookSolution();
    cout << "[Computer play]\n";
}
void storeCase() {
    cout << "[Case Stored]\n";
}

bool gameOver(int step, string currentUser, char tabuleiro[3][3]) {
    //linha completa
    for (int i = 0; i < 3; i++){
        if ((tabuleiro[i][0] == tabuleiro[i][1]) and (tabuleiro[i][1] == tabuleiro[i][2])) {
            cout << "Winner is " << currentUser << endl;
            return true;
        }
    }
    //coluna completa
    for (int i = 0; i < 3; i++){
        if ((tabuleiro[0][i] == tabuleiro[1][i]) and (tabuleiro[1][i] == tabuleiro[2][i])) {
            cout << "Winner is " << currentUser << endl;
            return true;
        }
    }
    //diagonal principal completa
    if((tabuleiro[0][0] == tabuleiro[1][1]) and (tabuleiro[1][1] == tabuleiro[2][2])) {
        cout << "Winner is " << currentUser << endl;
        return true;
    }
    //diagonal secundaria completa
    if((tabuleiro[3][0] == tabuleiro[2][2]) and (tabuleiro[2][2] == tabuleiro[1][3])) {
        cout << "Winner is " << currentUser << endl;
        return true;
    }
    //deu velha
    if (step == 9) {
        return true;
    }
    return false;
}

string changeUser(string currentPlayer, string mode) {
    if (mode == "CC") {
        return "C";
    }
    
    if (mode == "UU") {
        return "U";
    }
    
    if (mode == "UC" and currentPlayer == "C") {
        return "U";
    }
    return "C";
}

void gameLoop(string mode, jogada j1){
    char tabuleiro[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int step = 0;
    string currentPlayer = "C";
    if (mode == "UC"){
        cout << "Who starts (U/C):\n";
        cin >> currentPlayer;
    }
    else if (mode == "UU"){
        currentPlayer = "U";
    }
    bool over = false;
    while (!over) {
        if (currentPlayer == "C") {
            int x, y;
            bool deu = false;
            while(!deu){
                cin  >> x >> y;
                if (tabuleiro[x][y] == '2'){
                    deu = true;
                    tabuleiro[x][y] = 'C';
                }
            }
            
        }
        else {
            userPlay();
        }
        storeCase();
        over = gameOver(step, currentPlayer, tabuleiro);
        currentPlayer = changeUser(currentPlayer, mode);
        step=step+1;
    }
    cout << "Game is Over\n";
}

int main(){
    
    loadDataFile();
    string mode;
    cin >> mode;
    while (mode != "END") {
        if (mode == "CC" or mode == "UC" or mode == "UU") {
            jogada j1;
            for (int i = 0; i < 9; i++)
            {
                j1.jog[i][0] = 0;
                j1.jog[i][1] = 0;
            }
            
            gameLoop(mode, j1);
        }
        else {
            cout << "Incorrect Mode\n";
        }
        cin >> mode;
        storeDataFile();
    }
    return 0;
}
