// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameInstance.h"

#include "Kismet/GameplayStatics.h"

void UBattleBlasterGameInstance::LoadNextLevel()
{
	CurrentLevel++;
	if (CurrentLevel > LastLevel)
	{
		//log error 
		UE_LOG(LogTemp, Error, TEXT("No more levels to load! CurrentLevel %d exceeds LastLevel %d"), CurrentLevel, LastLevel);
		return;
	}
	ChangeLevel(CurrentLevel);
}

void UBattleBlasterGameInstance::RestartCurrentLevel()
{
	ChangeLevel(CurrentLevel);
}

void UBattleBlasterGameInstance::RestartGame()
{
	ChangeLevel(1);
}

int UBattleBlasterGameInstance::GetCurrentLevel() const
{
	return CurrentLevel;
}

bool UBattleBlasterGameInstance::IsLastLevel() const
{
	return CurrentLevel == LastLevel;
}

void UBattleBlasterGameInstance::ChangeLevel(int32 LevelNumber)
{
	if (LevelNumber < 1 || LevelNumber > LastLevel)
	{
		//log error 
		UE_LOG(LogTemp, Error, TEXT("LevelNumber %d is out of bounds!"), LevelNumber);
		return;
	}
	CurrentLevel = LevelNumber;

	const auto LevelName = FString::Printf(TEXT("Level_%d"), CurrentLevel);
	UGameplayStatics::OpenLevel(GetWorld(), *LevelName);
}
