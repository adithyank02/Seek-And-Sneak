// Fill out your copyright notice in the Description page of Project Settings.


#include "Feature/Hunter/Grenade/GrenadeProjectile.h"

#include "Net/UnrealNetwork.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AGrenadeProjectile::AGrenadeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(BaseCollision);

	GrenadeProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));

}

void AGrenadeProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGrenadeProjectile, IsGrenadeHit);

}

// Called when the game starts or when spawned
void AGrenadeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	BaseCollision->OnComponentBeginOverlap.AddDynamic(this, &AGrenadeProjectile::OnBeginOverlap);
}

void AGrenadeProjectile::OnRep_GrenadeHitNotify()
{
	IsHited = GetWorld()->SweepMultiByChannel(HitResultArray, StartPoint, EndPoint, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(DamageRadius), TraceParams);
}

void AGrenadeProjectile::OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	IsGrenadeHit = true;
}


