// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPawn.h"
#include "TankPawn.h"

ATowerPawn::ATowerPawn()
{
}

void ATowerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ATowerPawn::Tick(const float DeltaTime)
{
	if (!Target) return;
		RotateTurret(DeltaTime, Target->GetActorLocation());
}

void ATowerPawn::SetTarget(class ATankPawn* TankRef)
{
	Target = TankRef;
}
