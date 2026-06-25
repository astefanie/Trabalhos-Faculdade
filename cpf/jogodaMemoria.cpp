//Grupo: Alberto H.W, Arthur Petrelli, Gabriel Bestetti, Raisla Viti, Stefanie Saffnauer, Thiago da Rocha 
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
#define TAM 4 // Define o tamanho da matriz (4x4)

int main(){
    
    srand(time(NULL)); // Geração de semente randômica

    char jogarNovamente; 
    
    do{
        int gabarito[TAM][TAM], jogo[TAM][TAM] = {0}; //Declaração das variáveis das matrizes
        int principal[TAM][TAM] = {//Variável dos dígitos presentes na matriz
            {1, 4, 5, 2},
            {7, 2, 8, 7},
            {3, 6, 1, 4},
            {6, 5, 3, 8}
        }; 

        int aleatorio = rand() % 4 + 1;//Variável que escolhe aleatoriamente um número de 1 a 4

        switch (aleatorio){ // Estrutura condicional que alterna como a matriz principal será copiada para o gabarito
            case 1: // Caso 1: Mantém a matriz principal na ordem original
                for(int linha = 0; linha < TAM; linha++){
                    for(int coluna = 0; coluna < TAM; coluna++){
                        gabarito[linha][coluna] = principal[linha][coluna];
                    }
                }
                break;
            case 2: // Caso 2: Transposta da matriz principal
                for(int linha = 0; linha < TAM; linha++){
                    for(int coluna = 0; coluna < TAM; coluna++){
                        gabarito[linha][coluna] = principal[coluna][linha]; 
                    }
                }
                break;
            case 3: // Caso 3: Inverte as linhas da matriz principal
                for(int linha = 0; linha < TAM; linha++){
                    for(int coluna = 0; coluna < TAM; coluna++){
                        gabarito[linha][coluna] = principal[TAM - 1 - linha][coluna];
                    }
                }
                break;
            case 4: // Caso 4: Inverte as colunas da matriz principal
                for(int linha = 0; linha < TAM; linha++){
                    for(int coluna = 0; coluna < TAM; coluna++){
                        gabarito[linha][coluna] = principal[linha][TAM - 1 - coluna];
                    }
                }                    
                break;
        }
        
        cout << "Bem vindo ao Jogo da Memoria!" << endl // Exibe a tela de boas-vindas e as instruções básicas
             << "Você tera 24 jogadas para tentar acertar todos os pares!" << endl 
             << "Aperte quaquer tecla para continuar: " << endl;
             
        cin.ignore(); // Limpa o buffer de entrada
        cin.ignore(); 
        cout<<"\033c"; // Limpa a tela do terminal

        int l1, c1, l2, c2, jogadas = 0, pares = 0;  // Variáveis do jogo
        
        do { 
            cout << "\t1\t2\t3\t4" << endl; // Imprime o cabeçalho das colunas

            for(int linha = 0; linha < TAM; linha++){ // Loop para desenhar o tabuleiro atual para o jogador
                cout << linha + 1 << "\t"; // Imprime o número da linha na lateral

                for(int coluna = 0; coluna < TAM; coluna++){

                    if (jogo[linha][coluna] == 0){ // Se a posição for 0, a carta está escondida
                        cout << "*\t";
                    }
                    else{ // Se não for 0, mostra o número já descoberto
                        cout << jogo[linha][coluna] << "\t";
                    }
                    
                }
                cout << endl;
            }
            cout << "Jogadas restantes: " << 24 - jogadas << endl; // Mostra o número de rodadas restantes

            cout << "Adicione suas coordenadas das peças desejadas: " << endl;
            cout << "Coordenadas 1:" << endl << "Linha:\t"; // Pede as coordenadas
            cin >> l1;
            cout << "Coluna:\t";
            cin >> c1;
            cout << "Coordenadas 2:" << endl << "Linha:\t";
            cin >> l2;
            cout << "Coluna:\t";
            cin >> c2;
            

            l1 = l1 - 1; c1 = c1 - 1; // Diminui 1 das coordenadas, considerando que para o computador a linha 1 = 0
            l2 = l2 - 1; c2 = c2 - 1;
            
            while (l1 == l2 and c1 == c2 or l1 >= TAM or l1 < 0 or l2 < 0 or l2 >= TAM or // Validação para impedir jogadas repetidas, coordenadas fora do tabuleiro ou escolher a mesma carta duas vezes
            c1 >= TAM or c1 < 0 or c2 < 0 or c2 >= TAM or jogo[l1][c1] != 0 
            or jogo[l2][c2] !=0)  {
                cout << "Coordenadas Invalidas! Escolha novamente: " << endl;

                cout << "Coordenadas 1:" << endl << "Linha:\t"; // Atualiza as variáveis com a nova tentativa do usuário
                cin >> l1;
                cout << "Coluna:\t";
                cin >> c1;
                cout << "Coordenadas 2:" << endl << "Linha:\t";
                cin >> l2;
                cout << "Coluna:\t";
                cin >> c2;
                
                l1 = l1 - 1; c1 = c1 - 1; 
                l2 = l2 - 1; c2 = c2 - 1;
            }

            cout << "\t1\t2\t3\t4" << endl; 


            for(int linha = 0; linha < TAM; linha++){ // Loop para mostrar temporariamente o tabuleiro com as cartas escolhidas pelo usuário
                cout << linha + 1 << "\t";

                for(int coluna = 0; coluna < TAM; coluna++){

                    if((linha == l1 and coluna == c1) or 
                       (linha == l2 and coluna == c2)){ // Se a posição for uma das escolhidas, revela o valor do gabarito
                        cout << gabarito[linha][coluna] << "\t";

                       }
                    else if(jogo[linha][coluna] == 0){ // Mantém escondidas as posições que ainda não foram descobertas
                        cout << "*\t";
                    }
                    else{ // Mantém visíveis as que já foram descobertas anteriormente
                        cout << jogo[linha][coluna] << "\t";
                    }
                }
                cout << endl;
            }

            if(gabarito[l1][c1] == gabarito[l2][c2]){ // Verifica se os valores das duas cartas escolhidas são iguais
                cout << "JOGADA OK! (digite algo para continuar)" << endl;  
            
                jogo[l1][c1] = gabarito[l1][c1]; // Salva a carta 1 na matriz visível do jogo
                jogo[l2][c2] = gabarito[l2][c2]; // Salva a carta 2 na matriz visível do jogo
            
                pares++; // Incrementa a contagem de pares encontrados
            } 
            else{
                cout << "JOGADA NOK. :( (digite algo para continuar)" << endl; // Informa que errou o par
            }

            jogadas++; // Incrementa o número de jogadas realizadas

            cin.ignore(); 
            cin.ignore(); 
            cout<<"\033c"; // Limpa a tela para a próxima rodada
                
            

        } while(jogadas < 24 and pares < 8); // O jogo continua enquanto tiver jogadas e não achar os 8 pares

        if(pares == 8){ // Condição de vitória: se encontrou todos os 8 pares
            for(int linha = 0; linha < TAM; linha++){ // Exibe o tabuleiro completo do gabarito final
                for(int coluna = 0; coluna < TAM; coluna++){
                    cout << gabarito[linha][coluna] << "\t";
                }
                cout << endl;
            }

            cout << "Você venceu!" << endl 
                 << "Gostaria de jogar novamente?(s/n) " << endl;
            cin >> jogarNovamente; // Pergunta se quer recomeçar
        }
        else{ // Caso contrário, o jogador esgotou as 24 jogadas e perdeu
            for(int linha = 0; linha < TAM; linha++){ // Exibe o tabuleiro do gabarito para mostrar onde as cartas estavam
                for(int coluna = 0; coluna < TAM; coluna++){
                    cout << gabarito[linha][coluna] << "\t";
                }
                cout << endl;
            }
            cout << endl;
            
            cout << "Você perdeu! " << endl 
                 << "Gostaria de jogar novamente?(s/n) " << endl;
            cin >> jogarNovamente; // Pergunta se quer recomeçar
        }

        if (jogarNovamente == 'n' or jogarNovamente == 'N'){ // Mensagem de despedida caso o usuário queira sair
            cout << "Obrigado(a) por jogar!";
        }

    }while(jogarNovamente == 's' or jogarNovamente == 'S'); // Mantém o loop do jogo inteiro ativo enquanto responder 's' ou 'S'

    return 0;
}