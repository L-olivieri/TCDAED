#include <iostream>
#include <string>
#include <sstream>
#include <vector>
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
    virtual ~Matriz() {
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

Matriz subtracao(Matriz A, Matriz B) {
    // A-B=C
    int lin_A = A.getLinhas();
    int col_A = A.getColunas();
    int lin_B = B.getLinhas();
    int col_B = B.getColunas();
    if (lin_A == lin_B and col_A == col_B) {
        Matriz C = Matriz(lin_A, col_A);
        for (int i = 0; i < lin_A; i++) {
            for (int j = 0; j < col_A; j++) {
                C.alterar(i,j, A.getDado(i,j) - B.getDado(i,j));
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
    Matriz C = Matriz(col_A, lin_A);

    for (int i = 0; i < col_A; i++) {
        for (int j = 0; j < lin_A; j++) {
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

class MatrizQuadrada : public Matriz {
public:
    MatrizQuadrada(int n) : Matriz(n, n) {}

    float traco() {
        float soma = 0;
        for (int i = 0; i < getLinhas(); i++) {
            soma += getDado(i, i);
        }
        return soma;
    }

    float determinante() {
        if (getLinhas() == 2) {
            return getDado(0,0)*getDado(1,1) - getDado(0,1)*getDado(1,0);
        } else {
            cout << "Determinante so implementado para matrizes 2x2." << endl;
            return 0;
        }
    }
};


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
    vector<Matriz*> matrizes; // Armazena ponteiros para matrizes criadas

    int opcao;
    do {
        cout << "\n===== CALCULADORA DE MATRIZES =====" << endl;
        cout << "1. Criar matriz" << endl;
        cout << "2. Criar matriz quadrada" << endl;
        cout << "3. Somar duas matrizes" << endl;
        cout << "4. Subtrair duas matrizes" << endl;
        cout << "5. Multiplicar duas matrizes" << endl;
        cout << "6. Multiplicar matriz por escalar" << endl;
        cout << "7. Transpor matriz" << endl;
        cout << "8. Traco (matriz quadrada)" << endl;
        cout << "9. Determinante (matriz quadrada)" << endl;
        cout << "10. Ver todas as matrizes" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();

        if (opcao == 1) {
            Matriz* m = new Matriz(pergunta_cria());
            matrizes.push_back(m);
            m->imprimir();
            cout << "Sua matriz está salva. Caso queira fazer alguma conta com ela e não saiba seu índice, escolha 10" << endl;
        }
        else if (opcao == 2) {
            int n;
            cout << "Informe a ordem da matriz quadrada: ";
            cin >> n;
            cin.ignore();
            MatrizQuadrada* mq = new MatrizQuadrada(n);
            string entrada;
            cout << "Digite a matriz no formato [[a,b],[c,d]]:\n";
            getline(cin, entrada);
            mq->preencher(entrada);
            matrizes.push_back(mq);
            mq->imprimir();
        }
        else if (opcao == 3 || opcao == 4 || opcao == 5) {
            int i1, i2;
            cout << "Índice da primeira matriz: "; cin >> i1;
            cout << "Índice da segunda matriz: "; cin >> i2;

            if (i1 >= matrizes.size() || i2 >= matrizes.size()) {
                cout << "Índice inválido." << endl;
                continue;
            }

            Matriz* res = nullptr;
            if (opcao == 3)
                res = new Matriz(soma(*matrizes[i1], *matrizes[i2]));
            else if (opcao == 4)
                res = new Matriz(subtracao(*matrizes[i1], *matrizes[i2]));
            else
                res = new Matriz(multiplica_matrizes(*matrizes[i1], *matrizes[i2]));

            matrizes.push_back(res);
            cout << "Resultado:\n";
            res->imprimir();
        }
        else if (opcao == 6) {
            int i; float esc;
            cout << "Índice da matriz: "; cin >> i;
            cout << "Escalar: "; cin >> esc;

            if (i >= matrizes.size()) {
                cout << "Índice inválido." << endl;
                continue;
            }

            Matriz* res = new Matriz(multiplica_escalar(*matrizes[i], esc));
            matrizes.push_back(res);
            cout << "Resultado:\n";
            res->imprimir();
        }
        else if (opcao == 7) {
            int i;
            cout << "Índice da matriz: "; cin >> i;
            if (i >= matrizes.size()) {
                cout << "Índice inválido." << endl;
                continue;
            }

            Matriz* res = new Matriz(transposicao(*matrizes[i]));
            matrizes.push_back(res);
            cout << "Transposta:\n";
            res->imprimir();
        }
        else if (opcao == 8 || opcao == 9) {
            int i;
            cout << "Índice da matriz quadrada: "; cin >> i;
            if (i >= matrizes.size()) {
                cout << "Índice inválido." << endl;
                continue;
            }

            MatrizQuadrada* q = dynamic_cast<MatrizQuadrada*>(matrizes[i]);
            if (!q) {
                cout << "Essa matriz não é quadrada." << endl;
                continue;
            }

            if (opcao == 8)
                cout << "Traço: " << q->traco() << endl;
            else
                cout << "Determinante: " << q->determinante() << endl;
        }
        else if (opcao == 10) {
            for (int i = 0; i < matrizes.size(); i++) {
                cout << "[" << i << "]\n";
                matrizes[i]->imprimir();
            }
        }
        else if (opcao != 0) {
            cout << "Opção inválida." << endl;
        }

    } while (opcao != 0);

    // Limpeza de memória
    for (Matriz* m : matrizes) {
        delete m;
    }

    cout << "Programa encerrado." << endl;
    return 0;
}


