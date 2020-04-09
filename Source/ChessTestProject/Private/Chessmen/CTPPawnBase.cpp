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

bool ACTPPawnBase::CompareBorders(int CompareIndex, int A, int B)
{
	if(CompareIndex > 3)
	{
		CompareIndex -= 4;
	}
	switch(CompareIndex)
	{
	case 0: return (A < 8 && B < 8); 
	case 1: return (0 <= A && 0 <= B);
	case 2: return (A < 8 && 0 <= B); 
	case 3: return (0 <= A && B < 8); 
	default: return false;
	}
	return false;
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

TArray<UCTPBoardPiece*> ACTPPawnBase::GetAvailableMoves(bool HighlightPieces)
{
	return {};
}

TArray<UCTPBoardPiece*> ACTPPawnBase::GetAvailableCheckMoves(TArray<UCTPBoardPiece*> AvailableCheckPieces, bool HighlightPieces)
{
	auto Moves = GetAvailableMoves();
	TArray<UCTPBoardPiece*> AvailableMoves;
	for (auto& Pieces : AvailableCheckPieces)
	{
		for (auto& Move : Moves)
		{
			if(Move == Pieces)
			{
				AvailableMoves.Add(Move);				
			}
		}
	}

	if( AvailableMoves.Num() && HighlightPieces)
	{
		for (auto& Move : AvailableMoves)
		{
			if (Move->GetCurrentFigure())
			{
				Move->EnemyHighlightPiece();
			}
			else
			{
				Move->HighlightPiece();
			}
		}
	}
	
	return AvailableMoves;
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

TArray<UCTPBoardPiece*> ACTPPawnBase::GetPathTo(UCTPBoardPiece* TargetPiece)
{
	return {};
}
