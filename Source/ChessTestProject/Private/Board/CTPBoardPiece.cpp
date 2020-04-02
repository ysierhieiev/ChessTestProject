#include "Board/CTPBoardPiece.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"

UCTPBoardPiece::UCTPBoardPiece()
{
	const ConstructorHelpers::FObjectFinder<UMaterial> MLightCell(TEXT("Material'/Game/MobileStarterContent/Materials/M_Wood_Pine.M_Wood_Pine'"));
	if (MLightCell.Succeeded())
	{
		LightMaterial = MLightCell.Object;
	}

	const ConstructorHelpers::FObjectFinder<UMaterial> MDarkCell(TEXT("Material'/Game/MobileStarterContent/Materials/M_Wood_Walnut.M_Wood_Walnut'"));
	if (MDarkCell.Succeeded())
	{
		DarkMaterial = MDarkCell.Object;
	}

	const ConstructorHelpers::FObjectFinder<UMaterial> MHighlightedCell(TEXT("Material'/Game/Materials/M_SelectedMaterial.M_SelectedMaterial'"));
	if (MHighlightedCell.Succeeded())
	{
		HighlightedMaterial = MHighlightedCell.Object;
	}

	const ConstructorHelpers::FObjectFinder<UMaterial> MHighlightedEnemy(TEXT("Material'/Game/Materials/M_EliminateMaterial.M_EliminateMaterial'"));
	if (MHighlightedEnemy.Succeeded())
	{
		EnemyHighlightedMaterial = MHighlightedEnemy.Object;
	}
	
	const ConstructorHelpers::FObjectFinder<UStaticMesh> SMFloorAsset(TEXT("/Game/MobileStarterContent/Architecture/Floor_400x400.Floor_400x400"));

	this->SetStaticMesh(SMFloorAsset.Object);

	this->SetMaterial(0, DarkMaterial);
}

void UCTPBoardPiece::SetFigure(ACTPPawnBase* NewFigure)
{
	CurrentFigure = NewFigure;
	if (CurrentFigure)
	{
		CurrentState = EPieceState::CS_Figure;
	}
	else
	{
		CurrentState = EPieceState::CS_Empty;
	}
}

void UCTPBoardPiece::SetWhite()
{
	isWhite = true;
	this->SetMaterial(0, LightMaterial);
}

void UCTPBoardPiece::ReturnToDefault()
{
	if (isWhite)
	{
		this->SetMaterial(0, LightMaterial);
	}
	else
	{
		this->SetMaterial(0, DarkMaterial);
	}
	
	if (CurrentState == EPieceState::CS_EnemyHighlighted)
	{
		CurrentState = EPieceState::CS_Figure;
	}
	else
	{
		CurrentState = EPieceState::CS_Empty;
	}
}

void UCTPBoardPiece::HighlightPiece()
{
	this->SetMaterial(0, HighlightedMaterial);
	CurrentState = EPieceState::CS_Highlighted;
}

void UCTPBoardPiece::EnemyHighlightPiece()
{
	this->SetMaterial(0, EnemyHighlightedMaterial);
	CurrentState = EPieceState::CS_EnemyHighlighted;
}
