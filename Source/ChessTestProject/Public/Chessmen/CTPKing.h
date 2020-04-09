#pragma once

#include "CoreMinimal.h"
#include "Chessmen/CTPPawnBase.h"
#include "CTPKing.generated.h"

UCLASS()
class CHESSTESTPROJECT_API ACTPKing : public ACTPPawnBase
{
	GENERATED_BODY()

public:
	
	ACTPKing();

	TArray<UCTPBoardPiece*> GetAvailableMoves(bool HighlightPieces) override;

	TArray<UCTPBoardPiece*> GetPathTo(UCTPBoardPiece* TargetPiece) override;

	TArray<UCTPBoardPiece*> GetAvailableCheckMoves(TArray<UCTPBoardPiece*> AvailableCheckPieces, bool HighlightPieces = false) override;

protected:
	
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
