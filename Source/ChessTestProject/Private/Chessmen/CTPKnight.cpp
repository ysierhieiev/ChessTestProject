#include "Chessmen/CTPKnight.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

ACTPKnight::ACTPKnight()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> FoundMesh(TEXT("StaticMesh'/Game/Meshes/Knight.Knight'"));
	if (FoundMesh.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(FoundMesh.Object);
	}
	FigureScore = 30;
}

TArray<UCTPBoardPiece*> ACTPKnight::GetAvailableMoves()
{
	TArray<FGridRows> BoardGridOfRows = ChessBoard->GetBoardPieces();
	TArray<UCTPBoardPiece*> AvailableMoves;
	const FVector2D Coord = CurrentPiece->GetPieceCoord();
	const int PosX[] = { (int)Coord.X + 1, (int)Coord.X + 1, (int)Coord.X + 2, (int)Coord.X + 2, (int)Coord.X - 1, (int)Coord.X - 1, (int)Coord.X - 2, (int)Coord.X - 2 };
	const int PosY[] = { (int)Coord.Y - 2, (int)Coord.Y + 2, (int)Coord.Y - 1, (int)Coord.Y + 1, (int)Coord.Y - 2, (int)Coord.Y + 2, (int)Coord.Y - 1, (int)Coord.Y + 1 };
	for (int i = 0; i < 8; i++)
	{
		if ((PosX[i] >= 0 && PosX[i] < 8 && PosY[i] >= 0 && PosY[i] < 8))
		{
			if (BoardGridOfRows[PosX[i]][PosY[i]]->GetCurrentState() == EPieceState::CS_Figure)
			{
				if (BoardGridOfRows[PosX[i]][PosY[i]]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
				{
					AvailableMoves.Add(BoardGridOfRows[PosX[i]][PosY[i]]);
					if (isWhite)
						BoardGridOfRows[PosX[i]][PosY[i]]->EnemyHighlightPiece();
				}
			}
			else if (BoardGridOfRows[PosX[i]][PosY[i]]->GetCurrentState() == EPieceState::CS_Empty)
			{
				if (isWhite)
					BoardGridOfRows[PosX[i]][PosY[i]]->HighlightPiece();
				AvailableMoves.Add(BoardGridOfRows[PosX[i]][PosY[i]]);
			}
		}
	}
	return AvailableMoves;
}
