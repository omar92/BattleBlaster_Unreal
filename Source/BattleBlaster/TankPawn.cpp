// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"

ATankPawn::ATankPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(CapsuleComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
}

void ATankPawn::SetupInputSystem() const
{
	if (const auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (const auto LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (const auto EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				EnhancedInputSubsystem->AddMappingContext(DefaultMappingContext,0);
				return;
			}
			//log warning
			UE_LOG(LogTemp, Warning, TEXT("EnhancedInputSubsystem is null in TankPawn"));
			return;
		}
		//log warning
		UE_LOG(LogTemp, Warning, TEXT("LocalPlayer is null in TankPawn"));
		return;
	}
	//log warning
	UE_LOG(LogTemp, Warning, TEXT("PlayerController is null in TankPawn"));
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	SetupInputSystem();
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATankPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATankPawn::MoveInput);
	}
}

void ATankPawn::MoveInput(const FInputActionValue& Value)
{
	//log info
	UE_LOG(LogTemp, Warning, TEXT("MoveInput called Value: %f"), Value.Get<float>());
}
