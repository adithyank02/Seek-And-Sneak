// Fill out your copyright notice in the Description page of Project Settings.


#include "HunterPlayer/Animation/HunterAnimInstance.h"
#include "Interface/Player/HunterPlayerInterface.h"
#include "GameFramework/Character.h"

void UHunterAnimInstance::NativeInitializeAnimation()
{
	 OwnerCharacter = Cast <ACharacter>(GetOwningActor());
     
	 if (IHunterPlayerInterface* Interface = Cast <IHunterPlayerInterface>(OwnerCharacter))
	 {
		 PlayerInterface.SetObject(OwnerCharacter);
		 PlayerInterface.SetInterface(Interface);
	 }
}

void UHunterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (OwnerCharacter)
	{
		Velocity = OwnerCharacter->GetVelocity();
		Speed = Velocity.Size();
		Direction = CalculateDirection(Velocity, OwnerCharacter->GetActorRotation());

		AimRotation = OwnerCharacter->GetBaseAimRotation();
		if(AimRotation.Pitch >= 180)
		{
			Pitch = (360 - AimRotation.Pitch);
			
		}
		else
		{
			Pitch = AimRotation.Pitch * -1;
		}

		CanPlayerRun = PlayerInterface->CanRun();
	}

}
