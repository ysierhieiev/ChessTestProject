#include "CTPGameModePlayerVSAI.h"
#include "Player/CTPPlayerController.h"


void ACTPGameModePlayerVSAI::CompleteGame(bool isWhiteWin)
{
	OnGameComplete.Broadcast(isWhiteWin);
}

void ACTPGameModePlayerVSAI::MoveAI()
{
	//Get all available moves for black figures
	auto Chessmen = GameBoard->GetBlackChessmen();
	TArray<FAIMove>  AvailableAIMoves;
	for (auto& Figure : Chessmen)
	{
		auto TMPAIMove = FAIMove(Figure);
		if (TMPAIMove.AvailableMovesNum > 0)
			AvailableAIMoves.Add(TMPAIMove);
	}
	if (AvailableAIMoves.Num() == 0)
	{
		CompleteGame(true);
	}
	// Random move or calculated piece score
	if (FMath::RandBool())
	{		
		auto& Move = AvailableAIMoves[FMath::RandRange(0, (AvailableAIMoves.Num() - 1))];

		Move.CurrentFigure->MoveTo(Move.AvailableMoves[FMath::RandRange(0, (Move.AvailableMoves.Num() - 1))]);

		ChessPlayerController->PlayerMove();
	}
	else
	{
		int BestValue = -9999;
		FAIMove BestFigureToMove;

		for (auto Move : AvailableAIMoves)
		{
			const auto CurrentValue = Move.EvaluateBoard();
			if (CurrentValue > BestValue)
			{
				BestValue = CurrentValue;
				BestFigureToMove = Move;
			}
		}
		BestFigureToMove.Move();
		ChessPlayerController->PlayerMove();
	}		
}