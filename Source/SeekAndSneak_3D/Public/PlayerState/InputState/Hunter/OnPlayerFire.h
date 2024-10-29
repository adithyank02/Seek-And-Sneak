// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerState/InputState/InputStateAbstract.h"
#include "Particles/ParticleSystem.h"
#include "Interface/Player/HunterPlayerInterface.h"


class IPropPlayerInterface;

/**
 * 
 */
class SEEKANDSNEAK_3D_API OnPlayerFire : public InputStateAbstract
{
public:
	OnPlayerFire();
	~OnPlayerFire();

	void Begin(ACharacter* Player)override;
	void End(ACharacter* Player)override;
	void SetLocation(FVector V1, FVector V2)override;

private:


	//Weapon Variables
	float ShootingRange;

	//Caching Player Weapon Mesh
	USkeletalMeshComponent* WeaponMeshComp;


	UAnimSequence* FireAnimation;

	FTransform ParticleTransform;
	UParticleSystem* WeaponBulletHitParticle;

	TScriptInterface<IPropPlayerInterface>HitActorInterface;

	void CachePropPlayerInterface(AActor* HitActor);

	const int BulletHitDamage = 1.0f;

	//LineTrace Variables
	bool IsHit;
	FHitResult HitResult;
	FVector ForwardVector;
	FVector StartPoint;
	FVector EndPoint;
	FCollisionQueryParams TraceCollision;

protected:

	void WeaponFiring(ACharacter* Player);
};
