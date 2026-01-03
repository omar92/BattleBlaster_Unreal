// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"

//#include "EngineUtils.h"
#include "TankPawn.h"
#include "TowerPawn.h"
#include "Kismet/GameplayStatics.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	TankRef = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)); 

	TArray<AActor*> TowerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATowerPawn::StaticClass(), TowerActors);
	TowerCount = TowerActors.Num();
	//assign the tank as target to all towers 
	
	for (const auto TowerActor : TowerActors)
	{
		auto Tower = Cast<ATowerPawn>(TowerActor);
		Tower->SetTarget(TankRef);
	}
	// TankRef = Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//
	// //get reference to all towers in the world
	//
	// auto TowerItr = TActorIterator<ATowerPawn>(GetWorld());
	// while (TowerItr)
	// {
	// 	TowerArray.Add(*TowerItr);
	// 	++TowerItr;
	// }
	

}
