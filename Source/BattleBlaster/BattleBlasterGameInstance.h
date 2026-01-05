// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BattleBlasterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API UBattleBlasterGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	void LoadNextLevel();
	void RestartCurrentLevel();
	void RestartGame();
	int GetCurrentLevel() const;
	bool IsLastLevel() const ;
private:
	void ChangeLevel(int32 LevelNumber) ;
	
	UPROPERTY(EditAnywhere)
	int32 LastLevel = 3;
	
	UPROPERTY(VisibleAnywhere)
	int32 CurrentLevel = 1;
	
};
