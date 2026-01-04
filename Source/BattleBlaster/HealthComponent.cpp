// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnDamageTaken);

	const auto GameMode = UGameplayStatics::GetGameMode(GetWorld()); 
	if (!GameMode)
	{
		//log error
		UE_LOG(LogTemp, Error, TEXT("GameMode is null in HealthComponent"));
		return;
	}

	BattleBlasterGameMode = Cast<ABattleBlasterGameMode>(GameMode);
	if (!BattleBlasterGameMode)
	{
		//log error
		UE_LOG(LogTemp, Error, TEXT("BattleBlasterGameMode is null in HealthComponent"));
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UHealthComponent::OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0.f)
	{
		CurrentHealth = 0.f;
	}

	if (CurrentHealth > 0.f) return;
	
	
	//notify game mode of death
	if (!BattleBlasterGameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("BattleBlasterGameMode is null in HealthComponent OnDamageTaken"));
		return;
	}
	BattleBlasterGameMode->ActorDied(DamagedActor);
}
