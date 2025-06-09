from matrizes import Matriz_Geral, Diagonal, Quadrada, Triangular_Inf, Triangular_Sup

class MatrizManager:
    def __init__(self):
        self.matrizes = []  # Lista de tuplas (nome, objeto_matriz)
        self.backup_file = "matrizes_backup.pkl"
    
    def imprimir_matriz(self, matriz):
        """Retorna representação string de uma matriz"""
        return "\n".join([str(linha) for linha in matriz.valores])
    
    def inserir_matriz_teclado(self):
        """Cria matriz a partir de entrada do usuário"""
        try:
            nome = input("Nome para a matriz: ").strip()
            if any(nome == n for n, _ in self.matrizes):
                print("Nome já existe!")
                return
                
            m = int(input("Número de linhas: "))
            n = int(input("Número de colunas: "))
            
            print(f"Digite os valores da matriz {m}x{n} (linha por linha):")
            valores = []
            for i in range(m):
                linha = list(map(float, input(f"Linha {i+1} (valores separados por espaço): ").split()))
                if len(linha) != n:
                    raise ValueError(f"Linha deve ter {n} elementos")
                valores.append(linha)
            
            matriz = Matriz_Geral(m, n, valores)
            self.matrizes.append((nome, matriz))
            print(f"Matriz '{nome}' adicionada com sucesso!")
            
        except Exception as e:
            print(f"Erro: {e}")

    def inserir_matriz_arquivo(self):
        """Carrega matriz de arquivo"""
        try:
            nome = input("Nome para a matriz: ").strip()
            if any(nome == n for n, _ in self.matrizes):
                print("Nome já existe!")
                return
                
            caminho = input("Caminho do arquivo: ")
            with open(caminho, 'r') as f:
                linhas = f.readlines()
            
            valores = []
            for linha in linhas:
                valores.append(list(map(float, linha.strip().split())))
            
            m = len(valores)
            n = len(valores[0])
            matriz = Matriz_Geral(m, n, valores)
            self.matrizes.append((nome, matriz))
            print(f"Matriz '{nome}' carregada do arquivo!")
            
        except Exception as e:
            print(f"Erro: {e}")

    def inserir_identidade(self):
        """Cria matriz identidade"""
        try:
            nome = input("Nome para a matriz identidade: ").strip()
            if any(nome == n for n, _ in self.matrizes):
                print("Nome já existe!")
                return
                
            n = int(input("Dimensão (n): "))
            valores = [[1.0 if i == j else 0.0 for j in range(n)] for i in range(n)]
            matriz = Diagonal(n, valores)
            self.matrizes.append((nome, matriz))
            print(f"Matriz identidade '{nome}' criada!")
            
        except Exception as e:
            print(f"Erro: {e}")

    def alterar_remover_matrizes(self):
        """Gerencia alteração/remoção de matrizes"""
        if not self.matrizes:
            print("Nenhuma matriz cadastrada!")
            return
            
        self.listar_matrizes()
        try:
            nome = input("Nome da matriz para alterar/remover: ").strip()
            idx = next(i for i, (n, _) in enumerate(self.matrizes) if n == nome)
            
            acao = input("[A]lterar ou [R]emover? ").upper()
            if acao == 'A':
                novo_nome = input(f"Novo nome ({nome}): ").strip()
                if novo_nome and novo_nome != nome:
                    if any(novo_nome == n for n, _ in self.matrizes):
                        print("Nome já existe!")
                    else:
                        _, matriz = self.matrizes[idx]
                        self.matrizes[idx] = (novo_nome, matriz)
                        print(f"Matriz renomeada para '{novo_nome}'")
            elif acao == 'R':
                del self.matrizes[idx]
                print(f"Matriz '{nome}' removida!")
                
        except Exception as e:
            print(f"Erro: {e}")

    def listar_matrizes(self):
        """Lista todas as matrizes com informações"""
        if not self.matrizes:
            print("Nenhuma matriz cadastrada!")
            return
            
        print("\n{:<10} {:<15} {:<10} {}".format("Nome", "Tipo", "Dimensão", "Detalhes"))
        print("-" * 50)
        for nome, matriz in self.matrizes:
            tipo = type(matriz).__name__
            dim = f"{matriz.m}x{matriz.n}"
            detalhes = f"Traço: {matriz.Calcular_Traço()}" if hasattr(matriz, 'Calcular_Traço') else ""
            print(f"{nome:<10} {tipo:<15} {dim:<10} {detalhes}")

    def gravar_backup(self):
        """Salva lista de matrizes em arquivo"""
        try:
            from pickle import dump
            arquivo = input("Nome do arquivo de backup: ").strip() or self.backup_file
            with open(arquivo, 'wb') as f:
                dump(self.matrizes, f)
            print(f"Backup salvo em '{arquivo}'!")
        except Exception as e:
            print(f"Erro no backup: {e}")

    def carregar_backup(self):
        """Carrega lista de matrizes de arquivo"""
        try:
            from pickle import load
            arquivo = input("Nome do arquivo para carregar: ").strip() or self.backup_file
            with open(arquivo, 'rb') as f:
                novas_matrizes = load(f)
                
            if input("Substituir lista atual? [S/N] ").upper() == 'S':
                self.matrizes = novas_matrizes
                print("Lista substituída!")
            else:
                self.matrizes.extend(novas_matrizes)
                print("Matrizes adicionadas à lista atual!")
                
        except Exception as e:
            print(f"Erro ao carregar: {e}")

    def zerar_lista(self):
        """Remove todas as matrizes"""
        if input("Tem certeza? [S/N] ").upper() == 'S':
            self.matrizes = []
            print("Lista zerada!")

    def menu(self):
        """Exibe menu interativo"""
        while True:
            print("\n" + "="*50)
            print("GERENCIADOR DE MATRIZES")
            print("="*50)
            print("1. Imprimir matriz(es)")
            print("2. Inserir matriz (teclado)")
            print("3. Inserir matriz (arquivo)")
            print("4. Inserir matriz identidade")
            print("5. Alterar/Remover matriz(es)")
            print("6. Listar matrizes")
            print("7. Fazer backup")
            print("8. Carregar backup")
            print("9. Zerar lista")
            print("0. Sair")
            print("="*50)
            
            opcao = input("Opção: ").strip()
            
            if opcao == '1':
                if not self.matrizes:
                    print("Nenhuma matriz cadastrada!")
                    continue
                    
                self.listar_matrizes()
                selecao = input("Nome(s) da(s) matriz(es) (separar por vírgula) ou [T]odas: ").strip()
                
                if selecao.upper() == 'T':
                    for nome, matriz in self.matrizes:
                        print(f"\nMatriz: {nome} ({type(matriz).__name__} {matriz.m}x{matriz.n})")
                        print(self.imprimir_matriz(matriz))
                else:
                    for nome in selecao.split(','):
                        nome = nome.strip()
                        matriz = next((m for n, m in self.matrizes if n == nome), None)
                        if matriz:
                            print(f"\nMatriz: {nome} ({type(matriz).__name__} {matriz.m}x{matriz.n})")
                            print(self.imprimir_matriz(matriz))
                        else:
                            print(f"Matriz '{nome}' não encontrada!")
            
            elif opcao == '2': self.inserir_matriz_teclado()
            elif opcao == '3': self.inserir_matriz_arquivo()
            elif opcao == '4': self.inserir_identidade()
            elif opcao == '5': self.alterar_remover_matrizes()
            elif opcao == '6': self.listar_matrizes()
            elif opcao == '7': self.gravar_backup()
            elif opcao == '8': self.carregar_backup()
            elif opcao == '9': self.zerar_lista()
            elif opcao == '0': 
                print("Saindo...")
                break
            else:
                print("Opção inválida!")

if __name__ == "__main__":
    manager = MatrizManager()
    manager.menu()