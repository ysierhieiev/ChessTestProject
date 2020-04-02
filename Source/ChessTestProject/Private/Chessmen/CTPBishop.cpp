#include "Chessmen/CTPBishop.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

ACTPBishop::ACTPBishop()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> FoundMesh(TEXT("StaticMesh'/Game/Meshes/Bishop.Bishop'"));
	if (FoundMesh.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(FoundMesh.Object);
	}
	FigureScore = 30;
}

TArray<UCTPBoardPiece*> ACTPBishop::GetAvailableMoves()
{
	TArray<FGridRows> BoardGridOfRows = ChessBoard->GetBoardPieces();
	TArray<UCTPBoardPiece*> AvailableMoves;
	
	const FVector2D Coord = CurrentPiece->GetPieceCoord();
	for (auto i = (Coord.X + 1), j = (Coord.Y + 1); i < 8 && j < 8; ++i, ++j)
	{
		if (BoardGridOfRows[i][j]->GetCurrentState() == EPieceState::CS_Figure)
		{
			if (BoardGridOfRows[i][j]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
			{
				AvailableMoves.Add(BoardGridOfRows[i][j]);
				if(isWhite)
				BoardGridOfRows[i][j]->EnemyHighlightPiece();
			}
			break;
		}
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

