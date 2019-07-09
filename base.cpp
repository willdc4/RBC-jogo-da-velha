#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;


// Tabuleiro para representação do jog da velha
static char tabuleiro1[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

// Imprime o tabuleiro
void printTabuleiro(char tabuleiroP[3][3]){
    cout << "\n  " <<  tabuleiroP[0][0] << " | " << tabuleiroP[0][1] << " | " << tabuleiroP[0][2] << endl << "  ----------\n"
    << "  " << tabuleiroP[1][0] << " | " << tabuleiroP[1][1] << " | " << tabuleiroP[1][2] << endl << "  ----------\n"
    <<"  "<< tabuleiroP[2][0] << " | " << tabuleiroP[2][1] << " | " << tabuleiroP[2][2] << endl;

}

class Jogada{
	friend class lista;
    public:
    int numVitorias;
    int jog[9][2];
    int numJogadas;
    Jogada* proximo;
    bool ehPlayer1;
    
    Jogada() {
        numVitorias = 0;
        for (int i = 0; i < 9; i++) {
            jog[i][0] = -1;
            jog[i][1] = -1;
        } 
        numJogadas = 0;
        
    }

    int getVitorias(){
        return numVitorias;
    }


    void setVitorias(int v){
        numVitorias = v;
    }

    void incrementaNumVitorias(){
        numVitorias++;
    }


    void printJogada(){
        char tabuleiroPrint[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
        for (int i = 0; i < numJogadas; i++){
            cout << jog[i][0]  << " : " << jog[i][1] << endl;
            tabuleiroPrint[jog[i][0]][jog[i][1]] = 'X';
        }
        printTabuleiro(tabuleiroPrint);
    }
};



class lista {
    private:
        
        Jogada* ultimo;
        
    public:
        int tamanho;
        Jogada* primeiro;
        lista();
        ~lista();
        void insere(Jogada dado);
        Jogada* buscaMelhor(Jogada *jog, string cp);
        void insere(Jogada dado, int pos);
        int procura(Jogada valor);
        void imprime();
        inline bool vazia();
};

// constrói uma lista inicialmente vazia
lista::lista() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

lista::~lista() {
    Jogada* iter = primeiro;
    Jogada* proximo = NULL;
    while (iter != NULL) {
        proximo = iter->proximo;
        delete iter;
        iter = proximo;
    }
}

// método básico que *percorre* a lista, imprimindo seus elementos
void lista::imprime() {
    Jogada* aux = primeiro;
    while (aux != NULL) {
        aux->printJogada();
        aux = aux->proximo;
    }
    cout << endl;
}

Jogada* lista::buscaMelhor(Jogada *jog, string cp)  {
    Jogada* aux = primeiro;
    float maior = -1;
    Jogada* maiorJ = NULL;
    bool player1 = false;
    if(cp[1] == '1') {
        player1 = true;
    }

    while (aux != NULL) {
        
        bool foi = true;
        for(int i = 0; i < jog->numJogadas && foi; i++) {
            if (jog->jog[i][0] == aux->jog[i][0] && jog->jog[i][1] == aux->jog[i][1] && aux->ehPlayer1 == player1) {
            }else{
                foi = false;
            }
        }

        if  (aux->getVitorias() > maior and foi){
            maior = aux->getVitorias();
            maiorJ = aux;
        }
        aux = aux->proximo;
    }
    return maiorJ;
}

// insere por padrão no final da lista
void lista::insere(Jogada JInsere) {
    
    Jogada* novo = new Jogada(JInsere);
    
    if(novo)
    {
        novo -> proximo = NULL;
        
        if(primeiro == NULL){
           primeiro = novo;
           ultimo = novo;
       }
       else{
           ultimo -> proximo = novo;
           ultimo = novo;
       }
       tamanho++;
   }
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
        if (tabuleiro1[x][y] == ' '){
            jog.jog[jog.numJogadas][0] = x;
            jog.jog[jog.numJogadas][1] = y;
            
            deu = true;
            if (currentPlayer == "U1"){
                tabuleiro1[x][y] = 'U';
            }else{
                tabuleiro1[x][y] = 'K';
            }
        }
    }
    storeCase(x, y, jog);
}


void computerPlay(string currentPlayer, Jogada *jog, lista *listaJogada, char tabuleiro[3][3]) {
    int x, y;
    bool deu = false;
    Jogada *seguida = NULL;
    srand(time(0)*rand());
    int numRand = rand()%5;

    if (numRand!=0){
        seguida = listaJogada->buscaMelhor(jog, currentPlayer);
    }else{
        cout << "escolheu ir por uma direção aleatoria" << endl;
    }
    if  (seguida == NULL){
        cout << "\nNão achou jogada\n" << endl;
        while(!deu){
            srand(time(0)*rand());
            x = rand()%3;
            srand(time(0)*rand());
            y = rand()%3;
            if (tabuleiro[x][y] == ' '){
                deu = true;
                jog->jog[jog->numJogadas][0] = x;
                jog->jog[jog->numJogadas][1] = y;
                if (currentPlayer == "C1"){
                    tabuleiro[x][y] = 'C';
                }else{
                    tabuleiro[x][y] = 'K';
                }
            }
        }
    }else{
        cout << "\nAchou jogada\n" << endl;
        jog->jog[jog->numJogadas][0] = seguida->jog[jog->numJogadas][0];
        jog->jog[jog->numJogadas][1] = seguida->jog[jog->numJogadas][1];
        if (currentPlayer == "C1"){
            tabuleiro[jog->jog[jog->numJogadas][0]][jog->jog[jog->numJogadas][1]] = 'C';
        }else{
            tabuleiro[jog->jog[jog->numJogadas][0]][jog->jog[jog->numJogadas][1]] = 'K';
        }
    }
}


int gameOver(int step, string currentUser, char tabuleiro[3][3]) {
    //linha completa e coluna completa
    for (int i = 0; i < 3; i++){
        if ((tabuleiro[i][0] == tabuleiro[i][1]) and (tabuleiro[i][1] == tabuleiro[i][2]) and tabuleiro[i][2] != ' ') {
            return 1;
        }
        if ((tabuleiro[0][i] == tabuleiro[1][i]) and (tabuleiro[1][i] == tabuleiro[2][i]) and tabuleiro[2][i] != ' ') {
            return 1;
        }
    }

    //diagonal principal completa
    if((tabuleiro[0][0] == tabuleiro[1][1]) and (tabuleiro[1][1] == tabuleiro[2][2]) and tabuleiro[1][1] != ' ') {
        return 1;
    }
    //diagonal secundaria completa
    if((tabuleiro[2][0] == tabuleiro[1][1]) and (tabuleiro[1][1] == tabuleiro[0][2]) and tabuleiro[1][1] != ' ') {
        return 1;
    }
    //deu velha
    if (step >= 9) {
        return 2;
    }
    return 0;
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

void gameLoop(string mode, fstream *arquivo, lista *listaJogada){
    Jogada jog;
    char tabuleiro[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    jog.printJogada();
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
    int over = 0;
    while (over == 0) {
        if (currentPlayer == "U1" or currentPlayer == "U2") {
            userPlay(currentPlayer,jog);
        }else {
            computerPlay(currentPlayer, &jog, listaJogada, tabuleiro);
        }
        step=step+1;
        printTabuleiro(tabuleiro);
        over = gameOver(step, currentPlayer, tabuleiro);
        currentPlayer = changeUser(currentPlayer, mode);
        jog.numJogadas++;
    }
    if  (over == 1){
        if (currentPlayer[1] == '2'){
            jog.ehPlayer1 = true;
            
        }else{
            jog.ehPlayer1 = false;
        }
    }
    jog.incrementaNumVitorias();
    arquivo->write((char*) &jog, sizeof(jog));
    listaJogada->insere(jog);
    
    cout << "Game is Over\n";
}

int main(){
	fstream arquivo;
	lista *listaJogadas;
    listaJogadas = new lista();
    arquivo.open("jogadas.bin", ios::app | ios::binary | ios::in | ios::out);
    
    Jogada aux;
    arquivo.seekg(0);
    arquivo.read((char*) &aux, sizeof(Jogada));
    while(!arquivo.eof()) {
        listaJogadas->insere(aux);
        arquivo.read((char*) &aux, sizeof(Jogada));
    }
    arquivo.clear();
    arquivo.seekg(0);
    arquivo.seekp(0);
    string mode;
    cin >> mode;
   // Jogada *jogAux = new Jogada;
    while (mode != "END") {
        if (mode == "CC" or mode == "UC" or mode == "UU") {
            gameLoop(mode, &arquivo, listaJogadas);

            // ver se jogada está na lista
        }
        else {
            cout << "Incorrect Mode\n";
        }
        cin >> mode;
    }

    return 0;
}
