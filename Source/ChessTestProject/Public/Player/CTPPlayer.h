#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CTPPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ACTPPlayerController;

UCLASS()
class CHESSTESTPROJECT_API ACTPPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACTPPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	ACTPPlayerController* ChessPlayerController;

	void YawCamera(float AxisValue);
	
	void PitchCamera(float AxisValue);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	
	FVector2D CameraInput;
};

