// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPawn.h"
#include "TankPawn.h"

ATowerPawn::ATowerPawn()
{
}

void ATowerPawn::BeginPlay()
{
	Super::BeginPlay();

	IdleRotation = TurretMesh->GetComponentToWorld().GetRotation().Rotator();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATowerPawn::CheckFireCondition, FireRate, true);
}


void ATowerPawn::Tick(const float DeltaTime)
{
	if (!IsInFireRange())
	{
		RotateTurret(DeltaTime, IdleRotation);
		return;
	}

	RotateTurret(DeltaTime, Target->GetActorLocation());
}

void ATowerPawn::SetTarget(class ATankPawn* TankRef)
{
	Target = TankRef;
}

void ATowerPawn::CheckFireCondition() const
{
	if (!Target) return;
	if (!IsInFireRange()) return;
	Fire();
}

bool ATowerPawn::IsInFireRange() const
{
	if (!Target) return false;
	const float DistanceToTarget = FVector::Dist(Target->GetActorLocation(), GetActorLocation());
	return DistanceToTarget <= FireRange;
}
