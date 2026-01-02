// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	SetRootComponent(CapsuleComp);
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);	
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePawn::RotateTurret(const float DeltaTime, const FVector& LookAtTarget) const
{
	// auto location = TurretMesh->GetComponentLocation();
	// LookAtTarget.Z = location.Z;
	// FRotator TargetRotation = (LookAtTarget - location).Rotation();
	// TurretMesh->SetWorldRotation(TargetRotation);
	
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator TargetRotation = ToTarget.Rotation();
	FRotator TurretRotation = TurretMesh->GetComponentRotation();
	TargetRotation.Pitch = TurretRotation.Pitch;
	TargetRotation.Roll = TurretRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretRotation, TargetRotation, DeltaTime, TurretTurnRate));
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

