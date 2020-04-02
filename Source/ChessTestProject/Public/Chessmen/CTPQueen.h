#pragma once

#include "CoreMinimal.h"
#include "Chessmen/CTPPawnBase.h"
#include "CTPQueen.generated.h"

UCLASS()
class CHESSTESTPROJECT_API ACTPQueen : public ACTPPawnBase
{
	GENERATED_BODY()

public:

	ACTPQueen();

	TArray<UCTPBoardPiece*> GetAvailableMoves() override;
};
