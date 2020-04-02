#include "Chessmen/CTPQueen.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

ACTPQueen::ACTPQueen()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> FoundMesh(TEXT("StaticMesh'/Game/Meshes/Queen.Queen'"));
	if (FoundMesh.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(FoundMesh.Object);
	}
	FigureScore = 90;
}

TArray<UCTPBoardPiece*> ACTPQueen::GetAvailableMoves()
{
	TArray<FGridRows> BoardGridOfRows = ChessBoard->GetBoardPieces();
	TArray<UCTPBoardPiece*> AvailableMoves;


	const FVector2D Coord = CurrentPiece->GetPieceCoord();
	for (auto i = (Coord.X + 1); i < 8; ++i)
	{
		if (BoardGridOfRows[i][Coord.Y]->GetCurrentState() == EPieceState::CS_Figure)
		{
			if (BoardGridOfRows[i][Coord.Y]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
			{
				AvailableMoves.Add(BoardGridOfRows[i][Coord.Y]);
				if (isWhite)
				BoardGridOfRows[i][Coord.Y]->EnemyHighlightPiece();
			}
			break;
		}
		if (isWhite)
		BoardGridOfRows[i][Coord.Y]->HighlightPiece();
		AvailableMoves.Add(BoardGridOfRows[i][Coord.Y]);
	}
	for (auto i = (Coord.X - 1); 0 <= i; --i)
	{
		if (BoardGridOfRows[i][Coord.Y]->GetCurrentState() == EPieceState::CS_Figure)
		{
			if (BoardGridOfRows[i][Coord.Y]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
			{
				AvailableMoves.Add(BoardGridOfRows[i][Coord.Y]);
				if (isWhite)
				BoardGridOfRows[i][Coord.Y]->EnemyHighlightPiece();
			}
			break;
		}
		if (isWhite)
		BoardGridOfRows[i][Coord.Y]->HighlightPiece();
		AvailableMoves.Add(BoardGridOfRows[i][Coord.Y]);
	}
	for (auto i = (Coord.Y + 1); i < 8; ++i)
	{
		if (BoardGridOfRows[Coord.X][i]->GetCurrentState() == EPieceState::CS_Figure)
		{
			if (BoardGridOfRows[Coord.X][i]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
			{
				AvailableMoves.Add(BoardGridOfRows[Coord.X][i]);
				if (isWhite)
				BoardGridOfRows[Coord.X][i]->EnemyHighlightPiece();
			}
			break;
		}
		if (isWhite)
		BoardGridOfRows[Coord.X][i]->HighlightPiece();
		AvailableMoves.Add(BoardGridOfRows[Coord.X][i]);
	}
	for (auto i = (Coord.Y - 1); 0 <= i; --i)
	{
		if (BoardGridOfRows[Coord.X][i]->GetCurrentState() == EPieceState::CS_Figure)
		{
			if (BoardGridOfRows[Coord.X][i]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
			{
				AvailableMoves.Add(BoardGridOfRows[Coord.X][i]);
				if (isWhite)
				BoardGridOfRows[Coord.X][i]->EnemyHighlightPiece();
			}
			break;
		}
		if (isWhite)
		BoardGridOfRows[Coord.X][i]->HighlightPiece();
		AvailableMoves.Add(BoardGridOfRows[Coord.X][i]);
	}
	for (auto i = (Coord.X + 1), j = (Coord.Y + 1); i < 8 && j < 8; ++i, ++j)
	{
		if (BoardGridOfRows[i][j]->GetCurrentState() == EPieceState::CS_Figure)
		{
			if (BoardGridOfRows[i][j]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
			{
				AvailableMoves.Add(BoardGridOfRows[i][j]);
				if (isWhite)
				BoardGridOfRows[i][j]->EnemyHighlightPiece();
			}
			break;
		}
		if (isWhite)
		BoardGridOfRows[i][j]->HighlightPiece();
		AvailableMoves.Add(BoardGridOfRows[i][j]);
	}
	for (auto i = (Coord.X - 1), j = (Coord.Y - 1); 0 <= i && 0 <= j; --i, --j)
	{
		if (BoardGridOfRows[i][j]->GetCurrentState() == EPieceState::CS_Figure)
		{
			if (BoardGridOfRows[i][j]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
			{
				AvailableMoves.Add(BoardGridOfRows[i][j]);
				if (isWhite)
				BoardGridOfRows[i][j]->EnemyHighlightPiece();
			}
			break;
		}
		if (isWhite)
		BoardGridOfRows[i][j]->HighlightPiece();
		AvailableMoves.Add(BoardGridOfRows[i][j]);
	}
	for (auto i = (Coord.X + 1), j = (Coord.Y - 1); i < 8 && 0 <= j; ++i, --j)
	{
		if (BoardGridOfRows[i][j]->GetCurrentState() == EPieceState::CS_Figure)
		{
			if (BoardGridOfRows[i][j]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
			{
				AvailableMoves.Add(BoardGridOfRows[i][j]);
				if (isWhite)
				BoardGridOfRows[i][j]->EnemyHighlightPiece();
			}
			break;
		}
		if (isWhite)
		BoardGridOfRows[i][j]->HighlightPiece();
		AvailableMoves.Add(BoardGridOfRows[i][j]);
	}
	for (auto i = (Coord.X - 1), j = (Coord.Y + 1); 0 <= i && j < 8; --i, ++j)
	{
		if (BoardGridOfRows[i][j]->GetCurrentState() == EPieceState::CS_Figure)
		{
			if (BoardGridOfRows[i][j]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
			{
				AvailableMoves.Add(BoardGridOfRows[i][j]);
				if (isWhite)
				BoardGridOfRows[i][j]->EnemyHighlightPiece();
			}
			break;
		}
		if (isWhite)
		BoardGridOfRows[i][j]->HighlightPiece();
		AvailableMoves.Add(BoardGridOfRows[i][j]);
	}
	return AvailableMoves;
}
