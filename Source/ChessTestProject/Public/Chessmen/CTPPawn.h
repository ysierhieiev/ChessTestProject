#pragma once

#include "CoreMinimal.h"
#include "Chessmen/CTPPawnBase.h"
#include "CTPPawn.generated.h"

UCLASS()
class CHESSTESTPROJECT_API ACTPPawn : public ACTPPawnBase
{
	GENERATED_BODY()

public:

	ACTPPawn();
	
	TArray<UCTPBoardPiece*> GetAvailableMoves(bool HighlightPieces) override;

	TArray<UCTPBoardPiece*> GetPathTo(UCTPBoardPiece* TargetPiece) override;

	void MoveTo(UCTPBoardPiece* TargetPiece) override;
	
private:
	
	bool isCanTwoStepMove = true;
};
