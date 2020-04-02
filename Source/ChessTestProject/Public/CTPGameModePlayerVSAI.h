#pragma once

#include "Chessmen/CTPPawnBase.h"
#include "Board/CTPBoardPiece.h"
#include "CoreMinimal.h"
#include "CTPGameMode.h"
#include "CTPGameModePlayerVSAI.generated.h"

//Create an event to alert the end of the game and create a widget
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameCompleteSignature, bool, isWhiteWin);

class ACTPBoard;
class ACTPPlayerController;

//Struct for simple AI logic
USTRUCT(BlueprintType)
struct FAIMove
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACTPPawnBase* CurrentFigure;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UCTPBoardPiece*> AvailableMoves;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int AvailableMovesNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int BestMoveIndex;

	//Count the points of each piece.
	int EvaluateBoard()
	{
		int MaxScore = 0, CurrentScore;
		for(auto i = 0; i < AvailableMoves.Num(); ++i)
		{
			if(AvailableMoves[i]->GetCurrentState() == EPieceState::CS_Empty)
			{
				CurrentScore = 10;
			}
			else
			{
				if (auto& Figure = AvailableMoves[i]->GetCurrentFigure())
				{
					CurrentScore = Figure->GetFigureScore();
				}
			}
			if (CurrentScore == MaxScore) continue;
			if (CurrentScore > MaxScore)
			{
				MaxScore = CurrentScore;
				BestMoveIndex = i;
			}
		}
		return MaxScore;
	}

	void Move()
	{
		CurrentFigure->MoveTo(AvailableMoves[BestMoveIndex]);
	}
	
	FAIMove() {}
	
	FAIMove(ACTPPawnBase* NewCurrentFigure)
	{
		CurrentFigure = NewCurrentFigure;
		AvailableMoves = CurrentFigure->GetAvailableMoves();
		AvailableMovesNum = AvailableMoves.Num();
	}
};

UCLASS()
class CHESSTESTPROJECT_API ACTPGameModePlayerVSAI : public ACTPGameMode
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGameCompleteSignature OnGameComplete;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gamemode")
	ACTPBoard* GameBoard;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gamemode")
	ACTPPlayerController* ChessPlayerController;
		
public:

	FORCEINLINE void SetPlayerController(ACTPPlayerController* NewChessPlayerController) { ChessPlayerController = NewChessPlayerController; }
	
	FORCEINLINE void SetBoard(ACTPBoard* NewBoard) { GameBoard = NewBoard; }
	
	void CompleteGame(bool isWhiteWin);

	//Activate netx AI step
	void MoveAI();
};
