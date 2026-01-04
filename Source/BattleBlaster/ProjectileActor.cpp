// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileActor::OnHit);
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	auto MyOwner = GetOwner(); 
	if (!MyOwner )
	{
		Destroy();
		UE_LOG(LogTemp, Error, TEXT("Projectile has no owner"));
		return;
	}
	if (!OtherActor )
	{
		Destroy();
		UE_LOG(LogTemp, Error, TEXT("OtherActor is null"));
		return;
	}
	
	if (OtherActor == this || OtherActor == MyOwner) //ignore self hit or owner hit
	{
		Destroy();
		return;
	}
	
	//ApplyDamage 
	UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, UDamageType::StaticClass());

	Destroy();
}
