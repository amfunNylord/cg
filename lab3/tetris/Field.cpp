#include "Field.h"
#include "Pieces.h"
#include "TimeFunctions.h"

Field::Field()
	: m_nextPiece(GetRandomPiece())
	, m_currentPiece(GetRandomPiece())
{
	for (int i = 0; i < FIELD_HEIGHT; i++)
	{
		m_matrix.at(i).at(0) = GREY_COLOR;
		m_matrix.at(i).at(FIELD_WIDTH - 1) = GREY_COLOR;
	}
	for (int i = 0; i < FIELD_WIDTH; i++)
	{
		m_matrix.at(FIELD_HEIGHT - 1).at(i) = GREY_COLOR;
	}
}

FieldMatrix Field::GetMatrix() const
{
	return m_matrix;
}

int Field::GetLevel() const
{
	return m_level;
}

int Field::GetScore() const
{
	return m_score;
}

int Field::GetLinesLeft() const
{
	return m_linesLeft;
}

int Field::GetSpeed() const
{
	return m_speed;
}

bool Field::IsNeededNewPiece()
{
	return m_isNeededNewPiece;
}

bool Field::IsNoWallDown()
{
	PieceContains pieceContains = m_currentPiece.GetContains();
	PointI currCoords = m_currentPiece.GetCoords();

	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		if (pieceContains.at(PIECE_HEIGHT - 1).at(i) != EMPTY_SQUARE)
		{
			if (m_matrix.at(currCoords.y + PIECE_HEIGHT).at(currCoords.x + i) != EMPTY_SQUARE)
			{
				return false;
			}
		}
	}

	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		if (pieceContains.at(PIECE_HEIGHT - 2).at(i) != EMPTY_SQUARE && pieceContains.at(PIECE_HEIGHT - 1).at(i) == EMPTY_SQUARE)
		{
			if (m_matrix.at(currCoords.y + PIECE_HEIGHT - 1).at(currCoords.x + i) != EMPTY_SQUARE)
			{
				return false;
			}
		}
	}

	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		if (pieceContains.at(PIECE_HEIGHT - 3).at(i) != EMPTY_SQUARE && pieceContains.at(PIECE_HEIGHT - 2).at(i) == EMPTY_SQUARE)
		{
			if (m_matrix.at(currCoords.y + PIECE_HEIGHT - 2).at(currCoords.x + i) != EMPTY_SQUARE)
			{
				return false;
			}
		}
	}

	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		if (pieceContains.at(PIECE_HEIGHT - 4).at(i) != EMPTY_SQUARE && pieceContains.at(PIECE_HEIGHT - 3).at(i) == EMPTY_SQUARE)
		{
			if (m_matrix.at(currCoords.y + PIECE_HEIGHT - 3).at(currCoords.x + i) != EMPTY_SQUARE)
			{
				return false;
			}
		}
	}

	return true;
}

bool Field::IsNoWallRight()
{	
	PieceContains pieceContains = m_currentPiece.GetContains();
	PointI currCoords = m_currentPiece.GetCoords();

	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		if (pieceContains.at(i).at(PIECE_WIDTH - 1) != EMPTY_SQUARE)
		{
			if (m_matrix.at(currCoords.y + i).at(currCoords.x + PIECE_WIDTH) != EMPTY_SQUARE)
			{
				return false;
			}
		}
	}

	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		if (pieceContains.at(i).at(PIECE_WIDTH - 2) != EMPTY_SQUARE && pieceContains.at(i).at(PIECE_WIDTH - 1) == EMPTY_SQUARE)
		{
			if (m_matrix.at(currCoords.y + i).at(currCoords.x + PIECE_WIDTH - 1) != EMPTY_SQUARE)
			{
				return false;
			}
		}
	}

	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		if (pieceContains.at(i).at(PIECE_WIDTH - 3) != EMPTY_SQUARE && pieceContains.at(i).at(PIECE_WIDTH - 2) == EMPTY_SQUARE)
		{
			if (m_matrix.at(currCoords.y + i).at(currCoords.x + PIECE_WIDTH - 2) != EMPTY_SQUARE)
			{
				return false;
			}
		}
	}

	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		if (pieceContains.at(i).at(PIECE_WIDTH - 4) != EMPTY_SQUARE && pieceContains.at(i).at(PIECE_WIDTH - 3) == EMPTY_SQUARE)
		{
			if (m_matrix.at(currCoords.y + i).at(currCoords.x + PIECE_WIDTH - 3) != EMPTY_SQUARE)
			{
				return false;
			}
		}
	}

	return true;
}

bool Field::IsNoWallLeft()
{
	PieceContains pieceContains = m_currentPiece.GetContains();
	PointI currCoords = m_currentPiece.GetCoords();

	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		if (pieceContains.at(i).at(0) != EMPTY_SQUARE)
		{
			if (m_matrix.at(currCoords.y + i).at(currCoords.x - 1) != EMPTY_SQUARE)
			{
				return false;
			}
		}
	}

	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		if (pieceContains.at(i).at(1) != EMPTY_SQUARE && pieceContains.at(i).at(0) == EMPTY_SQUARE)
		{
			if (m_matrix.at(currCoords.y + i).at(currCoords.x) != EMPTY_SQUARE)
			{
				return false;
			}
		}
	}

	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		if (pieceContains.at(i).at(2) != EMPTY_SQUARE && pieceContains.at(i).at(1) == EMPTY_SQUARE)
		{
			if (m_matrix.at(currCoords.y + i).at(currCoords.x + 1) != EMPTY_SQUARE)
			{
				return false;
			}
		}
	}

	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		if (pieceContains.at(i).at(3) != EMPTY_SQUARE && pieceContains.at(i).at(2) == EMPTY_SQUARE)
		{
			if (m_matrix.at(currCoords.y + i).at(currCoords.x + 1) != EMPTY_SQUARE)
			{
				return false;
			}
		}
	}

	return true;
}

bool Field::IsFull()
{
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (m_matrix.at(START_POS_Y + i).at(START_POS_X + j) != EMPTY_SQUARE)
			{
				return true;
			}
		}
	}
	return false;
}

bool Field::IsPossibleRotate()
{
	PointI currCoords = m_currentPiece.GetCoords();
	PieceContains pieceContains = m_currentPiece.GetContains();
	
	PieceContains newPieceContains = pieceContains;

	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		newPieceContains.at(i).at(3) = pieceContains.at(0).at(i);
	}
	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		newPieceContains.at(i).at(2) = pieceContains.at(1).at(i);
	}
	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		newPieceContains.at(i).at(1) = pieceContains.at(2).at(i);
	}
	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		newPieceContains.at(i).at(0) = pieceContains.at(3).at(i);
	}
	
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (newPieceContains.at(i).at(j) != EMPTY_SQUARE)
			{
				if (pieceContains.at(i).at(j) == EMPTY_SQUARE)
				{
					if (m_matrix.at(currCoords.y + i).at(currCoords.x + j) != EMPTY_SQUARE)
					{
						return false;
					}
				}
			}
		}
	}

	return true;
}

bool Field::IsNeededClearLines()
{
	for (int i = FIELD_HEIGHT - 2; i > 0; i--)
	{
		bool isFull = true;
		for (int j = 1; j < FIELD_WIDTH - 1; j++)
		{
			if (m_matrix.at(i).at(j) == EMPTY_SQUARE)
			{
				isFull = false;
			}
		}
		if (isFull)
		{
			m_lineIndexes.at(m_lineIndexesCount) = i;
			m_lineIndexesCount++;
		}
	}
	return m_lineIndexesCount != 0;
}

void Field::MoveAllDown(const int& fromLine)
{
	for (int i = fromLine - 1; i > -1; i--)
	{
		for (int j = 1; j < FIELD_WIDTH - 1; j++)
		{
			m_matrix.at(i + 1).at(j) = m_matrix.at(i).at(j);
			m_matrix.at(i).at(j) = EMPTY_SQUARE; 
		}
	}
}

void Field::MovingPieceLeft()
{
	PointI currCoords = m_currentPiece.GetCoords();
	PieceContains pieceContains = m_currentPiece.GetContains();

	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (pieceContains.at(i).at(j) != EMPTY_SQUARE)
			{
				m_matrix.at(currCoords.y + i).at(currCoords.x + j - 1) = m_matrix.at(currCoords.y + i).at(currCoords.x + j);
				m_matrix.at(currCoords.y + i).at(currCoords.x + j) = EMPTY_SQUARE;
			}
		}
	}
	m_currentPiece.SetCoords({ currCoords.x - 1, currCoords.y });
}

void Field::MovingPieceRight()
{
	PointI currCoords = m_currentPiece.GetCoords();
	PieceContains pieceContains = m_currentPiece.GetContains();

	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = PIECE_WIDTH - 1; j > -1; j--)
		{
			if (pieceContains.at(i).at(j) != EMPTY_SQUARE)
			{
				m_matrix.at(currCoords.y + i).at(currCoords.x + j + 1) = m_matrix.at(currCoords.y + i).at(currCoords.x + j);
				m_matrix.at(currCoords.y + i).at(currCoords.x + j) = EMPTY_SQUARE;
			}
		}
	}
	m_currentPiece.SetCoords({ currCoords.x + 1, currCoords.y });
}

void Field::AddPiece(const Piece& piece)
{
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (piece.GetContains().at(i).at(j) != EMPTY_SQUARE)
			{
				m_matrix.at(START_POS_Y + i).at(START_POS_X + j) = piece.GetContains().at(i).at(j);
			}
		}
	}
	m_isNeededNewPiece = false;
}

void Field::MovingPieceByGame()
{
	PieceContains pieceContains = m_currentPiece.GetContains();
	PointI currCoords = m_currentPiece.GetCoords();
	for (int i = PIECE_HEIGHT - 1; i > -1; i--)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (pieceContains.at(i).at(j) != EMPTY_SQUARE)
			{
				m_matrix.at(currCoords.y + i + 1).at(currCoords.x + j) = m_matrix.at(currCoords.y + i).at(currCoords.x + j);
				m_matrix.at(currCoords.y + i).at(currCoords.x + j) = EMPTY_SQUARE;
			}
		}
	}
	m_currentPiece.SetCoords({ currCoords.x, currCoords.y + 1 });
}

void Field::MovingPieceByUser(const char& key)
{
	switch (key)
	{
	case LEFT_DIRECTION:
		MovingPieceLeft();
		break;
	case RIGHT_DIRECTION:
		MovingPieceRight();
		break;
	case DOWN_DIRECTION:
		MovingPieceByGame();
		break;
	}
}

void Field::RotatePiece()
{
	PointI currCoords = m_currentPiece.GetCoords();
	PieceContains pieceContains = m_currentPiece.GetContains();

	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (pieceContains.at(i).at(j) != EMPTY_SQUARE)
			{
				m_matrix.at(currCoords.y + i).at(currCoords.x + j) = EMPTY_SQUARE;
			}
		}
	}

	PieceContains newPieceContains = pieceContains;

	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		newPieceContains.at(i).at(3) = pieceContains.at(0).at(i);
	}
	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		newPieceContains.at(i).at(2) = pieceContains.at(1).at(i);
	}
	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		newPieceContains.at(i).at(1) = pieceContains.at(2).at(i);
	}
	for (int i = 0; i < PIECE_WIDTH; i++)
	{
		newPieceContains.at(i).at(0) = pieceContains.at(3).at(i);
	}

	m_currentPiece.SetContains(newPieceContains);

	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (newPieceContains.at(i).at(j) != EMPTY_SQUARE)
			{
				m_matrix.at(currCoords.y + i).at(currCoords.x + j) = newPieceContains.at(i).at(j);
			}
		}
	}
}

void Field::ClearLines()
{
	for (int i = m_lineIndexesCount - 1; i > -1; i--)
	{
		for (int j = 1; j < FIELD_WIDTH - 1; j++)
		{
			m_matrix.at(m_lineIndexes.at(i)).at(j) = EMPTY_SQUARE;
		}
		MoveAllDown(m_lineIndexes.at(i));
	}

	switch (m_lineIndexesCount)
	{
	case 1:
		m_score += 10;
		m_linesLeft -= 1;
		break;
	case 2:
		m_score += 30;
		m_linesLeft -= 2;
		break;
	case 3:
		m_score += 70;
		m_linesLeft -= 3;
		break;
	case 4:
		m_score += 150;
		m_linesLeft -= 4;
		break;
	}

	if (m_linesLeft == 0)
	{
		int emptyLines = 0;
		for (int i = 0; i < FIELD_HEIGHT; i++)
		{
			bool isEmpty = true;
			for (int j = 0; j < FIELD_WIDTH; j++)
			{
				if (m_matrix.at(i).at(j) != EMPTY_SQUARE)
				{
					isEmpty = false;
				}
			}
			emptyLines++;
		}
		m_score += 10 * emptyLines;
		Clear();
		m_level++;
		switch (m_level)
		{
		case GAME_LEVEL_2:
			m_linesLeft = GAME_LINES_LEFT_2;
			m_speed = GAME_SPEED_LEVEL_2;
			break;
		case GAME_LEVEL_3:
			m_linesLeft = GAME_LINES_LEFT_3;
			m_speed = GAME_SPEED_LEVEL_3;
			break;
		}
	}

	for (int i = 0; i < MAX_REMOVED_LINES; i++)
	{
		m_lineIndexes.at(i) = -1;
	}
	m_lineIndexesCount = 0;
}

void Field::Clear()
{
	for (int i = 0; i < FIELD_HEIGHT - 1; i++)
	{
		for (int j = 1; j < FIELD_WIDTH - 1; j++)
		{
			if (m_matrix.at(i).at(j) != EMPTY_SQUARE)
			{
				m_matrix.at(i).at(j) = EMPTY_SQUARE;
			}
		}
	}
}

bool Field::IsPaused()
{
	return m_isPaused;
}

Piece Field::GetCurrentPiece()
{
	return m_currentPiece;
}

Piece Field::GetNextPiece()
{
	return m_nextPiece;
}

void Field::SetNextPiece()
{
	m_nextPiece = GetRandomPiece();
}

void Field::SetCurrentPiece()
{
	m_currentPiece = m_nextPiece;
}

void Field::SetNeededNewPiece()
{
	m_isNeededNewPiece = true;
}

void Field::ResetScore()
{
	m_score = 0;
}

void Field::ResetLevel()
{
	m_level = GAME_LEVEL_1;
}

void Field::ResetSpeed()
{
	m_speed = GAME_SPEED_LEVEL_1;
}

void Field::ResetLinesLeft()
{
	m_linesLeft = GAME_LINES_LEFT_1;
}

void Field::Pause()
{
	m_isPaused = true;
}

void Field::Unpause()
{
	m_isPaused = false;
}

Piece Field::GetRandomPiece()
{
	return ALL_PIECES.at(GenerateRandomIndex());
}
