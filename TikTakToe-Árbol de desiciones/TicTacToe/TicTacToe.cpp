#include "TicTacToe.h"
TicTacToe* TicTacToe::ptr = nullptr;

/*Se imprimen los lugares vaci�s dentro del arreglo de dos dimensiones donde suceder� el juego*/
void TicTacToe::SetUp() {
	try {
		gameBoard = new string * [lines]; //Genera la primer dimensi�n para el arreglo de strings
		/*Determinar qu� se va a imprimir dentro de las casillas que tendr� el gameBoard*/
		for(int i = 0; i < lines; i++) {
			gameBoard[i] = new string[columns]; //Crea la segunda dimensi�n del arreglo de strings
			for(int j = 0; j < columns; j++) {
				gameBoard[i][j] = "_"; //El elemento en esta matriz se iguala a "_" simulando un espacio vac�o
			}
		}
	} catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*Se imprimen los valores del tablero*/
void TicTacToe::printBoard() {
	try {

		cout << "\nTablero del juego\n";
		/*Recorre toda la matriz e imprime los valores*/
		for(int i = 0; i < lines; i++) {
			for(int j = 0; j < columns; j++) {
				cout << "| " << gameBoard[i][j] << " ";
			}
			cout << "|" << endl;
		}
		cout << endl;
	} catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*La clase ser� singleton, por lo que el constructor y destructor no se pueden conseguir de manera p�blica*/
TicTacToe* TicTacToe::GetPtr() {
	if(!ptr) //Si el apuntador es nulo, crea uno nuevo
		ptr = new TicTacToe();
	return ptr; //regresa el apuntador
}

/*Funci�n que mandar� a llamar las primer funciones del juego de TicTacToe*/
void TicTacToe::Init() {	
	try {
		running = true;
		posibilidades = new Grafo<string>();
		SetUp();
		printBoard();
	} catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*Actualizac�on constante del juego*/
void TicTacToe::Update() {
	while(running) {
		if (PlayerInput() == true) { //Turno del jugador
			printBoard(); //Imprime la tabla
			CheckWin();
			if (agentWin || playerWin) {
				printBoard(); //Imprime la tabla
				break;
			}
			AgentTurn(); //Turno del agente
			/*copyBoard(); */
			CheckWin();
			if (agentWin || playerWin) {
				printBoard(); //Imprime la tabla
				break;
			}
			printBoard(); //Imprime la tabla
		}
	}
	if (playerWin)
	{
		cout << "YOU WINNNNNNNNNNNNNNNNNNNNNN";
	}
	else
	{
		cout << "YOU LOOOOOOOOOOOOOOOOOOSE";
	}
}

/*Detecta la posici�n en la que el jugador decide poner su s�mbolo*/
bool TicTacToe::PlayerInput() {
	try {

		cout << "Elige la fila donde se ubicara tu simbolo: ";
		cin >> x;  //Elemento en el eje X o en las l�neas del gameBoard
		if(cin.fail() || x > columns - 1 || x < 0) 
			throw(x);
		
		cout << "\nElige la columna donde se ubicar� tu simbolo: ";
		cin >> y; //Elemento en el eje Y o en las columnas del gameBoard
		if(cin.fail() || y > lines - 1 || y < 0) //El input fue uno no permitido o se pas� del n�mero de l�neas
			throw(x);

		if(gameBoard[x][y] == "O"|| gameBoard[x][y] ==  "X")
			cout << "Esa posicion ya fue elegida.\n";
		else {
			setNewBoard(x, y); //Cambia el tablero actual
			return true;
		}
		cout << endl;


	} catch(int x) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "You entered a wrong input" << endl;
	} catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}


/*Se actualiza el nuevo gameboard en caso de que ingresen buenos inputs por parte del jugador*/
void TicTacToe::setNewBoard(int x, int y) {
	try {
		/*Se actualiza el input del jugador dentro de la matriz del juego*/
		for(int i = 0; i < lines; i++) {
			if(i == x) { //Si la i es igual a la x, avanza el la j
				for(int j = 0; j < columns; j++) {
					if(j == y) { //Si es igual, cambia el string a una O
						gameBoard[i][j] = "O";
					}
				}
			}
		}
	} catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*Checamos si se cumplen las condiciones de victoria*/
void TicTacToe::CheckWin()
{ 
	string checking;

	//Horzontales
	for (int j = 0; j < lines; j++)
	{
		if (gameBoard[0][j] == "O" || gameBoard[0][j] == "X")
		{ //Preguntar si el caracter es del jugador o del agente
			checking = gameBoard[0][j]; //Guardar el string de este elemento
			if (gameBoard[1][j] == checking && gameBoard[2][j] == checking)
			{ //Preguntar si en el espacio al lado de este elemento tiene string
				if (checking == "O") { //Preguntar si es del jugador
					playerWin = true; //Win es igual a true
					running = false; //Termina el juego
				} else if (checking == "X") { //El ganador es el agente
					agentWin = true; //Cambia el bool a verdadero
					running = false; //Rompe el while
				}
			}
		}
	}

	//Verticales
	for (int i = 0; i < lines; i++)
	{ 
		if (gameBoard[i][0] == "O" || gameBoard[i][0] == "X")
		{ //Pregunta si es el jugador o es el agente
			checking = gameBoard[i][0];
			if (gameBoard[i][1] == checking && gameBoard[i][2] == checking)
			{ //Checa si las verticales son del mismo string
				if (checking == "O")
				{ //Checa si es string del jugador
					running = false; //Termina el while
					playerWin = true; //Gana el jugador
				}
				else if (checking == "X")
				{ //Es string del agente
					agentWin = true; //Gana el agente
					running = false; //Termina el while
				}
			}
		}
	}

	//Diagonal 1, posici�n [0][0]
	if (gameBoard[0][0] == "O" || gameBoard[0][0] == "X")
	{ //Checa las diagonales de izquierda a derecha
		checking = gameBoard[0][0];
		if (gameBoard[1][1] == checking && gameBoard[2][2] == checking) { //checa las diagonales de [1][1] y [2][2]
			if (checking == "O")
			{ //Checa si son s�mbolos del jugador
				playerWin = true; //Gana el jugador
				running = false; //Rompe el while
			}
			else if (checking == "X")
			{ //Checa si es tirada del agente
				agentWin = true; //Gana el agente, rompe el while
				running = false; //
			}
		}
	}

	//Diagonal 2, posici�n [2][2]
	if (gameBoard[0][2] == "O" || gameBoard[0][2] == "X")
	{ //checa de derecha a izquierda en la diagonal principal
		checking = gameBoard[0][2];
		if (gameBoard[1][1] == checking && gameBoard[2][0] == checking)
		{ //Si la diagonal de la derecha a la izquierda tiene el mismo string
			if (checking == "O")
			{ //Pregunta si es s�mbolo del jugador
				playerWin = true; //Gana el jugador
				running = false; //Termina el while
			}
			else if (checking == "X")
			{ //Pregunta si es s�mbolo del jugador
				agentWin = true;
				running = false;
			}
		}
	}
}

/*Es el turno del agente, checa qu� cambios hay en el tablero y a partir de ah� revisa qu� cambios hubo.*/
void TicTacToe::AgentTurn() {
	try 
	{
		Vector2* AgentPos = MinMax(GenerateCopy(gameBoard));
		gameBoard[AgentPos->x][AgentPos->y] = "X";
	} catch(...) {
		cout << "Algo esta mal!\n";
	}

}

/*Busca un valor vac�o dentro del arreglo de strings del par�metro, si est� ocupado por el s�mbolo del agente o del jugador, lo salta
 *@param[string** g] el tablero en el cual se va a buscar un string.
 *@return regresa un vector de 2 dimensiones*/
Vector2* TicTacToe::MinMax(string** g)
{
	Vector2* Best = new Vector2(0,0);
	int max = -10000;
	for (int i = 0; i < lines; i++)
	{ //Itera en la primer dimensi�n del arreglo
		for (int j = 0; j < columns; j++)
		{ //Itera en la segunda dimensi�n del arreglo
			if (g[i][j] != "O" && g[i][j] != "X")
			{ //Pregunta si el string en esta posici�n no ha sido ocupado por el jugador o del agente 
				int temp = MinMaxR(i, j, 1, g);
				if (max < temp) //Manda a llamar la funci�n recursiva del juego 
				{
					max = temp;
					Best->x = i;
					Best->y = j;
				}
			}
		}
	}
	return Best;
}

/*Pregunta si ya hay un estado terminal
 *@return regresa verdadero en caso de ser terminal y falso en caso de no serlo*/
bool TicTacToe::Terminal(string** g)
{
	string checking;
	for (int j = 0; j < lines; j++)
	{
		if (g[0][j] == "O" || g[0][j] == "X")
		{ //Preguntar si el caracter es del jugador o del agente
			checking = g[0][j]; //Guardar el string de este elemento
			if (g[1][j] == checking && g[2][j] == checking)
			{ //Preguntar si en el espacio al lado de este elemento tiene string
				return true;
			}
		}
	}

	//Verticales
	for (int i = 0; i < lines; i++)
	{
		if (g[i][0] == "O" || g[i][0] == "X")
		{ //Pregunta si es el jugador o es el agente
			checking = g[i][0];
			if (g[i][1] == checking && g[i][2] == checking)
			{ //Checa si las verticales son del mismo string
				return true;
			}
		}
	}

	//Diagonal 1, posici�n [0][0]
	if (g[0][0] == "O" || g[0][0] == "X")
	{ //Checa las diagonales de izquierda a derecha
		checking = g[0][0];
		if (g[1][1] == checking && g[2][2] == checking)
		{ //checa las diagonales de [1][1] y [2][2]
			return true;
		}
	}

	//Diagonal 2, posici�n [2][2]
	if (g[0][2] == "O" || g[0][2] == "X")
	{ //checa de derecha a izquierda en la diagonal principal
		checking = g[0][2];
		if (g[1][1] == checking && g[2][0] == checking)
		{ //Si la diagonal de la derecha a la izquierda tiene el mismo string
			return true;
		}
	}

	return false;
}


/*Se realiza la b�squeda recursiva para saber si la posici�n actual es adecuada para que el agente realice su tirada ah� mismo.
 *@param[int i] la posici�n en la primer dimensi�n [i][j]
 *@param[int j] la posici�n en la segunda dimensi�n [i][j]
 *@param[int turn] el turno del que est� tirando, puede ser del jugador (2) o del agente (1)
 *@return regresa el n�mero de la jugada (1 aceptable o -1 inaceptable) */
int TicTacToe::MinMaxR(int i, int j, int turn, string** cp)
{
	try {
		int value = 0;
		string** copy = GenerateCopy(cp); //Genera la copia del tablero de juego
		if (turn == 1)
		{ //El turno es del agente
			copy[i][j] = "X"; //En la copia imprime una X en estas posiciones
		}
		else
		{ //El turno es del jugador
			copy[i][j] = "O"; //En la copia imprime una O en estas posiciones
		}
		
		if (!Terminal(copy))
		{ //Si no ha sido un estado terminal
			for (int i = 0; i < lines; i++)
			{ //Itera por la primera dimensi�n del arreglo
				for (int j = 0; j < columns; j++) 
				{ //Itera por la segunda dimensi�n del arreglo
					if (copy[i][j] != "O" && copy[i][j] != "X")
					{ //Pregunta si es un espacio vac�o 
						if (turn == 1)
						{ //Si es turno del agente
							value += MinMaxR(i, j, 2, copy); //Recursividad con el turno del jugador y suma el resultador
						}
						else
						{
							value += MinMaxR(i, j, 1, copy); //Recursividad con el turno del agente y suma el resultado
						}
					}
				}
			}
			return value;
		}
		else
		{ //Es un estado terminal
			if (turn == 1)
			{  //Es turno del agente
				return 1; //Regresa 1
			}
			else if (turn == 2)
			{ //Es turno del jugador
				return -1; //Regresa -1
			}
		}
	}
	catch (exception & e) {
		cout << "exeption caught: " << e.what() << endl;
	}
}

/*Se genera una copia de la matriz indicada en el argumento y se regresa la copia.
 *@param[string** c] la matriz a la cual se le desea hacer la copia
 *@return se regresa la copia generada*/
string** TicTacToe::GenerateCopy(string** c)
{
	string** copy = new string * [lines]; //Crea una matriz de dos dimensiones con apuntadores

	for (int i = 0; i < lines; i++)
	{
		copy[i] = new string[columns];
		for (int j = 0; j < columns; j++)
		{
			copy[i][j] = c[i][j]; //Copia los valores de este arreglo
		}
	}
	return copy;
}


TicTacToe::TicTacToe() {
}

TicTacToe::~TicTacToe() {
}
