// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerState/InputState/InputStateAbstract.h"
#include "Interface/Player/PropPlayerInterface.h"

class APropCloneActor;


/**
 * 
 */
class SEEKANDSNEAK_3D_API OnPropClone : public InputStateAbstract
{
public:
	OnPropClone();
	~OnPropClone();

	void Begin(ACharacter* Player)override;
	void End(ACharacter* Player)override;

private:

	TScriptInterface<IPropPlayerInterface>PlayerInterface;

	//Actor Class To Spawn
	TSubclassOf<APropCloneActor>CloneActorClass;

	//Clone Actor 
	APropCloneActor* ClonedActor;

	FVector Location;

	FTransform SpawnTransform;
};
