#pragma once

#include "CoreMinimal.h"
#include "ChessTestProject/ChessTestProjectGameModeBase.h"
#include "CTPGameMode.generated.h"

UCLASS()
class CHESSTESTPROJECT_API ACTPGameMode : public AChessTestProjectGameModeBase
{
	GENERATED_BODY()

public:

	ACTPGameMode();

	void BeginPlay() override;
};
