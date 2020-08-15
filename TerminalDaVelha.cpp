//Inclusoes...
#include <iostream>

//Classes...
class ABoard // Cria Uma classe chamada de ABoard responsavel pelo tabuleiro
{
public: //Seçao publica da Classe
	ABoard() //Funcao contrutura da classe
	{
		for (int RowIndex = 0; RowIndex < 3; RowIndex++) // For que ira roda tres vezes pra A linha
		{
			for (int ColumIndex = 0; ColumIndex < 3; ColumIndex++) // For que ira roda tres vezes pra A Coluna
			{
				Board[RowIndex][ColumIndex] = ' '; // Coloca o valor da Line e Coluna como vazia 
			}
		}
	}

	void Print() const //Criar A funcao Print que nao retorna nada e que nao ira altera nada, Essa funcao ira desenha na tela o tabuleiro
	{
		for (int RowIndex = 0; RowIndex < 3; RowIndex++) //For que ira roda tres vezes pra A Linha
		{
			std::cout << "\t\t"; //Toda vez que roda o for deixa dois tabs de distancia

			for (int ColumIndex = 0; ColumIndex < 3; ColumIndex++) //for que roda tres vezez pra A Coluna
			{
				std::cout << Board[RowIndex][ColumIndex]; //Colocar o Valor atual de Linha e Coluna
				if (ColumIndex < 2) //Se o valor da Coluna for < 2
				{
					std::cout << "|"; //Desenha uma barra;
				}
			}
			std::cout << "\n"; //Dar Uma quebra de linha

			if (RowIndex < 2) //Ser o valor de Linha for < 2
			{
				std::cout <<"\t\t"<< "-----" << "\n"; // Desenha traços; 
			}
		}
		std::cout << "\n"; //Dar quebra da linha
	}

	char GetValue(int Row, int Colum) const // Funcao GetValue que retorn um char e nao muda nada, vai returna o valor na casa do Tabuleiro
	{
		return Board[Row][Colum]; //Retorna o valor na casa do Tabuleiro[Linha][Coluna]
	}

	void SetValue(int Row, int Colum, char Value) // Funcao SetValue que nao retorna nada, vai colocar um valor em uma casa do Tabuleiro
	{
		Board[Row][Colum] = Value; // Tableiro[Linha][Coluna] = Valor;
	}
	
	bool IsFull() const // Funcao IsFull que retorna um bool e nao muda nada
	{
		for (int RowIndex = 0; RowIndex < 3; RowIndex++) //For que ira roda tres vezes na Linha
		{
			for (int ColumIndex = 0; ColumIndex < 3; ColumIndex++) // For que ira roda tres vezes na Coluna
			{
				if (Board[RowIndex][ColumIndex] == ' ') //Se alguma casa do tabuleirio for igual a espaço vazio
				{
					return false; // Retorna o valord de Falso
				}
			}
		}

		return true; //Se ele passou pelo loop e nao teve casa vazia retona verdadeiro
	}
	
	bool IsEmpty() const //Funcao IsEmpty que retorna um bool e nao muda nada
	{
		for (int RowIndex = 0; RowIndex < 3; RowIndex++) //For que ira roda tres vezes na Linha
		{
			for (int ColumIndex = 0; ColumIndex < 3; ColumIndex++) //FOr que ira roda tres vezes na Coluna
			{
				if (Board[RowIndex][ColumIndex] != ' ') //Se alguma casa do tabuleiro for diferenet da casa vazia
				{
					return false; // Retorne Falso
				}
			}
		}

		return true; //Se passou pelo loop e todas as casas estavam vazias Retorne Verdadeiro
	}

private: //Secao privada da classe
	char Board[3][3]; // Criar uma Matriz com 3 linhas e colunas 
};

class APlayer //Criar classe Pai e Interface chamada de APlayer
{
public: //Secao Publica Da classe
	virtual const char* GetName() = 0; //Funcao que deve ser rescrita no filho dessa classe, Funcao GetName que retorna um ponteiro de Char e nao muda nada
	virtual void MakeMove(const ABoard* Tabuleiro, int& Row, int& Colum) = 0; // Funcao que deve ser rescrita no filho dessa classe, Funcao MakeMove que vai mosta a jogada do jogador em um tabuleiro constante
};

class AHumanPlayer : public APlayer //Criar Classe filha da Secao publica do APlayer, chamada AHumanPlayer
{
public: //Secao publica da classe
	const char* GetName() override //Funcao subscrita do GetName
	{
		return "Player"; //Retorna o nome "Player";
	}

	void MakeMove(const ABoard* Tabuleiro, int& Row, int& Colum) override //Funcao Subscrita do MakeMove
	{
		int Input = ReadInput(); //Variavel inteira com o valor da Funcao ReadInput

		Row = 2 - (Input - 1) / 3; //Faz o calcuro da jogada pra Linha
		Colum = (Input - 1) % 3; //Faz o calcuro da Jogada pra Coluna

	}

private: //Secao Privada da classe

	int ReadInput() //Funcao ReadInput que retorna um inteiro
	{
		while (true) //Loop enqunto verdadeiro
		{
			std::cout << "Faca sua Jogada [1..9]: " << "\n"; //Escreve na tela por jogado fazer sua jogadar
			int Input; // Criar variavel inteiro pra armezenar o input do Player
			std::cin >> Input; //Valor digitado ira para o Input

			if (1 <= Input && Input <= 9) // Se o valor de Input for >= 1 E Input for <= 9
			{
				return Input; //Retorna o valor de Input
			}
			else //SENAO
			{
				std::cout << "Jogada Invalida, tente novamente" << "\n"; //Se nao mostra na tela que a jogada foi invalida
			}
		}
		

	}

};

class AAIPlayer : public APlayer //Classe Filha da secao public de APlayer, chamada de AAIPlyer
{
public: //Secao publica da classe
	const char* GetName() override //Sobscreve a Funcao GetName
	{
		return "AI Player"; //Retorna o nome "AI Player";
	}

	void MakeMove(const ABoard* Tabuleiro, int& Row, int& Colum) override //Funao Sobscrita MakeMove
	{

		for (int RowIndex = 0; RowIndex < 3; RowIndex++) //For que ira roda tres vezes pra Linha
		{
			for (int ColumIndex = 0; ColumIndex < 3; ColumIndex++) //For que ira roda tres pra Coluna
			{
				if (Tabuleiro->GetValue(RowIndex, ColumIndex) == ' ') //Se no tabuleiro constante o valor de GetValue(Linha, Coluna) for igual a uma casa vazia
				{
					Row = RowIndex; //A jogada na linha receber a Linha
					Colum = ColumIndex;//A jogada na coluna receber a Coluna
					return;//Retorna e sair da funcao
				}
			}
		}
	}

};

class AGame //Criar Classe do AGame
{
public: //Secao Publica da Classe

	enum class GameResult //Cria um enum(lista de valores) de classes Chamado GameResult
	{
		NotOver, //Valor pra Enquanto nao tive acabado o jogo
		Player1, //Valor pra quando o Player1 Ganhar
		Player2, //Valor pra quando o Player2 Ganhar
		Draw //Valor pra quando enpata
	};

	AGame() //Funcao Contrutura da classe
	{
		Player1 = new AHumanPlayer; //O ponteiro Player1 receber uma nova classe AHumanPlayer
		Player2 = new AAIPlayer; //O ponteiro Player2 receber uma nova classe AIAPlayer
	}

	~AGame() //Funcao destrutura da classe
	{
		delete Player1; //Deletar da memoria o Player1
		delete Player2; //Deletae da memora o Player2
	}
	
	void SetGameOver() //Funcao SetGameOver que nao retorna nada
	{

		bIsGameOver = true; // A variavel bIsGameOver Receber o valor de verdadeiro
		if (bIsPlayer1Turn) //SE a variavel bISPlayer1Turn(vez do jogador1) for verdadeira
		{
			Result = GameResult::Player1; // Result Receber GameResult::Player1;
		}
		else //SENAO
		{
			Result = GameResult::Player2; // Result receber GameResult::Player2;
		}
	}

	bool IsALine(char A, char B, char C) //Funcao IsALine que retorna um bool
	{
		return A != ' ' && A == B && B == C; //Se todos as casas foram iguais e diferente de vazia retorna verdadeira
	}

	void CheckGameOver() //Funcao ChackGameOver que nao retorna nada
	{
		if (Tabuleiro.IsEmpty()) //SE o Tabuleiro.estiveVaziu
		{
			return; //Retorna e fecha
		}

		for (int RowIndex = 0; RowIndex < 3; ++RowIndex) //For que roda tres vezes pra Linha
		{
			char Col0 = Tabuleiro.GetValue(RowIndex, 0); //Variavel char que receber A casa do Tabuleiro.PegarValor(Linha, 0)
			char Col1 = Tabuleiro.GetValue(RowIndex, 1); //Variavel char que receber A casa do Tabuleiro.PegarValor(Linha, 1)
			char Col2 = Tabuleiro.GetValue(RowIndex, 2); //Variavel char que receber A casa do Tabuleiro.PegarValor(Linha, 2)

			if (IsALine(Col0, Col1, Col2)) //SE as casas forem iguias
			{
				SetGameOver(); //Chama a funcao pra GameOver
				return; //Retorna e sair
			}

		}

		for (int Colum = 0; Colum < 3; ++Colum) //For que roda tres vezes pra Coluna
		{
			char Row0 = Tabuleiro.GetValue(0, Colum); //Variavel char que receber A casa do Tabuleiro.PegarValor(0, Coluna)
			char Row1 = Tabuleiro.GetValue(1, Colum); //Variavel char que receber A casa do Tabuleiro.PegarValor(1, Coluna)
			char Row2 = Tabuleiro.GetValue(2, Colum); //Variavel char que receber A casa do Tabuleiro.PegarValor(2, Coluna)

			if (IsALine(Row0, Row1, Row2)) //SE as casas forem iguias
			{
				SetGameOver(); //Chama a funcao pra GameOver
				return; //Retorna e sair
			}
		}

		char Diag0 = Tabuleiro.GetValue(0, 0); //Variavel char que receber A casa do Tabuleiro.PegarValor(0, 0)
		char Diag1 = Tabuleiro.GetValue(1, 1);  //Variavel char que receber A casa do Tabuleiro.PegarValor(1, 1)
		char Diag2 = Tabuleiro.GetValue(2, 2); //Variavel char que receber A casa do Tabuleiro.PegarValor(2, 2)

		if (IsALine(Diag0, Diag1, Diag2)) //SE as casas forem iguias
		{
			SetGameOver(); //Chama a funcao pra GameOver
			return; //Retorna e sair

		}
		
		Diag0 = Tabuleiro.GetValue(0, 2); //Variavel char que receber A casa do Tabuleiro.PegarValor(0, 2)
		Diag2 = Tabuleiro.GetValue(2, 0); //Variavel char que receber A casa do Tabuleiro.PegarValor(2, 0)

		if (IsALine(Diag0, Diag1, Diag2)) //SE as casas forem iguias
		{
			SetGameOver(); //Chama a funcao pra GameOver
			return; //Retorna e sair
		}

		if (Tabuleiro.IsFull()) //SE o Tabuleiro.EstaCheio
		{
			bIsGameOver = true; // a variavel bISGameOver receber verdadeiro
			Result = GameResult::Draw; //A variavel result receber o GameResult::Draw
			return; //Retorna e sair
		}
	}

	bool Play(int Row, int Colum, char Value) //Funcao Play que retorna um bool
	{
		if (Tabuleiro.GetValue(Row, Colum) == ' ') //SE o valor da casa do tabuleiro estive vazia 
		{
			Tabuleiro.SetValue(Row, Colum, Value); //Coloque um Valor naquela casa
			return true; //Retorna um verdadeiro
		}
		else //SENAO
		{
			return false; //Retorna um Falso
		}
	}

	void PrintResult() //Funcao PrintResult que nao retorna nada
	{
		switch (Result) //Switch sobre o Result
		{
			case GameResult::Draw: //Caso o resultado for Empate
				std::cout << "Empate!" << "\n"; //Mostre na tela Empate
				break; //Termina

			case GameResult::Player1: //Caso o resultado for Player1
				std::cout << Player1->GetName() << " Ganhou!" << "\n"; //Mostra na tela que o Player1 Ganhou
				break; //Termina

			case GameResult::Player2: //Caso o resultado for Player2
				std::cout << Player2->GetName() << " Ganhou!" << "\n"; //Mostra na tela que o Player2 Ganhou
				break; //Termina

			default:
				break;
		}
	}

	void NextMove() //Funcao NextMone que nao retorna nada
	{
		int Row, Colum; //cria duas variaveis int Linha, Coluna

		if (bIsPlayer1Turn) //SE for a vez do jogado1(bISPlayer1Turn)
		{
			Player1->MakeMove(&Tabuleiro, Row, Colum); //Chama a funcao pra o Player1 monta a jogada
		}
		else //SENAO
		{
			Player2->MakeMove(&Tabuleiro, Row, Colum); //Chama a funcao pra o Jogador2 monta sua jogada
		}

		bool bIsMoveValid = Play(Row, Colum, bIsPlayer1Turn ? 'X' : 'O'); // variavel bool(bISMoveValid) que receber Play(o seu return)

		if (bIsMoveValid) //SE o movimento foi valido(bISMoveValid)
		{
			CheckGameOver(); //Chama a funcao pra check o game over, CheckGameOver

			bIsPlayer1Turn = !bIsPlayer1Turn; //Inverto o valor de bIsPlayer1Turn(Vez do jogado 1)
		}

	}

	APlayer* Player1; //Cria Objeto Ponteiro do tipo APlayer chamado Player1
	APlayer* Player2; //Cria Objeto Ponteiro do tipo APlayer chamado Player2
	ABoard Tabuleiro; //Cria um Objeto do tipo ABoard chamado Tabuleiro 
	bool bIsGameOver = false; //Criar variavel bool bIsGameOver(se teve game over) receber falso
	bool bIsPlayer1Turn = true; //Criar variavel bool bIsPlayer1Turn(vez do jogador1) receber verdadeiro
	GameResult Result = GameResult::NotOver; //Criar Variavel do Tipo GameResult chamada de Result e Receber o valor de NotOver

};


//Principal...
int main()
{
	
	AGame Game; //Criar um Objet do tipo AGame chamado Game

	while (!Game.bIsGameOver) //ENQUANTO O jogo GameOver for falso
	{
		Game.Tabuleiro.Print(); // Chama o Print do tabuleiro pelo Game, Para mostra na tela o mesmo

		Game.NextMove(); //Chama a funcao NextMove do Game

		system("cls"); //Funcao pra limpa a tela
	}

	Game.Tabuleiro.Print(); // Chama o Print do tabuleiro pelo Game, Para mostra na tela o mesmo
	Game.PrintResult(); // Mostra o resultado na tela

	return 0;
}