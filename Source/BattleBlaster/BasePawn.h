// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "BasePawn.generated.h"


UCLASS()
class BATTLEBLASTER_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RotateTurret(float DeltaTime, const FRotator TargetRotation) const;
	void RotateTurret(float DeltaTime, const FVector& LookAtTarget) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//fire function
	void Fire() ;
	
	//destruction function
	virtual void HandleDestruction();
	
protected:
	
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* TurretMesh;
	
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* ProjectileSpawnPoint;
	
	UPROPERTY(VisibleAnywhere)
	class UHealthComponent* HealthComponent;
	
	UPROPERTY(EditAnywhere)
	float TurretTurnRate = 5.f;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectileActor> ProjectileActor;
};
