//Inclusoes...
#include <iostream>

//Classes...
class ABoard // Cria Uma classe chamada de ABoard responsavel pelo tabuleiro
{
public: //Seçao publica da Classe
	ABoard()
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

			if (1 >= Input && Input <= 9) // Se o valor de Input for >= 1 E Input for <= 9
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

	enum class GameResult
	{
		NotOver,
		Player1,
		Player2,
		Draw
	};

	AGame()
	{
		Player1 = new AHumanPlayer;
		Player2 = new AAIPlayer;
	}

	~AGame()
	{
		delete Player1;
		delete Player2;
	}
	
	void SetGameOver()
	{

		bIsGameOver = true;
		if (bIsPlayer1Turn)
		{
			Result = GameResult::Player1;
		}
		else
		{
			Result = GameResult::Player2;
		}
	}

	bool IsALine(char A, char B, char C)
	{
		return A != ' ' && A == B && B == C;
	}

	void CheckGameOver()
	{
		if (Tabuleiro.IsEmpty())
		{
			return;
		}

		for (int RowIndex = 0; RowIndex < 3; ++RowIndex)
		{
			char Col0 = Tabuleiro.GetValue(RowIndex, 0);
			char Col1 = Tabuleiro.GetValue(RowIndex, 1);
			char Col2 = Tabuleiro.GetValue(RowIndex, 2);

			if (IsALine(Col0, Col1, Col2))
			{
				SetGameOver();
				return;
			}

		}

		for (int Colum = 0; Colum < 3; ++Colum)
		{
			char Row0 = Tabuleiro.GetValue(0, Colum);
			char Row1 = Tabuleiro.GetValue(1, Colum);
			char Row2 = Tabuleiro.GetValue(2, Colum);

			if (IsALine(Row0, Row1, Row2))
			{
				SetGameOver();
				return;
			}
		}

		char Diag0 = Tabuleiro.GetValue(0, 0);
		char Diag1 = Tabuleiro.GetValue(1, 1);
		char Diag2 = Tabuleiro.GetValue(2, 2);

		if (IsALine(Diag0, Diag1, Diag2))
		{
			SetGameOver();
			return;

		}
		
		Diag0 = Tabuleiro.GetValue(0, 2);
		Diag2 = Tabuleiro.GetValue(2, 0);

		if (IsALine(Diag0, Diag1, Diag2))
		{
			SetGameOver();
			return;
		}

		if (Tabuleiro.IsFull())
		{
			bIsGameOver = true;
			GameResult::Draw;
			return;
		}
	}

	bool Play(int Row, int Colum, char Value)
	{
		if (Tabuleiro.GetValue(Row, Colum) == ' ')
		{
			Tabuleiro.SetValue(Row, Colum, Value);
			return true;
		}
		else
		{
			return false;
		}
	}

	void PrintResult()
	{
		switch (Result)
		{
			case GameResult::Draw:
				std::cout << "Empate!" << "\n";
				break;

			case GameResult::Player1:
				std::cout << Player1->GetName() << " Ganhou!" << "\n";
				break;

			case GameResult::Player2:
				std::cout << Player2->GetName() << " Ganhou!" << "\n";
				break;

			default:
				break;
		}
	}

	void NextMove()
	{
		int Row, Colum;

		if (bIsPlayer1Turn)
		{
			Player1->MakeMove(&Tabuleiro, Row, Colum);
		}
		else
		{
			Player2->MakeMove(&Tabuleiro, Row, Colum);
		}

		bool bIsMoveValid = Play(Row, Colum, bIsPlayer1Turn ? 'X' : 'O');

		if (bIsMoveValid)
		{
			CheckGameOver();

			bIsPlayer1Turn = !bIsPlayer1Turn;
		}

	}

	APlayer* Player1;
	APlayer* Player2;
	ABoard Tabuleiro;
	bool bIsGameOver = false;
	bool bIsPlayer1Turn = true;
	GameResult Result = GameResult::NotOver;

};


//Principal...
int main()
{
	
	AGame Game;

	while (!Game.bIsGameOver)
	{
		Game.Tabuleiro.Print();

		Game.NextMove();
	}

	Game.Tabuleiro.Print();
	Game.PrintResult();

	return 0;
}