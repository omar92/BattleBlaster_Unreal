// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	SetRootComponent(ProjectileMesh);
	
	ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
//	ProjectileMoveComp->UpdatedComponent = ProjectileMesh;
	ProjectileMoveComp->InitialSpeed = 1000.f;
	ProjectileMoveComp->MaxSpeed = 1000.f;
	ProjectileMoveComp->bRotationFollowsVelocity = true;
	ProjectileMoveComp->bShouldBounce = true;
	
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

