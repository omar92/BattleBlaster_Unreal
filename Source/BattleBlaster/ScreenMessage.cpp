// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenMessage.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

// UScreenMessageUserWidget::UScreenMessageUserWidget()
// {
// 	ScreenMessageCanvasPanel = CreateDefaultSubobject<UCanvasPanel>(TEXT("ScreenMessageCanvasPanel"));
// 	ScreenMessageTextBlock = CreateDefaultSubobject<UTextBlock>(TEXT("ScreenMessageTextBlock"));
// 	//set child to canvas
// 	ScreenMessageCanvasPanel->AddChild(ScreenMessageTextBlock);
// }

void UScreenMessage::SetScreenMessageText(const FString& Message) const
{
	if (!MessageTextBlock)
	{
		UE_LOG(LogTemp, Error, TEXT("MessageTextBlock is null in ScreenMessageUserWidget"));
		return;
	}
	MessageTextBlock->SetText(FText::FromString(Message));
}

void UScreenMessage::SetHealthProgressBarPercent(const float Percent) const
{
	if (!PlayerHealthBar)
	{
		UE_LOG(LogTemp, Error, TEXT("HealthProgressBar is null in ScreenMessageUserWidget"));
		return;
	}
	PlayerHealthBar->SetPercent(Percent);
}
