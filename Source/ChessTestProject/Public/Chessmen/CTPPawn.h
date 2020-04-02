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
	
	TArray<UCTPBoardPiece*> GetAvailableMoves() override;

};
