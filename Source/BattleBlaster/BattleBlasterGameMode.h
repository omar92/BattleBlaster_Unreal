// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleBlasterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ABattleBlasterGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void ActorDied(AActor* Actor);
	void OnGameOver() const;

protected:
	TArray<class ATowerPawn*> GetTowers() const;
	static void SetTowersTarget(TArray<class ATowerPawn*> Towers, class ATankPawn* Target = nullptr);

private:
	class ATankPawn* TankRef = nullptr;
	int TowerCount = 0;
	UPROPERTY(EditAnywhere)
	float GameOverDelay = 3.f;
	UPROPERTY(VisibleAnywhere)
	bool IsGameOver = false;
	UPROPERTY(VisibleAnywhere)
	bool IsPlayerWin = false;
};
