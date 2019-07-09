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
    int numEmpates;
    int jog[9][2];
    int numJogadas;
    Jogada* proximo;
    
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

// insere um dado em uma determinada posição da lista
void lista::insere(Jogada JInsere, int posicao) {
    
    Jogada* novo = new Jogada(JInsere);
    
    if(novo){
        if(posicao > tamanho or posicao < 0){
            cerr << "Posicao muito grande desgraça" << endl;
        }
        else{
            if(primeiro == NULL){
                insere(JInsere);
            }
            else{
                Jogada* ant = NULL;
                Jogada* atual = primeiro;
                
                for (int i = 0; i < posicao; i++)
                {
                    ant = atual;
                    atual = atual -> proximo;
                }

            ant -> proximo = novo;
            novo -> proximo = atual;
            }
            tamanho++;
        }
    }
}


// procura por um elemento e retorna a posição ou -1 se não encontrado
int lista::procura(Jogada valor) {
    
    Jogada* aux;
    aux = primeiro;
    int cont = 0;
    
    while(aux != NULL)
    {
        //if(aux -> dado == valor)
        //{
        //    return cont;
        //}
        //else
        //{
        //    aux = aux -> proximo;
        //}
        cont++;
    }
    
    return -1;
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    // Implemente aqui
    if(primeiro == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
A estrutura de dados deve ser obrigatoriamente um vetor alocado dinamicamente iniciado com o tamanho 10 e expandido de 10 em 10 elementos
O vetor deve conter uma estrutura denominada Jogada que deve conter as jogadas e o número de vezes que ela foi vencedora, sugiro usar um vetor para armazenar as jogadas
A estrura básica do código deverá ser alterada para possibilitar que seja selecionado um número de jogadas máxima para o modo CC
*/

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

void computerPlay(string currentPlayer, Jogada *jog, lista *listaJogada, char tabuleiro[3][3]) {
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
            jog->jog[jog->numJogadas][0] = x;
            jog->jog[jog->numJogadas][1] = y;
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
    bool over = false;
    while (!over) {
        cout << "Passou \n";
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
    cout << jog.numJogadas << endl;
    
    cout <<"num: "<<listaJogada->tamanho*sizeof(Jogada) << endl;
    arquivo->write((char*) &jog, sizeof(jog));
    listaJogada->insere(jog);
    listaJogada->imprime();
    
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
    listaJogadas->imprime();
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
