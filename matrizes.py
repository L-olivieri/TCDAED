#from abc import ABC, abstractmethod

class Matriz_Geral():
    def __init__(self, m:int, n:int, valores:list=[]):
        self.m = m
        self.n = n
        self.valores = valores
    
    def set_Valores(self, novos_valores:list):
        self.valores = novos_valores

    @classmethod
    def Soma_Subtracao(cls, A, B, eh_soma:bool):
        if not(A.n == B.n and A.m == B.m):
            print("Matrizes não possuem as mesmas dimensões!")
            M = []
            return M

        else:
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

    @classmethod
    def Multiplicacao_Matricial(cls, A, B):
        if not(A.m == B.n):
            print("As Matrizes são incompatíveis!")
            #M = Matriz_Geral(0, 0, [])
            M = []
            return M
        
        else:
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

    def Multiplicacao_por_Escalar(self, k:float):
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
    
    def Transposicao(self):
        #fixo a posição i, vario o vetor j

        #Valores V da Matriz_Geral resultante M
        V = []

        for i in range(self.m):
            C:list = []
            for j in range(self.n):
                C.append(self.valores[j][i])
            V.append(C)
        return V



class Quadrada(Matriz_Geral):
    def __init__(self, n:int, valores:list=[]):
        super().__init__(n, n, valores)

    def set_Valores(self, novos_valores:list):
        self.valores = novos_valores

    def Calcular_Traço(self):
        traco = 0
        for i in range(len(self.valores)):
            traco += self.valores[i][i]
        return traco



class Triangular_Inf(Quadrada):
    def __init__(self, n, valores):
        super().__init__(n, valores)

    @classmethod
    def Soma_Subtracao(cls, A, B, eh_soma:bool):
        if not(A.n == B.n and A.m == B.m):
            print("Matrizes não possuem as mesmas dimensões!")
            M = []
            return M

        else:
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

    def Calcular_Determinante(self):
        det = 0
        for i in range(len(self.valores)):
            det *= self.valores[i][i]
        return det



class Triangular_Sup(Quadrada):
    def __init__(self, n, valores):
        super().__init__(n, valores)

    @classmethod
    def Soma_Subtracao(cls, A, B, eh_soma:bool):
        if not(A.n == B.n and A.m == B.m):
            print("Matrizes não possuem as mesmas dimensões!")
            M = []
            return M

        else:
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


class Diagonal(Quadrada):
    def __init__(self, n, valores):
        super().__init__(n, n, valores)

