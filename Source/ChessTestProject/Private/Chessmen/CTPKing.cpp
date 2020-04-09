#include "Chessmen/CTPKing.h"
#include "UObject/ConstructorHelpers.h"
#include "CTPGameModePlayerVSAI.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ACTPKing::ACTPKing()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> FoundMesh(TEXT("StaticMesh'/Game/Meshes/King.King'"));
	if (FoundMesh.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(FoundMesh.Object);
	}
	FigureScore = 900;
}

TArray<UCTPBoardPiece*> ACTPKing::GetAvailableMoves(bool  HighlightPieces)
{
	TArray<FGridRows> BoardGridOfRows = ChessBoard->GetBoardPieces();
	TArray<UCTPBoardPiece*> AvailableMoves;
	const FVector2D Coord = CurrentPiece->GetPieceCoord();
	for(auto i = -1; i < 2; ++i)
	{
		if (0 > (Coord.X + i) || (Coord.X + i) >= 8) continue;
		for (auto j = -1; j < 2; ++j)
		{
			if ((i == 0 && j == 0) ||(0 > (Coord.X + i) || (Coord.X + i) >= 8))	continue;

			if(BoardGridOfRows[Coord.X + i][Coord.Y + j]->GetCurrentState() == EPieceState::CS_Figure)
			{
				if (BoardGridOfRows[Coord.X + i][Coord.Y + j]->GetCurrentFigure()->GetIsWhiteColor() != isWhite)
				{
					AvailableMoves.Add(BoardGridOfRows[Coord.X + i][Coord.Y + j]);
					if (HighlightPieces)
					{
						BoardGridOfRows[Coord.X + i][Coord.Y + j]->EnemyHighlightPiece();
					}
				}
			}
			else if(BoardGridOfRows[Coord.X + i][Coord.Y + j]->GetCurrentState() == EPieceState::CS_Empty)
			{
				if (HighlightPieces)
				{
					BoardGridOfRows[Coord.X + i][Coord.Y + j]->HighlightPiece();
				}
				AvailableMoves.Add(BoardGridOfRows[Coord.X + i][Coord.Y + j]);
			}		
		}		
	}
	return AvailableMoves;
}

TArray<UCTPBoardPiece*> ACTPKing::GetPathTo(UCTPBoardPiece* TargetPiece)
{
	TArray<UCTPBoardPiece*> ReturnPieces;
	ReturnPieces.Add(GetCurrentPiece());
	return ReturnPieces;
}

TArray<UCTPBoardPiece*> ACTPKing::GetAvailableCheckMoves(TArray<UCTPBoardPiece*> AvailableCheckPieces, bool HighlightPieces)
{
	return GetAvailableMoves(HighlightPieces);
}

void ACTPKing::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		auto GameMode = Cast<ACTPGameModePlayerVSAI>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			if(isWhite)
			{
				GameMode->CompleteGame(ECompleteGameState::CGS_BlackWin);
			}
			else
			{
				GameMode->CompleteGame(ECompleteGameState::CGS_WhiteWin);
			}
			
		}
	}
}
