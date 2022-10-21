#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector <int> distancias;
int maior[2] = {0, 0};
bool continuar;


// 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente
// entre dois valores mínimo e máximo e retorna esse valor

void ex1(float valor, float vmax, float vmin) {
  float resultado = 0;
  resultado = 100 * ((valor - vmin) / (vmax - vmin));
  if (resultado < 50) {
    resultado = 100 - resultado;
    cout << "O valor " << valor << " está " << resultado << "% mais próximo de "
         << vmin << endl;
  } else if (resultado > 50) {
    cout << "O valor " << valor << " está " << resultado << "% mais próximo de "
         << vmax << endl;
  } else {
    cout << "O valor " << valor << " é a média entre " << vmin << " e " << vmax
         << endl;
  }
}

// 2 - Faça uma função que simule a leitura de um sensor lendo o
// valor do teclado ao final a função retorna este valor

int ex2() {
  float numero = 0;
  cout << "Digite um numero inteiro: " << endl;
  cin >> numero;
  return numero;
}

// 3 - Faça uma função que armazena uma medida inteira qualquer
// em um vetor fornecido. Note que como C não possui vetores
// nativos da linguagem, lembre-se que você precisa passar o
// valor máximo do vetor assim como a última posição preenchida
// Evite também que, por acidente, um valor seja escrito em
// uma área de memória fora do vetor
void ex3 () {

    cout <<endl<<"Defina a distancia do robo ate o objeto mais proximo a direita dele."<<endl;
    int direita = ex2();
    distancias.push_back(direita);

    cout << "Defina a distancia do robo ate o objeto mais proximo a esquerda dele."<<endl;
    int esquerda = ex2();
    distancias.push_back(esquerda);

    cout << "Defina a distancia do robo ate o objeto mais proximo a frente dele."<<endl;
    int frente = ex2();
    distancias.push_back(frente);

    cout << "Defina a distancia do robo ate o objeto mais proximo atras dele."<<endl;
    int tras = ex2();
    distancias.push_back(tras);
}

// 4 - Faça uma função que recebe um vetor com 4 posições que contém
// o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção
// de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a
// segunda é esta maior distância.
void ex4() {
  int maiorValor = distancias[0];
  int maiorDistancia = 0;



  for (int i = 1; i < 4; i++) {
    if (distancias[i] > maiorValor) {
      maiorValor = distancias[i];
      maiorDistancia = i;
    }
  }

  maior[0] = maiorDistancia;
  maior[1] = maiorValor;
}

// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e
// retorna verdadeiro ou falso
void ex5() {
  int resposta = 0;
  cout << "Para continuar o mapeamento digite 1, caso contrario, digite 0.";
  cin >> resposta;
  while (resposta != 1 && resposta != 0) {
    cout << "Valor invalido. Digite 0 (parar o mapeamento) ou 1 (continuar).";
    cin >> resposta;
  }
  if (resposta == 1) {
    continuar = true;
  }
  else {
    continuar = false;
  }
}

void ex6 () {
    cout << endl << "O robo andou uma unidade para ";

    if (maior[0] == 0) {
        distancias[0] -= 1;
        distancias[1] += 1;

        cout << "direita" << endl;
    }
    else if (maior[0] == 1) {
        distancias[1] -= 1;
        distancias[0] += 1;

        cout << "esquerda" << endl;
    }
    else if (maior[0] == 2) {
        distancias[2] -= 1;
        distancias[3] += 1;

        cout << "frente" << endl;
    }
    else if (maior[0] == 3) {
        distancias[3] -= 1;
        distancias[2] += 1;

        cout << "tras" << endl;
    }
}


int main() {
    const string lados[4] = {"Direita", "Esquerda", "Frente", "Tras"};
    ex3();
    continuar = true;
    cout << "As distancias sao:" << endl << endl;
    for (int i=0; i < 4; i++) {
        cout << lados[i] << ": " << distancias[i] << endl;
    }
    while (continuar == true) {
        ex4();
        ex6();
        cout << "As distancias sao:" << endl << endl;
        for (int i=0; i < 4; i++) {
            cout << lados[i] << ": " << distancias[i] << endl;
        }
        ex5();
    }
    return 0;
}
