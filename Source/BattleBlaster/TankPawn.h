// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TankPawn.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATankPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();
	void SetupInputSystem() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* RotateAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* FireAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* AccelerateAction;
	

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	APlayerController* PlayerControllerRef;
	
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 300.f;
	UPROPERTY(EditAnywhere)
	float AccelerationRate = 100.f;
	bool IsAccelerating = false;
	UPROPERTY(EditAnywhere)
	float TurnRate = 100.f;
	
	void MoveInput(const struct FInputActionValue& Value);
	void RotateInput(const struct FInputActionValue& Value);
	void FireInput();
	void AccelerateInputStarted();
	void AccelerateInputCompleted();
};
