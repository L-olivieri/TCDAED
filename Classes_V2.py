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
            if valores:
                if len(valores) != m: #verifica se o numero de linhas corresponde a dimensao m
                    raise ValueError("Número de linhas não corresponde à dimensão m")
                
                for linha in valores: 
                    if len(linha) != n: # verifica se o nujmero de coluinas corresponde a dimensao n
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
                if len(linha) != self.n:
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

            #Matriz_Geral M resultante
            #M = Matriz_Geral(A.m, A.n, V)

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
        #fixo a posição i, vario o vetor j

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
            super().__init__(n, n, valores)
            if n <= 0:
                raise ValueError("Dimensão deve ser positiva")
        
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
    def __init__(self, n, valores):
        try:
            super().__init__(n, valores)
            for i in range(n):
                for j in range(i+1, n):
                    if self.valores[i][j] != 0:
                        raise ValueError("Matriz não é triangular inferior")
                    
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

            #Matriz_Geral M resultante
            #M = Matriz_Geral(A.m, A.n, V)

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
        
            #Matriz_Geral M adiciona os valores V
            #M.set_Valores(V)
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
         super().__init__(n, valores)
         for i in range(n):
            for j in range(i):
                if self.valores[i][j] != 0:
                    raise ValueError("Matriz não é triangular superior")
                
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

                #Matriz_Geral M resultante
                #M = Matriz_Geral(A.m, A.n, V)

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
            
                #Matriz_Geral M adiciona os valores V
                #M.set_Valores(V)
                return V
            
        except ValueError as e:
            print(f"Erro na soma/subtração triangular: {e}")
            raise



class Diagonal(Quadrada):
    def __init__(self, n, valores):
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
        
        if len(valores) != n: # se o tamanho de valores for diferente do tamanho da matriz
            raise ValueError(f"Devem ser fornecidos exatamente {n} valores para a diagonal")
        
        # verifica se todos sao numeros
        for valor in valores:
            if not isinstance(valor, (int, float)):
                raise TypeError("Todos os valores devem ser numéricos")
        
        #armazena a diagonal
        self.diagonal = []
        for valor in valores:
            self.diagonal.append(valor)
        
        # Constrói a matriz completa para a classe pai
        matriz_completa = self.criar_matriz_completa()
        
        # Chama o construtor da classe pai
        super().__init__(n, matriz_completa) # Aqui a gente so chama nesse momento pra ter certeza que a matriz foi construida antes
    
    def criar_matriz_completa(self):
        """Constrói a matriz completa com zeros fora da diagonal"""
        matriz = []
        
        for i in range(self.n):  # Para cada linha
            linha = []
            
            for j in range(self.n):  # Para cada coluna
                if i == j:  # Se estiver na diagonal
                    linha.append(self.diagonal[i])
                else:  # Fora da diagonal
                    linha.append(0)
            
            matriz.append(linha)
        
        return matriz
    
    def set_valores(self, novos_valores):
        """Define novos valores para a diagonal principal"""

        # Validação
        if len(novos_valores) != self.n:
            raise ValueError(f"Devem ser fornecidos exatamente {self.n} valores")
        
        for valor in novos_valores:
            if not isinstance(valor, (int, float)):
                raise TypeError("Todos os valores devem ser números")
        
        # Atualiza a diagonal
        self.diagonal = []
        for valor in novos_valores:
            self.diagonal.append(valor)
        
        # Atualiza a matriz completa na classe pai
        matriz_completa = self.criar_matriz_completa()
        super().set_Valores(matriz_completa)
    
    def transposicao(self):
        """Retorna a matriz transposta (que é ela mesma para diagonais)"""
        return self
    
    def calcular_determinante(self):
        """Calcula o determinante"""
        determinante = 1
        for valor in self.diagonal:
            determinante *= valor
        return determinante
    
    @classmethod
    def somar(cls, A, B):
        """Soma duas matrizes diagonais"""
        # Validação
        if not isinstance(A, Diagonal) or not isinstance(B, Diagonal):
            raise TypeError("Ambas as matrizes devem ser diagonais")
        if A.n != B.n:
            raise ValueError("As matrizes devem ter o mesmo tamanho")
        
        # Calcula a nova diagonal
        nova_diagonal = []
        for i in range(A.n):
            nova_diagonal.append(A.diagonal[i] + B.diagonal[i])
        
        return cls(A.n, nova_diagonal)
    
    @classmethod
    def multiplicar(cls, A, B):
        """Multiplica duas matrizes diagonais"""
        # Validação
        if not isinstance(A, Diagonal) or not isinstance(B, Diagonal):
            raise TypeError("Ambas as matrizes devem ser diagonais")
        if A.n != B.n:
            raise ValueError("As matrizes devem ter o mesmo tamanho")
        
        # Calcula a nova diagonal
        nova_diagonal = []
        for i in range(A.n):
            nova_diagonal.append(A.diagonal[i] * B.diagonal[i])
        
        return cls(A.n, nova_diagonal)
    
    def multiplicar_por_escalar(self, k):
        """Multiplica a matriz por um escalar"""
        if not isinstance(k, (int, float)):
            raise TypeError("O escalar deve ser um número")
        
        nova_diagonal = []
        for valor in self.diagonal:
            nova_diagonal.append(valor * k)
        
        return Diagonal(self.n, nova_diagonal)
    
    def __str__(self):
        """Representação string da matriz diagonal"""
        return f"Matriz Diagonal {self.n}x{self.n} com valores: {self.diagonal}"


A = Triangular_Inf(3, [
   [1],
   [2, 3],
   [4, 5, 6],
])

B = Quadrada(3, [
    [1, 2, 3],
    [0, 5, 6],
    [2, 5, 7],
])

C = Triangular_Sup(3, [
    [1, 2, 3],
    [0, 4, 5],
    [0, 0, 6],
])


M = Matriz_Geral(3, 3)
M.set_Valores(Triangular_Sup.Soma_Subtracao(C, B, True))
print(M.valores)
