#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CTPPlayerController.generated.h"

class ACTPBoard;
class UCTPBoardPiece;
class ACTPPawnBase;
class ACTPGameModePlayerVSAI;

UENUM(BlueprintType)
enum class EControllerState : uint8
{
	CS_Free = 0 			UMETA(DisplayName = "Free"),
	CS_SelectedFigure	 	UMETA(DisplayName = "SelectedFigure"),
	CS_MoveFigure			UMETA(DisplayName = "MoveFigure"),
	CS_MoveCamera 			UMETA(DisplayName = "MoveCamera")
};

UCLASS()
class CHESSTESTPROJECT_API ACTPPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	EControllerState CurrentState = EControllerState::CS_Free;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerController")
	ACTPBoard* GameBoard;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerController")
	ACTPGameModePlayerVSAI* ChessGameMode;
	
	ACTPPawnBase* CurrentSelectedFigure;
	
	TArray<UCTPBoardPiece*> AvailableMoves;

	bool bPlayerCanMove = true;
	
	TArray<UCTPBoardPiece*> AvailableCheckMoves;
public:

	void BeginPlay() override;

	void PlayerMove(TArray<UCTPBoardPiece*> NewAvailableCheckMoves);
	
	FORCEINLINE EControllerState GetCurrentState() { return CurrentState; }
	
	ACTPPlayerController();

	void SetupInputComponent() override;

	void OnLeftMousePressed();
	
	void OnLeftMouseReleased();

};
