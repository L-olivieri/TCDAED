#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Matriz {
private:
    int linhas;
    int colunas;
    float** dados;

    // Função auxiliar para limpar a string (remove [ ] e espaços)
    string limparString(const string& entrada) {
        string resultado;
        for (char c : entrada) {
            if (c != ' ' && c != '[' && c != ']') {
                resultado += c;
            }
        }
        return resultado;
    }

public:
    // Construtor
    Matriz(int l, int c) {
        linhas = l;
        colunas = c;

        // Alocar memória
        dados = new float*[linhas];
        for (int i = 0; i < linhas; i++) {
            dados[i] = new float[colunas];
        }
    }

    // Construtor de cópia ??
    Matriz(const Matriz& outra) {
        linhas = outra.linhas;
        colunas = outra.colunas;

        // Alocar memória
        dados = new float*[linhas];
        for (int i = 0; i < linhas; i++) {
            dados[i] = new float[colunas];
            for (int j = 0; j < colunas; j++) {
                dados[i][j] = outra.dados[i][j]; // Copiar os valores
            }
        }
    }

    // Destrutor
    ~Matriz() {
        for (int i = 0; i < linhas; i++) {
            delete[] dados[i];
        }
        delete[] dados;
    }

    //getter das linhas
    int getLinhas() {
        return linhas;
    };
    //getter das colunas
    int getColunas() {
        return colunas;
    };
    //getter dos dados
    float getDado(int linha, int coluna) {
        return dados[linha][coluna];
    };

    Matriz& operator=(const Matriz& outra) {
        // Verificar autoatribuição
        if (this == &outra) {
            return *this;
        }

        // Liberar memória antiga
        for (int i = 0; i < linhas; i++) {
            delete[] dados[i];
        }
        delete[] dados;

        // Copiar dimensões
        linhas = outra.linhas;
        colunas = outra.colunas;

        // Alocar nova memória
        dados = new float*[linhas];
        for (int i = 0; i < linhas; i++) {
            dados[i] = new float[colunas];
            for (int j = 0; j < colunas; j++) {
                dados[i][j] = outra.dados[i][j]; // Copiar valores
            }
        }

        return *this;
    }
    // Método para preencher a matriz a partir da string
    void preencher(const string& entrada) {
        string limpa = limparString(entrada);
        stringstream ss(limpa);

        string numero;
        int linha_atual = 0;
        int coluna_atual = 0;

        while (getline(ss, numero, ',')) {
            if (linha_atual >= linhas) {
                cout << "Erro: mais elementos do que cabem na matriz." << endl;
                return;
            }

            dados[linha_atual][coluna_atual] = stof(numero);
            coluna_atual++;

            if (coluna_atual == colunas) {
                coluna_atual = 0;
                linha_atual++;
            }
        }

        if (linha_atual < linhas) {
            cout << "Aviso: menos elementos do que o tamanho da matriz." << endl;
        }
    }

    // Atribui valor a um elemento da matriz
    void alterar(int linha, int coluna, float valor) {
        dados[linha][coluna] = valor;
    };

    // Método para imprimir a matriz
    void imprimir() {
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                cout << dados[i][j] << " ";
            }
            cout << endl;
        }
    }
};

Matriz soma(Matriz A, Matriz B) {
    // A+B=C
    int lin_A = A.getLinhas();
    int col_A = A.getColunas();
    int lin_B = B.getLinhas();
    int col_B = B.getColunas();
    if (lin_A == lin_B and col_A == col_B) {
        Matriz C = Matriz(lin_A, col_A);
        for (int i = 0; i < lin_A; i++) {
            for (int j = 0; j < col_A; j++) {
                C.alterar(i,j, A.getDado(i,j) + B.getDado(i,j));
            }
        }
        return C;
    }else {
        cout << "Erro: Matrizes com dimensões incompatíveis." << endl;
        // Retorna uma matriz vazia de tamanho 0x0
        return Matriz(0, 0);
    }
};

Matriz multiplica_escalar(Matriz A, float escalar) {
    int col_A = A.getColunas();
    int lin_A = A.getLinhas();
    Matriz C = Matriz(lin_A, col_A);
    for (int i = 0; i < lin_A; i++) {
        for (int j = 0; j < col_A; j++) {
            C.alterar(i,j, A.getDado(i,j) * escalar);
        }
    }
    return C;
};

Matriz multiplica_matrizes(Matriz A, Matriz B) {
    int lin_A = A.getLinhas();
    int col_A = A.getColunas();
    int lin_B = B.getLinhas();
    int col_B = B.getColunas();
    if (col_A == lin_B) {
        Matriz C = Matriz(lin_A, col_B);
        for (int i = 0; i < lin_A; i++) {
            for (int j = 0; j < col_A; j++) {
                int contador = 0;
                for (int k = 0; k < col_A; k++) {
                    contador += A.getDado(i,k) * B.getDado(k, j);
                }
                C.alterar(i, j, contador);
            }
        }
        return C;
    }
    else {
        cout << "Dimensões incompatíveis para produto de matrizes"<< endl;
        return Matriz(0,0);
    };
}

Matriz transposicao(Matriz A) {
    int lin_A = A.getLinhas();
    int col_A = A.getColunas();
    Matriz C = Matriz(lin_A, col_A);

    for (int i = 0; i < lin_A; i++) {
        for (int j = 0; j < col_A; j++) {
            C.alterar(i,j, A.getDado(j,i));
        }
    }
    return C;
}

Matriz pergunta_cria() {
    int linhas, colunas;
    cout << "Digite o número de linhas: ";
    cin >> linhas;
    cout << "Digite o número de colunas: ";
    cin >> colunas;
    cin.ignore(); // Limpa o buffer do cin

    Matriz minhaMatriz(linhas, colunas);


    string entrada;
    cout << "Digite a matriz no formato [[a,b,c],[d,e,f]]:\n";
    getline(cin, entrada);

    minhaMatriz.preencher(entrada);
    return minhaMatriz;
}

#include <iostream>
using namespace std;

// Definição do nó da lista
struct Node {
    Matriz dado;
    Node* proximo;

    Node(const Matriz& valor) : dado(valor) {
        proximo = nullptr;
    }
};

// Definição da classe Lista
class Lista {
private:
    Node* inicio;

public:
    // Construtor
    Lista() {
        inicio = nullptr;
    }

    // Destrutor
    ~Lista() {
        Node* atual = inicio;
        while (atual != nullptr) {
            Node* temp = atual;
            atual = atual->proximo;
            delete temp;
        }
    }

    // Método para inserir no início
    void inserir(Matriz valor) {
        Node* novo = new Node(valor);
        novo->proximo = inicio;
        inicio = novo;
    }

    // Método para imprimir a lista
    void imprimir() {
        Node* atual = inicio;
        cout << "Lista: \n";
        while (atual != nullptr) {
            atual -> dado.imprimir();
            cout << " -> ";
            atual = atual->proximo;
        }
        cout << "NULL" << endl;
    }
};


int main() {
    Lista lista = Lista();
    Matriz A = Matriz(2,2);
    A.preencher("[[1,2], [3,4]]");
    lista.inserir(A);
    Matriz B = multiplica_escalar(A, 5);
    Matriz C = multiplica_matrizes(A, B);
    lista.inserir(B);
    lista.inserir(C);
    lista.imprimir();
    return 0;
}

