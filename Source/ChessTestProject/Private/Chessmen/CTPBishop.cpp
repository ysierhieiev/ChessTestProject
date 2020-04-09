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

TArray<UCTPBoardPiece*> ACTPBishop::GetAvailableMoves(bool HighlightPieces)
{
	TArray<FGridRows> BoardGridOfRows = ChessBoard->GetBoardPieces();
	TArray<UCTPBoardPiece*> AvailableMoves;
	
	const FVector2D Coord = CurrentPiece->GetPieceCoord();

	int Xpos[] = { 1, -1, 1,-1 };
	int Ypos[] = { 1, -1, -1, 1 };


	for (auto dir = 0; dir < 4 ; ++dir)
	{
		for (auto i = (Coord.X + Xpos[dir]), j = (Coord.Y + Ypos[dir]); CompareBorders(dir, i, j); i += Xpos[dir], j +=Ypos[dir])
		{
			if (BoardGridOfRows[i][j]->GetCurrentState() == EPieceState::CS_Figure)
			{
				if (BoardGridOfRows[i][j]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
				{
					AvailableMoves.Add(BoardGridOfRows[i][j]);
					if (HighlightPieces)
					{
						BoardGridOfRows[i][j]->EnemyHighlightPiece();
					}
				}
				break;
			}
			if (HighlightPieces)
			{
				BoardGridOfRows[i][j]->HighlightPiece();
			}
			AvailableMoves.Add(BoardGridOfRows[i][j]);
		}
	}
	return AvailableMoves;
}

TArray<UCTPBoardPiece*> ACTPBishop::GetPathTo(UCTPBoardPiece* TargetPiece)
{
	const auto StartCoord = GetCurrentPiece()->GetPieceCoord();
	auto LastCoord = TargetPiece->GetPieceCoord();
	
	auto Xdif = LastCoord.X - StartCoord.X;
	if(Xdif > 0)
	{
		Xdif = 1;
	}
	else if(Xdif == 0)
	{
		Xdif = 0;
	}
	else
	{
		Xdif = -1;
	}

	auto Ydif = LastCoord.Y - StartCoord.Y;
	if (Ydif > 0)
	{
		Ydif = 1;
	}
	else if (Ydif == 0)
	{
		Ydif = 0;
	}
	else
	{
		Ydif = -1;
	}
	TArray<UCTPBoardPiece*> ReturnPieces;
	for(int i = StartCoord.X, j = StartCoord.Y; i != LastCoord.X && j != LastCoord.Y; i+=Xdif, j+= Ydif)
	{
		ReturnPieces.Add(ChessBoard->GetBoardPieces()[i][j]);
	}

	return ReturnPieces;
}

