#include "Chessmen/CTPPawnBase.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Board/CTPBoard.h"

ACTPPawnBase::ACTPPawnBase()
{
 	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	// Set WhiteMaterial
	const ConstructorHelpers::FObjectFinder<UMaterial> MWhiteAsset(TEXT("Material'/Game/Materials/M_LightMaterial.M_LightMaterial'"));
	if (MWhiteAsset.Succeeded())
	{
		WhiteMaterial = MWhiteAsset.Object;
	}

	// Set BlackMaterial
	const ConstructorHelpers::FObjectFinder<UMaterial> MBlackAsset(TEXT("Material'/Game/Materials/M_DarkMaterial.M_DarkMaterial'"));
	if (MBlackAsset.Succeeded())
	{
		BlackMaterial = MBlackAsset.Object;
	}

	// Set SelectedMaterial
	const ConstructorHelpers::FObjectFinder<UMaterial> MSelectedAsset(TEXT("Material'/Game/Materials/M_SelectedMaterial.M_SelectedMaterial'"));
	if (MSelectedAsset.Succeeded())
	{
		SelectedMaterial = MSelectedAsset.Object;
	}
}

// Called when the game starts or when spawned
void ACTPPawnBase::BeginPlay()
{
	Super::BeginPlay();

	if(isWhite)
	{
		StaticMeshComponent->SetMaterial(0, WhiteMaterial);
	}
	else
	{		
		StaticMeshComponent->SetMaterial(0, BlackMaterial);
	}
}

void ACTPPawnBase::SetDefaultValues(ACTPBoard* Board, UCTPBoardPiece* Piece, bool isWhiteFigure)
{
	ChessBoard = Board;
	CurrentPiece = Piece;
	CurrentPiece->SetFigure(this);	
	if(!isWhiteFigure)
	{
		isWhite = false;
		StaticMeshComponent->SetMaterial(0, BlackMaterial);
	}
}

void ACTPPawnBase::SetCurrentPiece(UCTPBoardPiece* NewPiece)
{
	CurrentPiece = NewPiece;
}

TArray<UCTPBoardPiece*> ACTPPawnBase::GetAvailableMoves()
{
	return {};
}

void ACTPPawnBase::MoveTo(UCTPBoardPiece* TargetPiece)
{
	GetCurrentPiece()->SetFigure(nullptr);
	switch (TargetPiece->GetCurrentState())
	{
	case EPieceState::CS_Figure:
	{
		if(TargetPiece->GetCurrentFigure()->GetIsWhiteColor())
		{
			ChessBoard->GetWhiteChessmen().Remove(TargetPiece->GetCurrentFigure());				
		}
		else
		{
			ChessBoard->GetBlackChessmen().Remove(TargetPiece->GetCurrentFigure());
			UE_LOG(LogTemp, Warning, TEXT("%i"), ChessBoard->GetBlackChessmen().Num());
		}
		TargetPiece->GetCurrentFigure()->Destroy();
	}
	case EPieceState::CS_Empty:
	{
		FVector NewLocation = FVector(TargetPiece->GetComponentLocation().X + 200.f, TargetPiece->GetComponentLocation().Y + 200.f, GetActorLocation().Z);
		SetActorLocation(NewLocation);
		TargetPiece->SetFigure(this);
		SetCurrentPiece(TargetPiece);
		break;
	}
	default:;
	}
}
