#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

class Matriz {
protected:
    int linhas;
    int colunas;
    float** dados;
    string nome;

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

    void setNome(const string& n) {
        nome = n;
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
    virtual float getDado(int linha, int coluna) const {
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
    virtual void preencher(const string& entrada) {
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
    virtual void alterar(int linha, int coluna, float valor) {
        dados[linha][coluna] = valor;
    };

    // Método para imprimir a matriz
    virtual void imprimir() {
        cout << nome << " Matriz generica " << linhas << "x" << colunas << ":\n";
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                cout << dados[i][j] << " ";
            }
            cout << endl;
        }
    }
};

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

    virtual float determinante() {
        if (getLinhas() == 2) {
            return getDado(0,0)*getDado(1,1) - getDado(0,1)*getDado(1,0);
        } else {
            cout << "Determinante so implementado para matrizes 2x2." << endl;
            return 0;
        }
    }
    virtual void imprimir() {
        cout <<nome << " Matriz Quadrada " << linhas << "x" << colunas << ":\n";
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                cout << dados[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// Definição do nó da lista
struct Node {
    float dado;
    Node* proximo;

    Node(const float& valor) : dado(valor) {
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
    void inserir(float valor) {
        Node* novo = new Node(valor);
        novo->proximo = inicio;
        inicio = novo;
    }

void inserir_final(float valor) {
    Node* novo = new Node(valor);
    if (inicio == nullptr) {
        inicio = novo;
        return;
    }

    Node* atual = inicio;
    while (atual->proximo != nullptr) {
        atual = atual->proximo;
    }
    atual->proximo = novo;
}


    // Método para imprimir a lista
    virtual void imprimir() {
        Node* atual = inicio;
        cout << "Lista: \n";
        while (atual != nullptr) {
            cout << atual -> dado;
            cout << " -> ";
            atual = atual->proximo;
        }
        cout << "NULL" << endl;
    }


    Lista* reversa() {
        Lista* lista_reversa = new Lista();
        Node* atual = inicio;
        while (atual != nullptr) {
            lista_reversa->inserir(atual->dado);
            atual = atual->proximo;
        } 
        return lista_reversa;
    }
    Node* get_inicio() {
        return inicio;
    }
};

class MatrizTriangularInferior : public MatrizQuadrada {
private:
    Lista** listas;

public:
    MatrizTriangularInferior(int n) : MatrizQuadrada(n) {
        listas = new Lista*[n];
        for (int i = 0; i < n; ++i) {
            listas[i] = new Lista();
            for (int j = 0; j <= i; ++j) {
                listas[i]->inserir_final(0);  // <--- cria os nós acessáveis
            }
        }        
    }


    ~MatrizTriangularInferior() override {
    for (int i = 0; i < getLinhas(); i++) {
        delete listas[i];
    }
    delete[] listas;
}

    // Método para preencher a matriz (somente a parte triangular inferior)
    virtual void preencher(const string& entrada) {
        string limpa = limparString(entrada);  // usa método da classe base
        stringstream ss(limpa);
        string numero;
        int count = 0;

        for (int i = 0; i < linhas; i++) {
            Lista* auxiliar = new Lista();
            for (int j = 0; j < linhas; j++) {
                if (!getline(ss, numero, ',')) {
                    cout << "Erro: dados insuficientes para preencher matriz." << endl;
                    return;
                }
                float valor = stof(numero);
                if (j <= i) {
                    auxiliar->inserir(valor);
                }
                else if (valor != 0) {
                    cout << "Não é triangular";
                    return ;
                }
            }
            listas[i] = auxiliar->reversa();
            delete(auxiliar);
        }
    }

    float getDado(int linha, int coluna) const override{
        if (coluna > linha) return 0;
        Node* atual = listas[linha]->get_inicio();
        for (int i = 0; i < coluna; i++) {
            atual = atual->proximo;
        }
        return atual->dado;
        }

    virtual void alterar(int linha, int coluna, float valor) override {
        if (coluna > linha) {
            cout << "Erro: tentativa de alterar parte nula de matriz triangular.\n";
            return;
        }

        Node* atual = listas[linha] ? listas[linha]->get_inicio() : nullptr;

        int contador = 0;
        while (contador < coluna && atual != nullptr) {
            atual = atual->proximo;
            contador++;
        }

        if (atual == nullptr) {
            cout << "Erro: posição inválida na lista na linha " << linha << ", coluna " << coluna << endl;
            return;
        }

        atual->dado = valor;
    }

    void imprimir() {
        cout <<nome << " Matriz Triangular Inferior:\n" << linhas << "x" << colunas << ":\n";
         // Imprime a matriz triangular inferior
        for (int i = 0; i < getLinhas(); i++) {
            Node* atual = listas[i]->get_inicio();
            for (int j = 0; j < getColunas(); j++) {
                if (j > i) {
                    cout << "0 ";
                } else {
                    if (atual != nullptr) {
                        cout << atual->dado << " ";
                        atual = atual->proximo;
                    } else {
                        cout << "0 ";  // caso raro de lista incompleta
                    }
                }
            }
            cout << endl;
        }
    }
    float determinante() override {
        // Determinante de matriz triangular inferior é o produto dos elementos da diagonal
        float det = 1;
        for (int i = 0; i < getLinhas(); i++) {
            det *= getDado(i, i);
        }
        return det;
    }
};

class MatrizTriangularSuperior : public MatrizQuadrada {
private:
    Lista** listas;
public:
    MatrizTriangularSuperior(int n) : MatrizQuadrada(n) {
        listas = new Lista*[n];
        for (int i = 0; i < n; ++i) {
            listas[i] = new Lista();
            for (int j = n; j >= i; --j) {
                listas[i]->inserir_final(0);  // <--- cria os nós acessáveis
            }
        }        
    }


    ~MatrizTriangularSuperior() override {
    for (int i = 0; i < getLinhas(); i++) {
        delete listas[i];
    }
    delete[] listas;
}

    // Método para preencher a matriz (somente a parte triangular inferior)
    virtual void preencher(const string& entrada) {
        string limpa = limparString(entrada);  // usa método da classe base
        stringstream ss(limpa);
        string numero;
        int count = 0;

        for (int i = 0; i < linhas; i++) {
            Lista* auxiliar = new Lista();
            for (int j = 0; j < linhas; j++) {
                if (!getline(ss, numero, ',')) {
                    cout << "Erro: dados insuficientes para preencher matriz." << endl;
                    return;
                }
                float valor = stof(numero);
                if (j >= i) {
                    auxiliar->inserir(valor);
                }
                else if (valor != 0) {
                    cout << "Não é triangular";
                    return ;
                }
            }
            listas[i] = auxiliar->reversa();
            delete(auxiliar);
        }
    }

    float getDado(int linha, int coluna) const override{
        if (coluna < linha) return 0;
        Node* atual = listas[linha]->get_inicio();
        for (int j = linha; j < coluna; j++) {
            atual = atual->proximo;
        }
        return atual->dado;
        }

    virtual void alterar(int linha, int coluna, float valor) override {
        if (coluna < linha) {
            cout << "Erro: tentativa de alterar parte nula de matriz triangular.\n";
            return;
        }

        Node* atual = listas[linha] ? listas[linha]->get_inicio() : nullptr;

        int contador = linha;
        while (contador < coluna && atual != nullptr) {
            atual = atual->proximo;
            contador++;
        }

        if (atual == nullptr) {
            cout << "Erro: posição inválida na lista na linha " << linha << ", coluna " << coluna << endl;
            return;
        }

        atual->dado = valor;
    }

    void imprimir() {
        cout << nome << " Matriz Triangular Superior:\n" << linhas << "x" << colunas << ":\n";
         // Imprime a matriz triangular superior
        for (int i = 0; i < getLinhas(); i++) {
            Node* atual = listas[i]->get_inicio();
            for (int j = 0; j < getColunas(); j++) {
                if (j < i) {
                    cout << "0 ";
                } else {
                    if (atual != nullptr) {
                        cout << atual->dado << " ";
                        atual = atual->proximo;
                    } else {
                        cout << "0 ";  // caso raro de lista incompleta
                    }
                }
            }
            cout << endl;
        }
    }
    float determinante() override {
        // Determinante de matriz triangular inferior é o produto dos elementos da diagonal
        float det = 1;
        for (int i = 0; i < getLinhas(); i++) {
            det *= getDado(i, i);
        }
        return det;
    }
};

bool eh_inferior (Matriz* matriz){
    if (matriz->getColunas() != matriz->getLinhas()) {
        return false;
    };
    int ordem = matriz->getLinhas();
    for (int i = 0; i< ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            if (j>i and matriz->getDado(i, j) != 0) {
                return false;
            } 
        }
    }
    return true;
}
bool eh_superior (Matriz* matriz){
    if (matriz->getColunas() != matriz->getLinhas()) {
        return false;
    };
    int ordem = matriz->getLinhas();
    for (int i = 0; i< ordem; i++) {
        for (int j = 0; j < i; j++) {
            if (matriz->getDado(i, j) != 0) {
                return false;
            } 
        }
    }
    return true;
}
Matriz* operator+(Matriz& A, Matriz& B) {
    int lin = A.getLinhas();
    int col = A.getColunas();

    if (lin != B.getLinhas() || col != B.getColunas()) {
        cout << "Erro: Matrizes com dimensões incompatíveis." << endl;
        return new Matriz(0, 0);
    }

    // Verifica se é quadrada
    if (lin == col) {
        // Primeiro calcula a soma em uma MatrizQuadrada temporária
        MatrizQuadrada* soma = new MatrizQuadrada(lin);
        for (int i = 0; i < lin; i++) {
            for (int j = 0; j < col; j++) {
                soma->alterar(i, j, A.getDado(i,j) + B.getDado(i,j));
            }
        }


        if (eh_inferior(soma)) {
            MatrizTriangularInferior* triang = new MatrizTriangularInferior(lin);
            for (int i = 0; i < lin; i++) {
                for (int j = 0; j <= i; j++) {
                    triang->alterar(i, j, soma->getDado(i, j));
                }
            }
            delete soma; // limpa a intermediária
            return triang;
        }
        if (eh_superior(soma)) {
            MatrizTriangularSuperior* triang = new MatrizTriangularSuperior(lin);
            for (int i = 0; i < lin; i++) {
                for (int j = i; j < col; j++) {
                    triang->alterar(i, j, soma->getDado(i, j));
                }
            }
            delete soma; // limpa a intermediária
            return triang;
        }

        // Caso não seja triangular inferior
        return soma;
    }

    // Caso geral (não quadrada)
    Matriz* C = new Matriz(lin, col);
    for (int i = 0; i < lin; i++)
        for (int j = 0; j < col; j++)
            C->alterar(i,j, A.getDado(i,j) + B.getDado(i,j));

    return C;
}

Matriz* operator-(Matriz& A, Matriz& B) {
        int lin = A.getLinhas();
    int col = A.getColunas();

    if (lin != B.getLinhas() || col != B.getColunas()) {
        cout << "Erro: Matrizes com dimensões incompatíveis." << endl;
        return new Matriz(0, 0);
    }

    // Verifica se é quadrada
    if (lin == col) {
        // Primeiro calcula a soma em uma MatrizQuadrada temporária
        MatrizQuadrada* soma = new MatrizQuadrada(lin);
        for (int i = 0; i < lin; i++) {
            for (int j = 0; j < col; j++) {
                soma->alterar(i, j, A.getDado(i,j) - B.getDado(i,j));
            }
        }


        if (eh_inferior(soma)) {
            MatrizTriangularInferior* triang = new MatrizTriangularInferior(lin);
            for (int i = 0; i < lin; i++) {
                for (int j = 0; j <= i; j++) {
                    triang->alterar(i, j, soma->getDado(i, j));
                }
            }
            delete soma; // limpa a intermediária
            return triang;
        }
        if (eh_superior(soma)) {
            MatrizTriangularSuperior* triang = new MatrizTriangularSuperior(lin);
            for (int i = 0; i < lin; i++) {
                for (int j = i; j < col; j++) {
                    triang->alterar(i, j, soma->getDado(i, j));
                }
            }
            delete soma; // limpa a intermediária
            return triang;
        }

        // Caso não seja triangular inferior
        return soma;
    }

    // Caso geral (não quadrada)
    Matriz* C = new Matriz(lin, col);
    for (int i = 0; i < lin; i++)
        for (int j = 0; j < col; j++)
            C->alterar(i,j, A.getDado(i,j) - B.getDado(i,j));

    return C;
}

Matriz* operator*(Matriz& A, float escalar) {
    int col_A = A.getColunas();
    int lin_A = A.getLinhas();
    if (lin_A == col_A) {
        return new MatrizQuadrada([&]{
            MatrizQuadrada* C = new MatrizQuadrada(lin_A);
            for (int i = 0; i < lin_A; i++)
                for (int j = 0; j < col_A; j++)
                    C->alterar(i,j, A.getDado(i,j)* escalar);
            return *C;
        }());
    }
    Matriz* C = new Matriz(lin_A, col_A);
    for (int i = 0; i < lin_A; i++) {
        for (int j = 0; j < col_A; j++) {
            C->alterar(i,j, A.getDado(i,j) * escalar);
        }
    }
    return C;
};

Matriz* operator *(Matriz& A, Matriz& B) {
    int lin_A = A.getLinhas();
    int col_A = A.getColunas();
    int lin_B = B.getLinhas();
    int col_B = B.getColunas();
    if (col_A != lin_B) {
        cout << "Dimensões incompatíveis para produto de matrizes"<< endl;
        return nullptr;
    }
    if (lin_A == col_B) {
        // Se A é quadrada, cria uma MatrizQuadrada para o resultado
        MatrizQuadrada* C = new MatrizQuadrada(lin_A);
        for (int i = 0; i < lin_A; i++) {
            for (int j = 0; j < col_B; j++) {
                float contador = 0;
                for (int k = 0; k < col_A; k++) {
                    contador += A.getDado(i,k) * B.getDado(k, j);
                }
                C->alterar(i, j, contador);
            }
        }
        if (eh_inferior(C)) {
            MatrizTriangularInferior* triang = new MatrizTriangularInferior(lin_A);
            for (int i = 0; i < lin_A; i++) {
                for (int j = 0; j <= i; j++) {
                    triang->alterar(i, j, C->getDado(i, j));
                }
            }
            delete C; // limpa a intermediária
            return triang;
        }
        return C;
        if (eh_superior(C)) {
            MatrizTriangularSuperior* triang = new MatrizTriangularSuperior(lin_A);
            for (int i = 0; i < lin_A; i++) {
                for (int j = i; j < col_B; j++) {
                    triang->alterar(i, j, C->getDado(i, j));
                }
            }
            delete C; // limpa a intermediária
            return triang;
        }
    }
    Matriz* C = new Matriz(lin_A, col_B);
    for (int i = 0; i < lin_A; i++) {
        for (int j = 0; j < col_B; j++) {
            float contador = 0;
            for (int k = 0; k < col_A; k++) {
                contador += A.getDado(i,k) * B.getDado(k, j);
            }
            C->alterar(i, j, contador);
        }
    }
    return C;
}

Matriz* transposicao(Matriz& A) {
    int lin_A = A.getLinhas();
    int col_A = A.getColunas();
    if (lin_A == col_A) {
        if (eh_inferior(&A)) {
            MatrizTriangularSuperior* C = new MatrizTriangularSuperior(lin_A);
            for (int i = 0; i < col_A; i++) {
                for (int j = i; j < col_A; j++) {
                    C->alterar(i,j, A.getDado(j,i));
                }
            }
            return C;
        }
        if (eh_superior(&A)) {
            MatrizTriangularInferior* C = new MatrizTriangularInferior(lin_A);
            for (int i = 0; i < col_A; i++) {
                for (int j = 0; j <= i; j++) {
                    C->alterar(i,j, A.getDado(j,i));
                }
            }
            return C;
        }
        MatrizQuadrada* C = new MatrizQuadrada(lin_A);
        for (int i = 0; i < col_A; i++) {
            for (int j = 0; j < lin_A; j++) {
                C->alterar(i,j, A.getDado(j,i));
            }
        }
        return C;
    }
    Matriz* C = new Matriz(col_A, lin_A);
    for (int i = 0; i < col_A; i++) {
        for (int j = 0; j < lin_A; j++) {
            C->alterar(i,j, A.getDado(j,i));
        }
    }
    return C;
}

string lerArquivoParaString(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    string linha, resultado;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir arquivo: " << nomeArquivo << endl;
        return "";
    }

    while (getline(arquivo, linha)) {
        resultado += linha + ",";  // separa os elementos com vírgula
    }

    // remove última vírgula extra, se houver
    if (!resultado.empty() && resultado.back() == ',') {
        resultado.pop_back();
    }

    return resultado;
}

Matriz* pergunta_cria() {
    int linhas, colunas;
    cout << "Digite o número de linhas: ";
    cin >> linhas;
    cout << "Digite o número de colunas: ";
    cin >> colunas;
    cin.ignore(); // Limpa o buffer do cin

    Matriz* matriz = nullptr;
    if (linhas == colunas) {
        matriz = new MatrizQuadrada(linhas);  // ou (linhas, colunas) se for o caso
    } else {
        matriz = new Matriz(linhas, colunas);
    }

    string entrada;
    cout << "Digite a matriz no formato [[a,b,c],[d,e,f]]:\n";
    getline(cin, entrada);

    matriz->preencher(entrada);
    if (eh_inferior(matriz)) {
        MatrizTriangularInferior* novamatriz = new MatrizTriangularInferior(linhas);
        novamatriz ->preencher(entrada);
        delete matriz;
        return novamatriz;
    }
    if (eh_superior(matriz)) {
        MatrizTriangularSuperior* novamatriz = new MatrizTriangularSuperior(linhas);
        novamatriz ->preencher(entrada);
        delete matriz;
        return novamatriz;
    }
    cout << "Qual o nome da matriz? ";
    string nome;
    getline(cin, nome);
    matriz->setNome(nome);
    return matriz;
}

int main() {
    vector<Matriz*> matrizes; // Armazena ponteiros para matrizes criadas

    int opcao;
    do {
        cout << "\n===== CALCULADORA DE MATRIZES =====" << endl;
        cout << "1. Criar matriz" << endl;
        cout << "2. Somar duas matrizes" << endl;
        cout << "3. Subtrair duas matrizes" << endl;
        cout << "4. Multiplicar duas matrizes" << endl;
        cout << "5. Multiplicar matriz por escalar" << endl;
        cout << "6. Transpor matriz" << endl;
        cout << "7. Traco (matriz quadrada)" << endl;
        cout << "8. Determinante (matriz quadrada)" << endl;
        cout << "9. Ver todas as matrizes" << endl;
        cout << "10. Deletar matriz" << endl;
        cout << "11. Alterar matriz" << endl;
        cout << "12. Apagar todas as matrizes" << endl;
        cout << "13. Ler matriz de arquivo" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();

        if (opcao == 1) {
            Matriz* m = (pergunta_cria());
            matrizes.push_back(m);
            m->imprimir();
            cout << "Sua matriz está salva. Caso queira fazer alguma conta com ela e não saiba seu índice, escolha 10" << endl;
        }
        else if (opcao == 2 || opcao == 3 || opcao == 4) {
            int i1, i2;
            cout << "Índice da primeira matriz: "; cin >> i1;
            cout << "Índice da segunda matriz: "; cin >> i2;

            if (i1 >= matrizes.size() || i2 >= matrizes.size()) {
                cout << "Índice inválido." << endl;
                continue;
            }

            Matriz* res = nullptr;
            if (opcao == 2)
                res = (*matrizes[i1] + *matrizes[i2]);
            else if (opcao == 3)
                res = (*matrizes[i1] - *matrizes[i2]);
            else
                res = (*matrizes[i1] * *matrizes[i2]);

            matrizes.push_back(res);
            cout << "Resultado:\n";
            res->imprimir();
        }
        else if (opcao == 5) {
            int i; float esc;
            cout << "Índice da matriz: "; cin >> i;
            cout << "Escalar: "; cin >> esc;

            if (i >= matrizes.size()) {
                cout << "Índice inválido." << endl;
                continue;
            }

            Matriz* res = (*matrizes[i] * esc);
            matrizes.push_back(res);
            cout << "Resultado:\n";
            res->imprimir();
        }
        else if (opcao == 6) {
            int i;
            cout << "Índice da matriz: "; cin >> i;
            if (i >= matrizes.size()) {
                cout << "Índice inválido." << endl;
                continue;
            }

            Matriz* res = transposicao(*matrizes[i]);
            matrizes.push_back(res);
            cout << "Transposta:\n";
            res->imprimir();
        }
        else if (opcao == 7 || opcao == 8) {
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

            if (opcao == 7)
                cout << "Traço: " << q->traco() << endl;
            else
                cout << "Determinante: " << q->determinante() << endl;
        }
        else if (opcao == 9) {
            for (int i = 0; i < matrizes.size(); i++) {
                cout << "[" << i << "]\n";
                matrizes[i]->imprimir();
            }
        }
        else if (opcao == 10) {
            int i;
            cout << "Índice da matriz a ser deletada: "; cin >> i;
            if (i >= matrizes.size()) {
                cout << "Índice inválido." << endl;
                continue;
            }
            delete matrizes[i]; // Libera a memória da matriz
            matrizes.erase(matrizes.begin() + i); // Remove o ponteiro do vetor
            cout << "Matriz deletada com sucesso." << endl;
        }
        else if (opcao == 11) {
            int i, linha, coluna;
            float valor;
            cout << "Índice da matriz: "; cin >> i;
            if (i >= matrizes.size()) {
                cout << "Índice inválido." << endl;
                continue;
            }
            cout << "Linha: "; cin >> linha;
            cout << "Coluna: "; cin >> coluna;
            cout << "Valor: "; cin >> valor;

            if (linha < 0 || linha >= matrizes[i]->getLinhas() || coluna < 0 || coluna >= matrizes[i]->getColunas()) {
                cout << "Posição inválida." << endl;
                continue;
            }

            matrizes[i]->alterar(linha, coluna, valor);
            cout << "Matriz alterada com sucesso." << endl;
        }
        else if (opcao == 12) {
            for (Matriz* m : matrizes) {
                delete m; // Libera a memória de cada matriz
            }
            matrizes.clear(); // Limpa o vetor
            cout << "Todas as matrizes foram apagadas." << endl;
        }
        else if (opcao != 0) {
            cout << "Opção inválida." << endl;
        }
        else if (opcao == 13) {
            string nome_arquivo;
            cout << "Digite o nome do arquivo: ";
            cin >> nome_arquivo;
            cin.ignore(); // Limpa o buffer do cin

            string conteudo = lerArquivoParaString(nome_arquivo);
            Matriz* m = pergunta_cria(); // Simula a criação de uma matriz
            m->preencher(conteudo);
            cout << "Qual o nome da matriz? ";
            string nome;
            getline(cin, nome);
            m->setNome(nome);
            if (eh_inferior(m)) {
                MatrizTriangularInferior* triang = new MatrizTriangularInferior(m->getLinhas());
                triang->preencher(conteudo);
                delete m; // limpa a intermediária
                m = triang;
            }
            if (eh_superior(m)) {
                MatrizTriangularSuperior* triang = new MatrizTriangularSuperior(m->getLinhas());
                triang->preencher(conteudo);
                delete m; // limpa a intermediária
                m = triang;
            }
            matrizes.push_back(m);
            cout << "Matriz lida do arquivo e salva com sucesso." << endl;
        }
    } while (opcao != 0);

    // Limpeza de memória
    for (Matriz* m : matrizes) {
        delete m;
    }

    cout << "Programa encerrado." << endl;
    return 0;
}
