// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/InputState/Hunter/OnPlayerFire.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

OnPlayerFire::OnPlayerFire()
{

	FireAnimation = LoadObject<UAnimSequence>(nullptr, TEXT("/Game/Asset/Weapons/Rifle/Animations/RifileFireAnimation.RifileFireAnimation"));
	WeaponBulletHitParticle = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/Asset/Weapons/Rifle/Vfx/RifileShotImpact.RifileShotImpact"));

	ShootingRange = 2000.0f;

	WeaponMeshComp = nullptr;
}

OnPlayerFire::~OnPlayerFire()
{

}

void OnPlayerFire::Begin(ACharacter* Player)
{
	if (!WeaponMeshComp)
	{
		//Call At Once , So Using This For Store Other Datas
		if (IHunterPlayerInterface* Interface = Cast <IHunterPlayerInterface>(Player))
		{
			WeaponMeshComp = Interface->GetWeaponMeshComp();
		}
		TraceCollision.AddIgnoredActor(Player);
	}
	WeaponFiring(Player);

}

void OnPlayerFire::End(ACharacter* Player)
{

}

void OnPlayerFire::SetLocation(FVector V1, FVector V2)
{
	StartPoint = V1;
	EndPoint = StartPoint + (V2 * ShootingRange);
}

//Contain Fire Weapon Logic
void OnPlayerFire::WeaponFiring(ACharacter* Player)
{
	/*Weapon Animation Added*/
	if(FireAnimation)WeaponMeshComp->PlayAnimation(FireAnimation, false);

	IsHit = Player->GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, TraceCollision);

	if (IsHit)
	{
		ParticleTransform.SetLocation(HitResult.ImpactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(Player->GetWorld(), WeaponBulletHitParticle, ParticleTransform, true, EPSCPoolMethod::AutoRelease);
	}

	DrawDebugLine(Player->GetWorld(), StartPoint, EndPoint, FColor::Red,false,3);
	
}
