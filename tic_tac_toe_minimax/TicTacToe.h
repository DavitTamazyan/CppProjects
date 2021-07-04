#pragma once

#include<iostream>
#include<vector>

struct Move
{
	int row{-1};
	int col{-1};

	Move()
	{
		row = -1;
		col = -1;
	}

	Move(int row_, int col_)
	{
		row = row_;
		col = col_;
	}

	bool operator !=(Move& rhs)
	{
		return (row == rhs.row) && (col == rhs.col);
	}
};

class TicTacToe
{
public:
	TicTacToe();

	TicTacToe(char player_type);

	~TicTacToe();

	void GameStat();

	void PrintTable(std::vector<std::string> table);

	Move ReadCommand(std::string command);

	bool CheckCommand(Move move);

	void PLayMove(Move move, char curPLayer);

	Move BotMove();

	int BotMoveMiniMax(std::vector<std::string> table, char player_type, char curMove);

	bool GameEnd(std::vector<std::string> table);

private:
	std::vector<std::string> m_table;
	char m_player_type;
	char m_winner_type;
};

