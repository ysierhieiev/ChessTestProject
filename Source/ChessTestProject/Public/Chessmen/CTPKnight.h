#pragma once

#include "CoreMinimal.h"
#include "Chessmen/CTPPawnBase.h"
#include "CTPKnight.generated.h"

UCLASS()
class CHESSTESTPROJECT_API ACTPKnight : public ACTPPawnBase
{
	GENERATED_BODY()

public:

	ACTPKnight();

	TArray<UCTPBoardPiece*> GetAvailableMoves() override;

};
