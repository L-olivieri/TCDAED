#from abc import ABC, abstractmethod

class Matriz_Geral():
    def __init__(self, m:int, n:int, valores:list=[]):
        """
        Inicializa uma matriz m x n
        
        Args:
            m: número de linhas
            n: número de colunas
            valores: lista com os valores da matriz
            
        Raises:
            ValueError: Se as dimensões não forem positivas ou se o número de valores não corresponder
            TypeError: Se os valores não forem numéricos
        """
        try:
            if m <= 0 or n <= 0:
                raise ValueError("As dimensões da matriz devem ser positivas")
            
            self.m = m
            self.n = n

            # Verifica se a estrutura de valores está correta
            if len(valores) > m: #verifica se o numero de linhas corresponde a dimensao m
                raise ValueError("Número de linhas não corresponde à dimensão m")
                
            for linha in valores:
                if len(linha) > n: # verifica se o numero de coluinas corresponde a dimensao n
                    raise ValueError("Número de colunas não corresponde à dimensão n")
                    
                for elemento in linha:
                    if not isinstance(elemento, (int, float)): # verifica se o elemento eh um numero
                        raise TypeError("Todos os elementos devem ser números")
                
            self.valores = valores

        except ValueError as e:
            print(f"Erro de valor: {e}")
            raise

        except TypeError as e:
            print(f"Erro de tipo: {e}")
            raise
        
    def set_Valores(self, novos_valores:list):
        """Define novos valores para a matriz, com verificação de dimensões"""

        try:
            if len(novos_valores) != self.m:
                raise ValueError("Número de linhas não corresponde à dimensão m")
            
            for linha in novos_valores:
                if len(linha) > self.n:
                    raise ValueError("Número de colunas não corresponde à dimensão n")
            
            self.valores = novos_valores

        except ValueError as e:
            print(f"Erro ao definir valores: {e}")
            raise

    @classmethod
    def Soma_Subtracao(cls, A, B, eh_soma:bool):
        try:
            if not(A.n == B.n and A.m == B.m):
                raise ValueError("Matrizes não possuem as mesmas dimensões")
            
            #Valores V da Matriz_Geral M
            V = []

            for j in range(A.n):
                #Vetor j-ésimo a da Matriz_Geral A
                a:list = A.valores[j]

                #Vetor j-ésimo b da Matriz_Geral B
                b:list = B.valores[j]

                #Vetor j-ésimo C da Matriz_Geral M (vazio)
                C:list = []
                    
                for i in range(len(a)):
                    c:float = 0
                    #Valor i-ésimo c do j-ésimo vetor da Matriz_Geral M (resultante da soma dos i-ésimos valores dos j-ésimos vetores das Matriz_Gerales A e B)
                    if a[i] != 0 and b[i] != 0:
                        if eh_soma:
                            c = a[i] + b[i]
                        else:
                            c = a[i] - b[i]

                        #Vetor j-ésimo C da Matriz_Geral M adiciona o i-ésimo valor c
                        if c != 0:
                            C.append(c)
                
                    #Valores V adiciona vetor j-ésimo C da Matriz_Geral M
                    V.append(C)
            
                #Matriz_Geral M adiciona os valores V
                #M.set_Valores(V)
                return V
            
        except ValueError as e:
            print(f"Erro na soma/subtração: {e}")
            raise
 
    @classmethod
    def Multiplicacao_Matricial(cls, A, B):
        try:
            if not(A.m == B.n):
                raise ValueError("Matrizes incompatíveis para multiplicação")
            
            #Valores V da Matriz_Geral M
            V = []

            #Matriz_Geral M resultante
            #M = Matriz_Geral(A.n, B.m, V)

            #Para cada vetor j-ésimo da Matriz_Geral A
            for j in range(A.m):

                #Vetor j-ésimo C da Matriz_Geral M (vazio)
                C:list = []

                #Para cada valor i-ésimo do vetor j-ésimo da Matriz_Geral A
                #E para cada valor j-ésimo dos vetores i-ésimos da Matriz_Geral B
                for k in range(B.n):
                    soma:float = 0
                    for i in range(len(A.valores[j])):
                        if A.valores[j][i] != 0 or B.valores[i][k] != 0:
                            soma += A.valores[j][i] * B.valores[i][k]
                    if soma != 0:
                        C.append(soma)
                V.append(C)
            #M.set_Valores(V)
            return V

        except ValueError as e:
            print(f"Erro na multiplicação: {e}")
            raise

    def Multiplicacao_por_Escalar(self, k:float):
        try:
            #Valores V da Matriz_Geral resultante B
            V = []

            #B = Matriz_Geral(self.m, self.n, V)

            for vetor in self.valores:
                elementos = []
                for elemento in vetor:
                    if elemento != 0:
                        elemento = k*elemento
                        elementos.append(elemento)
                V.append(elementos)
            #B.set_Valores(V)
            return V

        except TypeError as e:
            print(f"Erro na multiplicação por escalar: {e}")
            raise

    def Transposicao(self):
        try:
            #fixa a posição i, varia o vetor j

            #Valores V da Matriz_Geral resultante M
            V = []

            for i in range(self.m):
                C:list = []
                for j in range(self.n):
                    C.append(self.valores[j][i])
                V.append(C)
            return V

        except IndexError as e:
            print(f"Erro na transposição: {e}")
            raise



class Quadrada(Matriz_Geral):
    def __init__(self, n:int, valores:list=[]):
        try:
            if n <= 0:
                raise ValueError("Dimensão deve ser positiva")
            super().__init__(n, n, valores)
        
        except ValueError as e:
            print(f"Erro na matriz quadrada: {e}")
            raise

    def set_Valores(self, novos_valores:list):
        self.valores = novos_valores

    def Calcular_Traço(self):
        try:
            traco = 0
            for i in range(len(self.valores)):
                traco += self.valores[i][i]
            return traco
        
        except IndexError as e:
            print(f"Erro ao calcular traço: {e}")
            raise



class Triangular_Inf(Quadrada):
    def __init__(self, n, valores=[[]]):
        try:
            for i in range(n):
                if len(valores[i]) != i+1:
                     ValueError("Matriz não é triangular inferior")
            super().__init__(n, valores)
                    
        except ValueError as e:
            print(f"Erro na triangular inferior: {e}")
            raise

    @classmethod
    def Soma_Subtracao(cls, A, B, eh_soma:bool):
        try:
            if not(A.n == B.n and A.m == B.m):
                raise ValueError("Matrizes não possuem as mesmas dimensões")

            #Valores V da Matriz_Geral M
            V = []

            for j in range(A.n):
                #Vetor j-ésimo a da Matriz_Geral A
                a:list = A.valores[j]

                #Vetor j-ésimo b da Matriz_Geral B
                b:list = B.valores[j]

                #Vetor j-ésimo C da Matriz_Geral M (vazio)
                C:list = []
                
                if len(a) < A.n:
                    for k in range(A.n - len(a)):
                        a.append(0)

                elif len(b) < B.n:
                    for k in range(B.n - len(b)):
                        b.append(0)

                for i in range(A.n):
                    c:float = 0
                    #Valor i-ésimo c do j-ésimo vetor da Matriz_Geral M (resultante da soma dos i-ésimos valores dos j-ésimos vetores das Matriz_Gerales A e B)
                    if eh_soma:
                        c = a[i] + b[i]
                    else:
                        c = a[i] - b[i]

                    #Vetor j-ésimo C da Matriz_Geral M adiciona o i-ésimo valor c
                    if c != 0:
                        C.append(c)
            
                #Valores V adiciona vetor j-ésimo C da Matriz_Geral M
                V.append(C)
        
            return V
         
        except ValueError as e:
            print(f"Erro na soma/subtração triangular: {e}")
            raise

    def Calcular_Determinante(self):
        try:
            det = 0
            for i in range(len(self.valores)):
                det *= self.valores[i][i]
            return det
        
        except IndexError as e:
            print(f"Erro ao calcular determinante: {e}")
            raise



class Triangular_Sup(Quadrada):
    def __init__(self, n, valores):
        try:
            for i in range(-1, -n, -1):
                if len(valores[i]) != (-1)*i:
                    raise ValueError("Matriz não é triangular superior")
            super().__init__(n, valores)
         
                
        except ValueError as e:
            print(f"Erro na triangular superior: {e}")
            raise

    @classmethod
    def Soma_Subtracao(cls, A, B, eh_soma:bool):
        try:
            if not(A.n == B.n and A.m == B.m):
                raise ValueError("Matrizes não possuem as mesmas dimensões")
            
            #Valores V da Matriz_Geral M
            V = []
            
            for j in range(A.n):
                #Vetor j-ésimo a da Matriz_Geral A
                a:list = A.valores[j]
                
                #Vetor j-ésimo b da Matriz_Geral B
                b:list = B.valores[j]
                
                #Vetor j-ésimo C da Matriz_Geral M (vazio)
                C:list = []
                    
                if len(a) < A.n:
                    for k in range(A.n - len(a)):
                        a.insert(0, 0)

                elif len(b) < B.n:
                    for k in range(B.n - len(b)):
                        b.insert(0, 0)

                for i in range(A.n):
                    c:float = 0
                        #Valor i-ésimo c do j-ésimo vetor da Matriz_Geral M (resultante da soma dos i-ésimos valores dos j-ésimos vetores das Matriz_Gerales A e B)
                    if eh_soma:
                        c = a[i] + b[i]
                    else:
                        c = a[i] - b[i]

                        #Vetor j-ésimo C da Matriz_Geral M adiciona o i-ésimo valor c
                    if c != 0:
                        C.append(c)
                
                #Valores V adiciona vetor j-ésimo C da Matriz_Geral M
                V.append(C)
            
            return V
            
        except ValueError as e:
            print(f"Erro na soma/subtração triangular: {e}")
            raise



class Diagonal(Quadrada):
    def __init__(self, n, valores=[[]]):
        """
        Inicializa uma matriz diagonal n x n 
        
        Parâmetros:
            n: tamanho da matriz (n x n)
            valores: lista com os valores da diagonal principal
        
        Raises:
            ValueError: Se o tamanho não for positivo ou se o número de valores não corresponder a n
            TypeError: Se os valores não forem numéricos
        """
        
        if not isinstance(n, int) or n <= 0: # n  NAO eh um inteiro ou N < 0 
            raise ValueError("O tamanho da matriz deve ser um número inteiro positivo")
        
        # verifica se todos sao numeros
        for valor in valores[0]:
            if not isinstance(valor, (int, float)):
                raise TypeError("Todos os valores devem ser numéricos")

        # Chama o construtor da classe pai
        super().__init__(n, valores)
    
    def set_valores(self, novos_valores):
        """Define novos valores para a diagonal principal"""

        # Validação
        if len(novos_valores) != self.n:
            raise ValueError(f"Devem ser fornecidos exatamente {self.n} valores")
        
        for valor in novos_valores:
            if not isinstance(valor, (int, float)):
                raise TypeError("Todos os valores devem ser números")
        
        # Atualiza a diagonal
        self.valores = novos_valores
    
    @classmethod
    def Soma_Subtracao(cls, A, B, eh_soma:bool):
        """Soma duas matrizes diagonais"""
        # Validação
        if not isinstance(A, Diagonal) or not isinstance(B, Diagonal):
            raise TypeError("Ambas as matrizes devem ser diagonais")
        
        if A.n != B.n:
            raise ValueError("As matrizes devem ter o mesmo tamanho")
        
        # Calcula a nova diagonal
        nova_diagonal = []
        for i in range(A.n):
            if eh_soma:
                c = (A.valores[0][i] + B.valores[0][i])
            else:
                c = (A.valores[0][i] - B.valores[0][i])

            if c != 0:
                nova_diagonal.append(c)

        return nova_diagonal

    @classmethod
    def Multiplicacao_Matricial(cls, A, B):
        """Multiplica duas matrizes diagonais"""
        # Validação
        if not isinstance(A, Diagonal) or not isinstance(B, Diagonal):
            raise TypeError("Ambas as matrizes devem ser diagonais")
        if A.n != B.n:
            raise ValueError("As matrizes devem ter o mesmo tamanho")
        
        # Calcula a nova diagonal
        nova_diagonal = []
        for i in range(A.n):
            c = (A.valores[0][i] * B.valores[0][i])

            if c != 0:
                nova_diagonal.append(c)

        return nova_diagonal

    def Multiplicacao_por_Escalar(self, k):
        """Multiplica a matriz por um escalar"""
        if not isinstance(k, (int, float)):
            raise TypeError("O escalar deve ser um número!")
        
        nova_diagonal = []
        for valor in self.valores[0]:
            c = (valor * k)
            if c != 0:
                nova_diagonal.append(c)
        
        return nova_diagonal
    
    def __str__(self):
        """Representação string da matriz diagonal"""
        return f"Matriz Diagonal {self.n}x{self.n} com valores: {self.diagonal}"

    def Transpoicao(self):
        """Retorna a matriz transposta (que é ela mesma para diagonais)"""
        return self
    
    def Calcular_Determinante(self):
        """Calcula o determinante"""
        determinante = 1
        for valor in self.valores[0]:
            determinante *= valor
        return determinante



def read_matriz(path):
    """
    Lê uma matriz de um arquivo.
    O arquivo deve conter uma matriz onde cada linha é uma lista de números separados por espaços.
    """
    with open(path, 'r') as file:
        M = []
        for line in file:
            # col = list(map(float, line.strip().split()))
            col = [int(x) if x.isdigit() or (x[0] == '-' and x[1:].isdigit()) else float(x) for x in line.strip().split()]
            M.append(col)
    return M

def write_matriz(M, path):
    """
    Escreve uma matriz em um arquivo.
    Cada linha da matriz será escrita em uma linha do arquivo, com os números separados por espaços.
    """
    with open(path, 'r', encoding='utf-8') as file:
        content = file.read()
        i = content.count('Matriz')
    with open(path, 'a', encoding='utf-8') as file:
        file.write(f"Matriz {i}\n")
        for linha in M:
            file.write(' '.join(map(str, linha)) + '\n')
        file.write('\n')


def delete_matriz(index, path):
    """
    Deleta uma matriz de um arquivo.
    O índice da matriz a ser deletada é passado como parâmetro.
    """
    with open(path, 'r', encoding='utf-8') as file:
        content = file.read()
        i = content.count('Matriz')
    if index < 0 or index >= i:
        raise IndexError("Índice da matriz inválido.")
    with open(path, 'w', encoding='utf-8') as file:
        lines = content.splitlines()
        new_content = []
        matriz_del = False
        for line in lines:
            if line.startswith(f"Matriz {index}"):
               matriz_del = True
            elif line.startswith("Matriz") and matriz_del:
                matriz_del = False
            if not matriz_del:
                new_content.append(line)
        i = 0
        for index,matriz in enumerate(new_content):
            if "Matriz" in matriz:
                matriz_new = matriz[:7] + str(i)
                new_content[index] = matriz_new
                i+=1
        file.write('\n'.join(new_content) + '\n')
