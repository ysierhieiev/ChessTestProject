#pragma once

#include "CoreMinimal.h"
#include "Chessmen/CTPPawnBase.h"
#include "CTPRook.generated.h"

UCLASS()
class CHESSTESTPROJECT_API ACTPRook : public ACTPPawnBase
{
	GENERATED_BODY()

public:

	ACTPRook();

	TArray<UCTPBoardPiece*> GetAvailableMoves(bool HighlightPieces) override;

	TArray<UCTPBoardPiece*> GetPathTo(UCTPBoardPiece* TargetPiece) override;
};
