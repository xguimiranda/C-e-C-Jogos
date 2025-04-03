#include<iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    cout << "************************************" << endl;
    cout << "*Bem vindos ao jogo de advinhacao!*" << endl;
    cout << "************************************" << endl;

    cout << "Facil = 15 tentativas | Medio = 10 Tentativas | Dificil = 5 tentativas" << endl;
    cout << "Facil (F), Medio (M), Dificil(D): " << endl;

    char dificuldade;
    cin >> dificuldade;

    int numeroDeTentativas;

    if (dificuldade=='F'){
        numeroDeTentativas = 15;
    }else if (dificuldade=='M'){
        numeroDeTentativas=10;
    }else{
        numeroDeTentativas=5;
    }

    srand(time(NULL));
    const int NUMEROSECRETO = rand()%100;

    bool naoAcertou = true;
    int tentativas =0;
    double pontos = 1000.0;

    for (tentativas=1; tentativas<=numeroDeTentativas;tentativas++){
        int chute;
        cout << "Tentativa: " << tentativas << endl;
        cout << "Qual o seu chute: " << endl;
        cin >> chute;

        double pontosPerdidos = abs(chute - NUMEROSECRETO)*5.0;
        pontos = pontos - pontosPerdidos;

        cout << "O valor do seu chute eh: " << chute << endl;
        bool acertou = chute == NUMEROSECRETO;
        bool maior = chute > NUMEROSECRETO;

        if (acertou){
            cout << "Parabens voce acertou!" << endl;
            naoAcertou = false;
            break;
        }else if(maior){
            cout << "Voce chutou um numero maior!" << endl;
        }else{
            cout << "Voce chutou um numero menor!" << endl;
        }
    }

    cout << "Fim de jogo!" << endl;
    if (naoAcertou){
        cout << "Voce perdeu! Tente novamente" << endl;
    }else{
        cout << "Voce acertou o numero secreto em: "<<tentativas << " tentativas" << endl;
        if (pontos<0){
            pontos=0;
        }
        cout << fixed << setprecision(2);
        cout << "Sua pontuacao foi de "<<pontos << " pontos." << endl;
    }
return 0;
}
