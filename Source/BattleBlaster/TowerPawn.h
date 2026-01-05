// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TowerPawn.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATowerPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATowerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class ATankPawn* Target;
	
	UPROPERTY(VisibleAnywhere) 
	FRotator IdleRotation;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetTarget(class ATankPawn* TankRef);
	void CheckFireCondition() ;
	bool IsInFireRange() const;

	virtual void HandleDestruction() override;

	UPROPERTY(EditAnywhere)
	float FireRange = 700.f;
	UPROPERTY(EditAnywhere)
	float FireRate = 2.f;
	
};
