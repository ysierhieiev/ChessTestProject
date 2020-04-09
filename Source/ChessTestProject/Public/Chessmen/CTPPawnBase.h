#pragma once

#include "Board/CTPBoard.h"
#include "Board/CTPBoardPiece.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTPPawnBase.generated.h"

class UMaterial;

UCLASS()
class CHESSTESTPROJECT_API ACTPPawnBase : public AActor
{
	GENERATED_BODY()

public:
	ACTPPawnBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Figure", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Figure")
	bool isWhite = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Figure")
	UMaterial* WhiteMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Figure")
	UMaterial* BlackMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Figure")
	UMaterial* SelectedMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Figure")
	UCTPBoardPiece* CurrentPiece = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Figure")
	ACTPBoard* ChessBoard;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Figure")
	int FigureScore;

	bool CompareBorders(int CompareIndex, int A = 0, int B = 0);
public:

	void SetDefaultValues(ACTPBoard* Board, UCTPBoardPiece* Piece, bool isWhiteFigure = true );
	
	FORCEINLINE bool GetIsWhiteColor() const { return isWhite; };

	FORCEINLINE UCTPBoardPiece* GetCurrentPiece() const { return CurrentPiece; }

	FORCEINLINE int GetFigureScore() const { return FigureScore; };
	
	void SetCurrentPiece(UCTPBoardPiece* NewPiece);

	//Return an array of pieces to which the figure can move.
	virtual TArray<UCTPBoardPiece*> GetAvailableMoves(bool HighlightPieces = false);

	virtual TArray<UCTPBoardPiece*> GetAvailableCheckMoves(TArray<UCTPBoardPiece*> AvailableCheckPieces, bool HighlightPieces = false);

	virtual void MoveTo(UCTPBoardPiece* TargetPiece);
	
	virtual TArray<UCTPBoardPiece*> GetPathTo(UCTPBoardPiece* TargetPiece);
};
