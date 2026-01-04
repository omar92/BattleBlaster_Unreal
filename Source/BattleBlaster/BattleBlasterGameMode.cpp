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

	auto Towers = GetTowers();
	TowerCount = Towers.Num();
	SetTowersTarget(Towers, TankRef);
}

TArray<ATowerPawn*> ABattleBlasterGameMode::GetTowers() const
{
	TArray<AActor*> TowerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATowerPawn::StaticClass(), TowerActors);

	TArray<ATowerPawn*> Result;
	for (const auto TowerActor : TowerActors)
	{
		Result.Add(Cast<ATowerPawn>(TowerActor));
	}
	return Result;
}

void ABattleBlasterGameMode::SetTowersTarget(TArray<ATowerPawn*> Towers, ATankPawn* Target)
{
	//assign the tank as target to all towers 
	for (const auto Tower : Towers)
	{
		Tower->SetTarget(Target);
	}
}

void ABattleBlasterGameMode::ActorDied(AActor* Actor)
{
	if (Actor == TankRef)
	{
		TankRef->HandleDestruction();
		UE_LOG(LogTemp, Warning, TEXT("Tank destroyed, game over!"));
		//UGameplayStatics::OpenLevel(this, FName("GameOver"));
		return;
	}

	if (const auto Tower = Cast<ATowerPawn>(Actor))
	{
		//tower is dead
		Tower->HandleDestruction();
		TowerCount--;
		if (TowerCount <= 0)
		{
			//all towers are dead, player wins
			UE_LOG(LogTemp, Warning, TEXT("All towers destroyed, you win!"));
			//UGameplayStatics::OpenLevel(this, FName("WinScreen"));
			SetTowersTarget(GetTowers(), nullptr);
		}
		return;
	}

	//log
	UE_LOG(LogTemp, Error, TEXT("ActorDied: Unknown actor type"));
}
