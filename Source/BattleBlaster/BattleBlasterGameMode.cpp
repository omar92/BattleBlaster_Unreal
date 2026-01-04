// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"

//#include "EngineUtils.h"
#include "BattleBlasterGameInstance.h"
#include "TankPawn.h"
#include "TowerPawn.h"
#include "Kismet/GameplayStatics.h"


void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameInstanceRef = Cast<UBattleBlasterGameInstance>(GetGameInstance());
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
	IsGameOver = false;
	IsPlayerWin = false;

	if (Actor == TankRef)
	{
		TankRef->HandleDestruction();
		IsGameOver = true;
		IsPlayerWin = false;
	}

	else if (const auto Tower = Cast<ATowerPawn>(Actor))
	{
		//tower is dead
		Tower->HandleDestruction();
		TowerCount--;
		if (TowerCount <= 0)
		{
			IsGameOver = true;
			IsPlayerWin = true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ActorDied: Unknown actor type"));
		return;
	}

	if (!IsGameOver) return;
	//log game over
	UE_LOG(LogTemp, Warning, TEXT("Game Over! %s"), IsPlayerWin ? TEXT("Player Wins!") : TEXT("Towers Win!"));

	//clear towers target
	SetTowersTarget(GetTowers(), nullptr);

	//create timer 
	FTimerHandle GameOverTimerHandle;
	GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ABattleBlasterGameMode::OnGameOver, GameOverDelay, false);
}

void ABattleBlasterGameMode::OnGameOver() const
{
	if (!GameInstanceRef)
	{
		//log error
		UE_LOG(LogTemp, Error, TEXT("GameInstanceRef is null in OnGameOver"));
		return;
	}

	if (IsPlayerWin)
	{
		if (GameInstanceRef->IsLastLevel())
		{
			//log player completed all levels
			UE_LOG(LogTemp, Warning, TEXT("Player completed all levels! Restarting game."));
			GameInstanceRef->RestartGame();
		}
		else
		{
			//log player won level and loading next level
			UE_LOG(LogTemp, Warning, TEXT("Loading next level..."));
			GameInstanceRef->LoadNextLevel();
		}
	}
	else
	{
		//log player lost and restarting current level
		UE_LOG(LogTemp, Warning, TEXT("Restarting current level..."));
		GameInstanceRef->RestartCurrentLevel();
	}
}
