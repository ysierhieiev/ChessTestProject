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

TArray<UCTPBoardPiece*> ACTPQueen::GetAvailableMoves(bool HighlightPieces)
{
	TArray<FGridRows> BoardGridOfRows = ChessBoard->GetBoardPieces();
	TArray<UCTPBoardPiece*> AvailableMoves;


	const FVector2D Coord = CurrentPiece->GetPieceCoord();
	int Xpos[] = { 1, -1, 0, 0, 1, -1, 1,-1 };
	int Ypos[] = { 0, 0, -1, 1, 1, -1, -1, 1 };
	
	for (auto dir = 0; dir < 8; ++dir)
	{
		for (auto i = (Coord.X + Xpos[dir]), j = (Coord.Y + Ypos[dir]); CompareBorders(dir, i, j); i += Xpos[dir], j += Ypos[dir])
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

TArray<UCTPBoardPiece*> ACTPQueen::GetPathTo(UCTPBoardPiece* TargetPiece)
{
	const auto StartCoord = GetCurrentPiece()->GetPieceCoord();
	auto LastCoord = TargetPiece->GetPieceCoord();

	auto Xdif = LastCoord.X - StartCoord.X;
	if (Xdif > 0)
	{
		Xdif = 1;
	}
	else if (Xdif == 0)
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

	int i = StartCoord.X, j = StartCoord.Y;
	bool XComplete = false, YComplete = false;
	while ((0 <= i && i < 8) || (0 <= j && j < 8))
	{
		ReturnPieces.Add(ChessBoard->GetBoardPieces()[i][j]);
		if (i != LastCoord.X)
		{
			i += Xdif;
		}
		else
		{
			XComplete = true;
		}

		if (j != LastCoord.Y)
		{
			j += Ydif;
		}
		else
		{
			YComplete = true;
		}

		if (XComplete && YComplete)
		{
			break;
		}
	}
	
	return ReturnPieces;
}
