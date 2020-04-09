#include "Chessmen/CTPPawn.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

ACTPPawn::ACTPPawn()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> FoundMesh(TEXT("StaticMesh'/Game/Meshes/Pawn.Pawn'"));
	if (FoundMesh.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(FoundMesh.Object);
	}
	FigureScore = 15;
}

TArray<UCTPBoardPiece*> ACTPPawn::GetAvailableMoves(bool HighlightPieces)
{
	TArray<FGridRows> BoardGridOfRows = ChessBoard->GetBoardPieces();
	TArray<UCTPBoardPiece*> AvailableMoves;

	int FigureDirection = -1;
	if (isWhite)
	{
		FigureDirection *= -1;
	}
	const FVector2D Coord = CurrentPiece->GetPieceCoord();
	const int OneForwardMove = Coord.X + (1 * FigureDirection);
	const int TwoForwardMove = Coord.X + (2 * FigureDirection);
	const int OneRightMove = Coord.Y + 1;
	const int OneLeftMove = Coord.Y - 1;
	
	if ((0 <= OneForwardMove) && ( OneForwardMove < 8 ))
	{
		if(BoardGridOfRows[OneForwardMove][Coord.Y]->GetCurrentState() == EPieceState::CS_Empty)
		{
			if (HighlightPieces)
			{
				BoardGridOfRows[OneForwardMove][Coord.Y]->HighlightPiece();
			}
			AvailableMoves.Add(BoardGridOfRows[OneForwardMove][Coord.Y]);
		}

		
		if ( 0 <= OneLeftMove )
		{
			if (BoardGridOfRows[OneForwardMove][OneLeftMove]->GetCurrentState() == EPieceState::CS_Figure)
			{
				if(BoardGridOfRows[OneForwardMove][OneLeftMove]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
				{
					if (HighlightPieces)
					{
						BoardGridOfRows[OneForwardMove][OneLeftMove]->EnemyHighlightPiece();
					}
					AvailableMoves.Add(BoardGridOfRows[OneForwardMove][OneLeftMove]);
				}
			}
		}

		if (OneRightMove < 8)
		{
			if (BoardGridOfRows[OneForwardMove][OneRightMove]->GetCurrentState() == EPieceState::CS_Figure)
			{
				if (BoardGridOfRows[OneForwardMove][OneRightMove]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
				{
					if (HighlightPieces)
					{
						BoardGridOfRows[OneForwardMove][OneRightMove]->EnemyHighlightPiece();
					}
					AvailableMoves.Add(BoardGridOfRows[OneForwardMove][OneRightMove]);
				}
			}
		}		
		
	}
	if((0 <= TwoForwardMove) && (TwoForwardMove < 8) && isCanTwoStepMove)
	{
		if (BoardGridOfRows[TwoForwardMove][Coord.Y]->GetCurrentState() == EPieceState::CS_Empty)
		{
			if (HighlightPieces)
			{
				BoardGridOfRows[TwoForwardMove][Coord.Y]->HighlightPiece();
			}
			AvailableMoves.Add(BoardGridOfRows[TwoForwardMove][Coord.Y]);
		}		
	}
	
	return AvailableMoves;
}

TArray<UCTPBoardPiece*> ACTPPawn::GetPathTo(UCTPBoardPiece* TargetPiece)
{
	TArray<UCTPBoardPiece*> ReturnPieces;
	ReturnPieces.Add(GetCurrentPiece());
	return ReturnPieces;
}

void ACTPPawn::MoveTo(UCTPBoardPiece* TargetPiece)
{
	ACTPPawnBase::MoveTo(TargetPiece);

	isCanTwoStepMove = false;
}
