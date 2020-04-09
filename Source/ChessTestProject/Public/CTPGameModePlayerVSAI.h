#pragma once

#include "Chessmen/CTPPawnBase.h"
#include "Board/CTPBoardPiece.h"
#include "CoreMinimal.h"
#include "CTPGameMode.h"
#include "CTPGameModePlayerVSAI.generated.h"

UENUM(BlueprintType)
enum class ECompleteGameState : uint8
{
	CGS_WhiteWin = 0 		UMETA(DisplayName = "WhiteWin"),
	CGS_BlackWin			UMETA(DisplayName = "BlackWin"),
	CGS_Stalemate			UMETA(DisplayName = "Stalemate")};

UENUM(BlueprintType)
enum class EGameState : uint8
{
	GS_Play = 0 			UMETA(DisplayName = "Play"),
	GS_Check				UMETA(DisplayName = "Check"),
	GS_Mat					UMETA(DisplayName = "Mat")
};


//Create an event to alert the end of the game and create a widget
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameCompleteSignature, ECompleteGameState, isWhiteWin);

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
		return (MaxScore - (CurrentFigure->GetFigureScore()/2));
	}

	void Move()
	{
		CurrentFigure->MoveTo(AvailableMoves[BestMoveIndex]);
	}
	
	FAIMove() {}
	
	FAIMove(ACTPPawnBase* NewCurrentFigure, TArray<UCTPBoardPiece*> AvailableCheckMoves)
	{
		CurrentFigure = NewCurrentFigure;
		if(AvailableCheckMoves.Num() > 0)
		{
			AvailableMoves = CurrentFigure->GetAvailableCheckMoves(AvailableCheckMoves);
		}
		else
		{
			AvailableMoves = CurrentFigure->GetAvailableMoves();
		}			
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
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gamemode")
	EGameState CurrentGameState = EGameState::GS_Play;

	TArray<UCTPBoardPiece*> IsCheck(TArray<ACTPPawnBase*>& Chessmen);
	
public:
	FORCEINLINE void SetCurrentGameState(EGameState NewCurrentGameState) { CurrentGameState = NewCurrentGameState; }

	FORCEINLINE EGameState GetCurrentGameState() { return CurrentGameState; }

	FORCEINLINE void SetPlayerController(ACTPPlayerController* NewChessPlayerController) { ChessPlayerController = NewChessPlayerController; }
	
	FORCEINLINE void SetBoard(ACTPBoard* NewBoard) { GameBoard = NewBoard; }
	
	void CompleteGame(ECompleteGameState CompleteState);

	//Activate netx AI step
	void MoveAI();
};
