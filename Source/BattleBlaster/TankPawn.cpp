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
				EnhancedInputSubsystem->AddMappingContext(DefaultMappingContext, 0);
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

	PlayerControllerRef = Cast<APlayerController>(Controller);
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	if (PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, OUT HitResult))
	{
		FVector HitLocation = HitResult.ImpactPoint;
		//draw sphere at hit location
		DrawDebugSphere(GetWorld(), HitLocation, 25.f, 12, FColor::Red, false, -1.f);
		
		// auto location = TurretMesh->GetComponentLocation();
		// HitLocation.Z = location.Z;
		// FRotator TargetRotation = (HitLocation - location).Rotation();
		// TurretMesh->SetWorldRotation(TargetRotation);
		
		FVector ToTarget = HitLocation - TurretMesh->GetComponentLocation();
		FRotator TargetRotation = ToTarget.Rotation();
		FRotator TurretRotation = TurretMesh->GetComponentRotation();
		TargetRotation.Pitch = TurretRotation.Pitch;
		TargetRotation.Roll = TurretRotation.Roll;
		TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretRotation, TargetRotation, DeltaTime, 5.f));
	}
}

void ATankPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATankPawn::MoveInput);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATankPawn::RotateInput);
	}
}

void ATankPawn::MoveInput(const FInputActionValue& Value)
{
	const auto InputValue = Value.Get<float>();
	auto DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = InputValue * MoveSpeed * GetWorld()->GetDeltaSeconds();
	AddActorLocalOffset(DeltaLocation, true);
}

void ATankPawn::RotateInput(const FInputActionValue& Value)
{
	const auto InputValue = Value.Get<float>();
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = InputValue * TurnRate * GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(FQuat(DeltaRotation), true);
}
