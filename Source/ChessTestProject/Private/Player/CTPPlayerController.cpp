#include "Player/CTPPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Board/CTPBoard.h"
#include "CTPGameModePlayerVSAI.h"
#include "Chessmen/CTPPawnBase.h"


void ACTPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(const auto FindedActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACTPBoard::StaticClass()))
	{
		CurrentBoard = Cast<ACTPBoard>(FindedActor);
	}

	if (const auto FindedGameMode = UGameplayStatics::GetGameMode(GetWorld()))
	{
		ChessGameMode = Cast<ACTPGameModePlayerVSAI>(FindedGameMode);
		if(ChessGameMode)
		{
			ChessGameMode->SetPlayerController(this);
		}
	}
}

void ACTPPlayerController::PlayerMove()
{
	bPlayerCanMove = true;
}

ACTPPlayerController::ACTPPlayerController()
{	
	if(!UGameplayStatics::GetPlatformName().Equals("Android"))
	{
		bShowMouseCursor = true;						// Show mouse cursor
	}
}

void ACTPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &ACTPPlayerController::OnLeftMousePressed);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &ACTPPlayerController::OnLeftMouseReleased);
}

void ACTPPlayerController::OnLeftMousePressed()
{
	FHitResult TraceResult(ForceInit);	// FHitResult variable to keep track of mouse hit.
	GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult);
	if (TraceResult.GetComponent())	// Check if any component was hit.
	{
		//If player click on figure
		if(auto SelectedChessFigure = Cast<ACTPPawnBase>(TraceResult.GetActor()))
		{
			if (CurrentState == EControllerState::CS_Free && SelectedChessFigure->GetIsWhiteColor() && bPlayerCanMove )
			{
				AvailableMoves = SelectedChessFigure->GetAvailableMoves();
				if (AvailableMoves.Num() > 0)
				{
					CurrentState = EControllerState::CS_SelectedFigure;
					CurrentSelectedFigure = SelectedChessFigure;
				}
			}
			else if(CurrentState == EControllerState::CS_SelectedFigure)
			{
				for (auto& Move : AvailableMoves)
				{
					Move->ReturnToDefault();
					if (SelectedChessFigure->GetCurrentPiece() == Move)
					{
						CurrentSelectedFigure->MoveTo(Move);
						bPlayerCanMove = false;
						ChessGameMode->MoveAI();
					}
				}
				AvailableMoves.Empty();
				CurrentSelectedFigure = nullptr;
				CurrentState = EControllerState::CS_Free;
			}
		}

		//If click on chess board
		if(auto SelectedBoard = Cast<ACTPBoard>(TraceResult.GetActor()))
		{			
			if (auto SelectedPiece = Cast<UCTPBoardPiece>(TraceResult.GetComponent()))	// Check if cast was successful.
			{
				switch (CurrentState)
				{
				case EControllerState::CS_Free:
					CurrentState = EControllerState::CS_MoveCamera; break;
				case EControllerState::CS_SelectedFigure:
				{				
					for(auto& Move : AvailableMoves)
					{
						Move->ReturnToDefault();						
						if (SelectedPiece == Move)
						{
							CurrentSelectedFigure->MoveTo(Move);
							bPlayerCanMove = false;
							ChessGameMode->MoveAI();
						}
					}
					AvailableMoves.Empty();
					CurrentSelectedFigure = nullptr;
					CurrentState = EControllerState::CS_Free;
					break;
				}
				default: ;
				}
			}
		}		
	}	
}

void ACTPPlayerController::OnLeftMouseReleased()
{
	if(CurrentState == EControllerState::CS_MoveCamera)
	{
		CurrentState = EControllerState::CS_Free;
	}
}
