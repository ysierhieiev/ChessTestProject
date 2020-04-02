#include "Player/CTPPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Board/CTPBoard.h"
#include "Player/CTPPlayerController.h"

ACTPPlayer::ACTPPlayer()
{
 	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetRelativeRotation(FRotator(-40.0f, 0.0f, 0.0f));
	CameraSpringArm->bDoCollisionTest = false;
	CameraSpringArm->TargetArmLength = 3000.f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;
	CameraSpringArm->SetupAttachment(RootComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	//Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ACTPPlayer::BeginPlay()
{
	Super::BeginPlay();

	ChessPlayerController = Cast<ACTPPlayerController>(GetController());
}

void ACTPPlayer::YawCamera(float AxisValue)
{
	if(ChessPlayerController->GetCurrentState() == EControllerState::CS_MoveCamera)
	{
		CameraInput.X = AxisValue * 1.5f;
	}
}

void ACTPPlayer::PitchCamera(float AxisValue)
{
	if(ChessPlayerController->GetCurrentState() == EControllerState::CS_MoveCamera)
	{		
		CameraInput.Y = AxisValue * 1.5f;
	}
}

void ACTPPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ChessPlayerController->GetCurrentState() == EControllerState::CS_MoveCamera)
	{
		//Rotate our actor's yaw, which will turn our camera because we're attached to it
		{
			FRotator NewRotation = GetActorRotation();
			NewRotation.Yaw += CameraInput.X;
			SetActorRotation(NewRotation);
		}

		//Rotate our camera's pitch, but limit it so we're always looking downward
		{
			FRotator NewRotation = CameraSpringArm->GetComponentRotation();
			NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -20.0f);
			CameraSpringArm->SetWorldRotation(NewRotation);
		}
	}
}

void ACTPPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindAxis("CameraPitch", this, &ACTPPlayer::YawCamera);
	InputComponent->BindAxis("CameraYaw", this, &ACTPPlayer::PitchCamera);
}

