#pragma once

#include "CoreMinimal.h"
#include "Chessmen/CTPPawnBase.h"
#include "CTPBishop.generated.h"

UCLASS()
class CHESSTESTPROJECT_API ACTPBishop : public ACTPPawnBase
{
	GENERATED_BODY()

public:
	
	ACTPBishop();

	TArray<UCTPBoardPiece*> GetAvailableMoves(bool HighlightPieces) override;

	TArray<UCTPBoardPiece*> GetPathTo(UCTPBoardPiece* TargetPiece) override;
};
