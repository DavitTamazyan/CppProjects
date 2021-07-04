#include "TicTacToe.h"

TicTacToe::TicTacToe()
{
	m_table.push_back("   ");
	m_table.push_back("   ");
	m_table.push_back("   ");
	m_winner_type = 'U';
	char tmp = 'U';
	while (tmp != 'X' && tmp != 'O')
	{
		std::cout << "Please Select X or O : ";
		std::cin >> tmp;
	}
	m_player_type = tmp;
	GameStat();
}

TicTacToe::TicTacToe(char player_type)
{
	m_table.push_back("   ");
	m_table.push_back("   ");
	m_table.push_back("   ");
	m_player_type = player_type;
	m_winner_type = 'U';
	GameStat();
}

TicTacToe::~TicTacToe()
{
}

void TicTacToe::GameStat()
{
	std::cout << "Game Started" << std::endl;
	char curPLayer = 'X';
	std::string command;
	Move tmp;
	while (!GameEnd(m_table))
	{
		PrintTable(m_table);
		if (curPLayer == m_player_type)
		{
			std::cout << "Your Move : ";
			std::cin >> command;
			tmp = ReadCommand(command);
			if (CheckCommand(tmp))
			{
				PLayMove(tmp, curPLayer);
				curPLayer = (curPLayer == 'X') ? 'O' : 'X';
			}
			else
			{
				std::cout << "Invalid Command" << std::endl;
			}
		}
		else
		{
			tmp = BotMove();
			PLayMove(tmp, curPLayer);
			std::cout << "Bot Move : " << tmp.col << tmp.row << std::endl;
			curPLayer = (curPLayer == 'X') ? 'O' : 'X';
		}
	}

	PrintTable(m_table);
	std::cout << m_winner_type << " Wins" << std::endl;
	std::cout << "Game End" << std::endl;
}

void TicTacToe::PrintTable(std::vector<std::string> table)
{
	for (auto itr : table)
	{
		std::cout << "_____________" << std::endl;
		for (char& c : itr)
		{
			std::cout << "| " << c << " ";
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "_____________" << std::endl;
}

Move TicTacToe::ReadCommand(std::string command)
{
	Move result;
	if (!((command.size() != 2) || 
		 ((command[0] - 48) < 0 || (command[0] - 48) > 2) || 
		 ((command[1] - 48) < 0 || (command[1] - 48) > 2)))
	{
		result.row = (command[0] - 48);
		result.col = (command[1] - 48);
	}

	return result;
}

bool TicTacToe::CheckCommand(Move move)
{
	if ((move.col == -1 && move.row == -1) || m_table[move.row][move.col] != ' ')
	{
		return false;
	}
	return true;
}

void TicTacToe::PLayMove(Move move, char curPLayer)
{
	m_table[move.row][move.col] = curPLayer;
}

Move TicTacToe::BotMove()
{
	std::cout << "Bots Main Logic Start" << std::endl;

	std::vector<std::string> table = this->m_table;
	int* PosibleMoves = new int[9];
	Move result;

	for (int i = 0; i < 9; ++i)
	{
		//std::cout << "-" << i / 3 << " " << i % 3 << "-" << std::endl;
		//std::cout << "---------------------- Big i = " << i << "----------------------" << std::endl;
		if (m_table[i / 3][i % 3] == ' ')
		{
			table[i / 3][(i % 3)] = (m_player_type == 'X') ? 'O' : 'X';
			PosibleMoves[i] = BotMoveMiniMax(table, m_player_type, m_player_type);
			//PosibleMoves[i] = BotMoveMiniMax(table, m_player_type, (m_player_type == 'X') ? 'O' : 'X');
			table[i / 3][(i % 3)] = ' ';
			//std::cout << "i = " << i << " " << PosibleMoves[i] << std::endl;
		}
		else
		{
			PosibleMoves[i] = -1;
		}
	}
	int max = 0;

	for (int i = 1; i < 9; ++i)
	{
		if (PosibleMoves[i] > PosibleMoves[max])
		{
			max = i;
		}
	}

	//std::cout << "max = " << max << std::endl;
	result.row = max / 3;
	result.col = max % 3;

	std::cout << "Bots Main Logic End" << std::endl;
	return result;
}

int TicTacToe::BotMoveMiniMax(std::vector<std::string> table, char player_type, char curMove)
{
	int count = 0;
	if (GameEnd(table))
	{
		if (player_type == m_winner_type) /// m_winner_type mast to be local for yhis func.
		{
			return -1;
		}
		else if ('D' == m_winner_type)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else {
		for (int i = 0; i < 9; ++i)
		{
			if (table[i / 3][(i % 3)] == ' ')
			{
				table[i / 3][(i % 3)] = curMove;
				count += BotMoveMiniMax(table, player_type, (curMove == 'X') ? 'O' : 'X');
				table[i / 3][(i % 3)] = ' ';
			}
		}
	}
	return count;
}

bool TicTacToe::GameEnd(std::vector<std::string> table)
{
	bool isWin = false;
	bool isDraw = true;
	bool xWin = false;
	bool oWin = false;
	char row0 = 255,
		row1 = 255,
		row2 = 255,
		col0 = 255,
		col1 = 255,
		col2 = 255,
		anc1 = 255,
		anc2 = 255;

	for (int i = 0; i < 3; ++i)
	{
		row0 &= table[0][i];
		row1 &= table[1][i];
		row2 &= table[2][i];
		col0 &= table[i][0];
		col1 &= table[i][1];
		col2 &= table[i][2];
		anc1 &= table[i][i];
		anc2 &= table[2 - i][i];
		isDraw &= (table[0][i] != ' ') && (table[1][i] != ' ') && (table[2][i] != ' ');
	}

	xWin = row0 == 'X' || row1 == 'X' || row2 == 'X' ||
		col0 == 'X' || col1 == 'X' || col2 == 'X' ||
		anc1 == 'X' || anc2 == 'X';

	oWin = row0 == 'O' || row1 == 'O' || row2 == 'O' ||
		col0 == 'O' || col1 == 'O' || col2 == 'O' ||
		anc1 == 'O' || anc2 == 'O';

	isWin = xWin || oWin;

	if (isWin)
	{
		m_winner_type = (xWin) ? 'X' : 'O';
	}
	else if (isDraw)
	{
		m_winner_type = 'D';
	}

	return isWin || isDraw;

	return false;
}
