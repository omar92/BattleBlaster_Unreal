// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreenMessage.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API UScreenMessage : public UUserWidget
{
	GENERATED_BODY()

protected:
	//TEXT WIDGET 
	UPROPERTY(EditAnywhere , meta = (BindWidget))
	class UTextBlock* MessageTextBlock;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* PlayerHealthBar;

public:
	void SetScreenMessageText(const FString& Message) const;
	void SetHealthProgressBarPercent(float Percent) const;
};
