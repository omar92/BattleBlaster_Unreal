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
}


void ATowerPawn::Tick(const float DeltaTime)
{
	if (!Target)
	{
		RotateTurret(DeltaTime, IdleRotation);
		return;
	}
	const float DistanceToTarget = FVector::Dist(Target->GetActorLocation(), GetActorLocation());
	if (DistanceToTarget > FireRange)
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
