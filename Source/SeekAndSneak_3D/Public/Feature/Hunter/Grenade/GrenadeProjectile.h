// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
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

	UPROPERTY(ReplicatedUsing = OnRep_GrenadeHitNotify)
	bool IsGrenadeHit;

	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_GrenadeHitNotify();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);

	TArray<FHitResult>HitResultArray;
	bool IsHited;
	const float DamageRadius = 500.0f;
	FVector StartPoint;
	FVector EndPoint;
	FCollisionQueryParams TraceParams;

};
