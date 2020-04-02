#include "Board/CTPBoard.h"
#include "Board/CTPBoardPiece.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SceneComponent.h"
#include "Materials/Material.h"
#include "Chessmen/CTPPawnBase.h"
#include "CTPGameModePlayerVSAI.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

ACTPBoard::ACTPBoard()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CreateBoard();	
}

void ACTPBoard::BeginPlay()
{
	Super::BeginPlay();

	SpawnChessmen();

	auto GameMode = Cast<ACTPGameModePlayerVSAI>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->SetBoard(this);
	}	
}

void ACTPBoard::CreateBoard()
{	
	for (auto i = 0u; i < 8u; ++i)
	{
		GridOfRows.Add(FGridRows());
		for (auto j = 0u; j < 8u; ++j)
		{			
			GridOfRows[i].Cols.Add(CreateDefaultSubobject<UCTPBoardPiece>(*FString("Piece" + FString::FromInt(i) + FString::FromInt(j)), false));
						
			GridOfRows[i][j]->SetupAttachment(RootComponent);
			GridOfRows[i][j]->SetRelativeLocation(FVector(i * 400, j * 400, 0));
			GridOfRows[i][j]->SetCoords(FVector2D(i, j));

			if((i+j) % 2 != 0)
			{
				GridOfRows[i][j]->SetWhite();
			}		
		}
	}
}

void ACTPBoard::SpawnChessmen()
{
	if (BPChessmenClasses.Num() == 6)
	{
		for (auto i = 0; i < 8; ++i)
		{
			WhiteChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[0], GridOfRows[1][i]->GetComponentLocation() + FVector(200.f,200.f,0.f), FRotator::ZeroRotator));
			BlackChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[0], GridOfRows[6][i]->GetComponentLocation() + FVector(200.f, 200.f, 0.f), FRotator::ZeroRotator));
			WhiteChessmen.Last()->SetDefaultValues(this, GridOfRows[1][i]);
			BlackChessmen.Last()->SetDefaultValues(this, GridOfRows[6][i], false);
		}
				
		//Spawn Rooks
		WhiteChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[1], GridOfRows[0][0]->GetComponentLocation() + FVector(200.f, 200.f, 190.f), FRotator::ZeroRotator));
		WhiteChessmen.Last()->SetDefaultValues(this, GridOfRows[0][0]);
		WhiteChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[1], GridOfRows[0][7]->GetComponentLocation() + FVector(200.f, 200.f, 190.f), FRotator::ZeroRotator));
		WhiteChessmen.Last()->SetDefaultValues(this, GridOfRows[0][7]);
				
		BlackChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[1], GridOfRows[7][0]->GetComponentLocation() + FVector(200.f, 200.f, 190.f), FRotator::ZeroRotator));
		BlackChessmen.Last()->SetDefaultValues(this, GridOfRows[7][0], false);
		BlackChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[1], GridOfRows[7][7]->GetComponentLocation() + FVector(200.f, 200.f, 190.f), FRotator::ZeroRotator));
		BlackChessmen.Last()->SetDefaultValues(this, GridOfRows[7][7], false);
			
		//Spawn Bishops
		WhiteChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[2], GridOfRows[0][1]->GetComponentLocation() + FVector(200.f, 200.f, 0.f), FRotator::ZeroRotator));
		WhiteChessmen.Last()->SetDefaultValues(this, GridOfRows[0][1]);
		WhiteChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[2], GridOfRows[0][6]->GetComponentLocation() + FVector(200.f, 200.f, 0.f), FRotator::ZeroRotator));
		WhiteChessmen.Last()->SetDefaultValues(this, GridOfRows[0][6]);

		BlackChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[2], GridOfRows[7][1]->GetComponentLocation() + FVector(200.f, 200.f, 0.f), FRotator::ZeroRotator));
		BlackChessmen.Last()->SetDefaultValues(this, GridOfRows[7][1], false);
		BlackChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[2], GridOfRows[7][6]->GetComponentLocation() + FVector(200.f, 200.f, 0.f), FRotator::ZeroRotator));
		BlackChessmen.Last()->SetDefaultValues(this, GridOfRows[7][6], false);

		//Spawn Knight
		WhiteChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[3], GridOfRows[0][2]->GetComponentLocation() + FVector(200.f, 200.f, 90.f), FRotator::ZeroRotator + FRotator(0.f, -90.f,0.f)));
		WhiteChessmen.Last()->SetDefaultValues(this, GridOfRows[0][2]);
		WhiteChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[3], GridOfRows[0][5]->GetComponentLocation() + FVector(200.f, 200.f, 90.f), FRotator::ZeroRotator + FRotator(0.f, -90.f, 0.f)));
		WhiteChessmen.Last()->SetDefaultValues(this, GridOfRows[0][5]);
		
		BlackChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[3], GridOfRows[7][2]->GetComponentLocation() + FVector(200.f, 200.f, 90.f), FRotator::ZeroRotator + FRotator(0.f, 90.f, 0.f)));
		BlackChessmen.Last()->SetDefaultValues(this, GridOfRows[7][2], false);
		BlackChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[3], GridOfRows[7][5]->GetComponentLocation() + FVector(200.f, 200.f, 90.f), FRotator::ZeroRotator + FRotator(0.f, 90.f, 0.f)));
		BlackChessmen.Last()->SetDefaultValues(this, GridOfRows[7][5], false);
		
		//Spawn Queens
		WhiteChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[4], GridOfRows[0][3]->GetComponentLocation() + FVector(200.f, 200.f, 280.f), FRotator::ZeroRotator));
		WhiteChessmen.Last()->SetDefaultValues(this, GridOfRows[0][3]);
		BlackChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[4], GridOfRows[7][3]->GetComponentLocation() + FVector(200.f, 200.f, 280.f), FRotator::ZeroRotator));
		BlackChessmen.Last()->SetDefaultValues(this, GridOfRows[7][3], false);
				
		//Spawn Kings
		WhiteChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[5], GridOfRows[0][4]->GetComponentLocation() + FVector(200.f, 200.f, 310.f), FRotator::ZeroRotator));
		WhiteChessmen.Last()->SetDefaultValues(this, GridOfRows[0][4]);
		BlackChessmen.Add(GetWorld()->SpawnActor<ACTPPawnBase>(BPChessmenClasses[5], GridOfRows[7][4]->GetComponentLocation() + FVector(200.f, 200.f, 310.f), FRotator::ZeroRotator));
		BlackChessmen.Last()->SetDefaultValues(this, GridOfRows[7][4], false);
	}	
}
