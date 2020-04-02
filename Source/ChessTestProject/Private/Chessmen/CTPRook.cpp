#include "Chessmen/CTPRook.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

ACTPRook::ACTPRook()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> FoundMesh(TEXT("StaticMesh'/Game/Meshes/Rook.Rook'"));
	if (FoundMesh.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(FoundMesh.Object);
	}
	FigureScore = 50;
}

TArray<UCTPBoardPiece*> ACTPRook::GetAvailableMoves()
{
	TArray<FGridRows> BoardGridOfRows = ChessBoard->GetBoardPieces();
	TArray<UCTPBoardPiece*> AvailableMoves;

	
	const FVector2D Coord = CurrentPiece->GetPieceCoord();
	for(auto i = (Coord.X+1); i < 8; ++i)
	{
		if(BoardGridOfRows[i][Coord.Y]->GetCurrentState() == EPieceState::CS_Figure)
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
	return AvailableMoves;
}
