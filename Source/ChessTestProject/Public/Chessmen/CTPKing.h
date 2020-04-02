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

	TArray<UCTPBoardPiece*> GetAvailableMoves() override;

protected:
	
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
