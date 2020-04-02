#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "CTPBoardPiece.generated.h"

class ACTPPawnBase;
class ACTPBoard;

UENUM(BlueprintType)
enum class EPieceState : uint8
{
	CS_Empty = 0 			UMETA(DisplayName = "Empty"),
	CS_Figure				UMETA(DisplayName = "Figure"),
	CS_Highlighted			UMETA(DisplayName = "Highlighted"),
	CS_EnemyHighlighted		UMETA(DisplayName = "EnemyHighlighted")
};

UCLASS()
class CHESSTESTPROJECT_API UCTPBoardPiece : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UCTPBoardPiece();

protected:

	EPieceState CurrentState = EPieceState::CS_Empty;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ChessBoard")
	bool isWhite = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ChessBoard")
	UMaterial* LightMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ChessBoard")
	UMaterial* DarkMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ChessBoard")
	UMaterial* HighlightedMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ChessBoard")
	UMaterial* EnemyHighlightedMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ChessBoard")
	FVector2D PieceCoord;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ChessBoard")
	ACTPPawnBase* CurrentFigure;

public:

	void SetFigure(ACTPPawnBase* NewFigure = nullptr);

	FORCEINLINE void SetCoords(FVector2D NewCoord) { PieceCoord = NewCoord; }

	FORCEINLINE void SetStatus(EPieceState NewState) { CurrentState = NewState; }

	UFUNCTION(BlueprintCallable)
	void SetWhite();

	//Set default color of piece
	UFUNCTION(BlueprintCallable)
	void ReturnToDefault();

	//Highlight piece
	UFUNCTION(BlueprintCallable)
	void HighlightPiece();

	//Highlight piece with enemy
	UFUNCTION(BlueprintCallable)
	void EnemyHighlightPiece();

	FORCEINLINE ACTPPawnBase*& GetCurrentFigure() { return CurrentFigure; }

	FORCEINLINE FVector2D GetPieceCoord() const { return PieceCoord; }

	FORCEINLINE EPieceState GetCurrentState() const { return CurrentState; }
};
