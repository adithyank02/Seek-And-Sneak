// Fill out your copyright notice in the Description page of Project Settings.


#include "Feature/Hunter/Grenade/GrenadeProjectile.h"

#include "Net/UnrealNetwork.h"

#include "HunterPlayer/HunterPlayer.h"
#include "PropPlayer/PropPlayer.h"
#include "Interface/Player/PropPlayerInterface.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "NiagaraFunctionLibrary.h"

// Sets default values
AGrenadeProjectile::AGrenadeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(BaseCollision);

	GrenadeProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));

	GrenadeExplosionParticle = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Other_BP/NiagraParticle/NS_GrenadeExplosion.NS_GrenadeExplosion"));

}

// Called when the game starts or when spawned
void AGrenadeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	BaseCollision->OnComponentHit.AddDynamic(this, &AGrenadeProjectile::OnHit);
}

void AGrenadeProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
	if (HasAuthority())
	{
		GrenadeHitOnMulticast(HitResult.ImpactPoint);
	}
	else
	{
		GrenadeHitOnServer(HitResult.ImpactPoint);
	}
	
}


void AGrenadeProjectile::GrenadeHitOnServer_Implementation(FVector ImpactPoint)
{
   GrenadeHitOnMulticast(ImpactPoint);
}

void AGrenadeProjectile::GrenadeHitOnMulticast_Implementation(FVector ImpactPoint)
{
	IsHited =  GetWorld()->SweepMultiByObjectType(HitResultArray, ImpactPoint, ImpactPoint, FQuat::Identity, ObjectQueryParams, FCollisionShape::MakeSphere(DamageRadius));

	//Giving Hit Damage To Player On Grenade Explosion
	if (IsHited && HitResultArray.Num() > 0)
	{
		for (const FHitResult& HitResult : HitResultArray)
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor->IsA(APropPlayer::StaticClass()))
			{
				if (IPropPlayerInterface* PlayerInterface = Cast<IPropPlayerInterface>(HitActor))
				{
					PlayerInterface->PlayerGetDamaged(10);
				}
			}
		}
	}
	if(GrenadeExplosionParticle)UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), GrenadeExplosionParticle, ImpactPoint, FRotator(0.0f), FVector(1.0f), true, true, ENCPoolMethod::AutoRelease);

	//Not Pooling The Actor Since Its Not Continously Used
	Destroy();

}

