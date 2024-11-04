// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraSystem.h"
#include "GrenadeProjectile.generated.h"

UCLASS()
class SEEKANDSNEAK_3D_API AGrenadeProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AGrenadeProjectile();

private:

	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* BaseCollision;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* GrenadeProjectileComponent;

	bool IsGrenadeHited;
	

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY()
	UNiagaraSystem* GrenadeExplosionParticle;

	UFUNCTION(Server,Reliable)
	void GrenadeHitOnServer(FVector ImpactLocation);

	UFUNCTION(NetMulticast, Reliable)
	void GrenadeHitOnMulticast(FVector ImpactLocation);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult);

	//LineTrace Variables
	TArray<FHitResult>HitResultArray;
	bool IsHited;
	const float DamageRadius = 350.0f;
	FCollisionObjectQueryParams ObjectQueryParams = ECollisionChannel::ECC_Pawn;

};
