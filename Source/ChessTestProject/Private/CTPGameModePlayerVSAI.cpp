#include "CTPGameModePlayerVSAI.h"

#include "Chessmen/CTPKing.h"
#include "Player/CTPPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

TArray<UCTPBoardPiece*> ACTPGameModePlayerVSAI::IsCheck(TArray<ACTPPawnBase*>& Chessmen)
{
	TArray<UCTPBoardPiece*> AvailableCheckMoves;

	for (auto& Figure : Chessmen)
	{
		for (auto BoardPiece : Figure->GetAvailableMoves())
		{
			if (const auto EnemyFigure = BoardPiece->GetCurrentFigure())
			{
				if (UKismetMathLibrary::ClassIsChildOf(EnemyFigure->GetClass(), ACTPKing::StaticClass()))
				{
					AvailableCheckMoves = Figure->GetPathTo(EnemyFigure->GetCurrentPiece());
					SetCurrentGameState(EGameState::GS_Check);
					break;
				}
			}
		}
	}
	return AvailableCheckMoves;
}

void ACTPGameModePlayerVSAI::CompleteGame(ECompleteGameState CompleteState)
{
	OnGameComplete.Broadcast(CompleteState);
}

void ACTPGameModePlayerVSAI::MoveAI()
{		
	auto WhiteChessmen = GameBoard->GetWhiteChessmen();
	
	const auto BlackMoves = IsCheck(WhiteChessmen);

	if (BlackMoves.Num() == 0 && CurrentGameState == EGameState::GS_Check)
	{
		SetCurrentGameState(EGameState::GS_Mat);
		CompleteGame(ECompleteGameState::CGS_WhiteWin);
	}
	
	//Get all available moves for black figures
	auto& BlackChessmen = GameBoard->GetBlackChessmen();
	TArray<FAIMove>  AvailableAIMoves;
	for (auto& Figure : BlackChessmen)
	{
		auto TMPAIMove = FAIMove(Figure, BlackMoves);
		if (TMPAIMove.AvailableMovesNum > 0)
		{
			AvailableAIMoves.Add(TMPAIMove);
		}
	}
	if (AvailableAIMoves.Num() == 0)
	{
		if (CurrentGameState == EGameState::GS_Play)
		{
			CompleteGame(ECompleteGameState::CGS_Stalemate);
		}
		else
		{
			CompleteGame(ECompleteGameState::CGS_WhiteWin);
		}
	}
	
	int BestValue = -9999;
	TArray<FAIMove> BestFigureToMove;
	
	for (auto Move : AvailableAIMoves)
	{
		const auto CurrentValue = Move.EvaluateBoard();
		if(CurrentValue == BestValue)
		{
			BestFigureToMove.Add(Move);
		}
		if (CurrentValue > BestValue)
		{
			BestValue = CurrentValue;
			BestFigureToMove.Empty();
			BestFigureToMove.Add(Move);
		}
	}
	BestFigureToMove[FMath::RandRange(0, BestFigureToMove.Num()-1)].Move();
	SetCurrentGameState(EGameState::GS_Play);


	//Check if player can move
	int AvailableCountMove = 0;
	for (auto& Figure : WhiteChessmen)
	{			
		AvailableCountMove += Figure->GetAvailableMoves().Num();
	}
	if (AvailableCountMove == 0)
	{
		CompleteGame(ECompleteGameState::CGS_Stalemate);
	}

	//Check if Chess Check
	const auto WhiteMoves = IsCheck(BlackChessmen);
	
	if(WhiteMoves.Num() == 0 && CurrentGameState == EGameState::GS_Check)
	{
		SetCurrentGameState(EGameState::GS_Mat);
		CompleteGame(ECompleteGameState::CGS_BlackWin);
	}
	ChessPlayerController->PlayerMove(WhiteMoves);
}		
