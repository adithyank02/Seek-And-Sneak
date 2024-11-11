// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/InputState/Prop/OnPropClone.h"
#include "GameFramework/Character.h"
#include "PropPlayer/CloneActor/PropCloneActor.h"
#include "PropPlayer/PropPlayer.h"

OnPropClone::OnPropClone()
{
}

OnPropClone::~OnPropClone()
{
}

void OnPropClone::Begin(ACharacter* Player)
{
	if (PlayerInterface == nullptr)
	{
		if (IPropPlayerInterface* Interface = Cast <IPropPlayerInterface>(Player))
		{
			PlayerInterface.SetObject(Player);
			PlayerInterface.SetInterface(Interface);

			//Binding The Delegate
			Interface->GetPropPlayerRef()->PropMeshChanged.BindRaw(this, &OnPropClone::RemovePreviousSpawnedMesh);
		}
		CloneActorClass = APropCloneActor::StaticClass();
	}
    Location = Player->GetActorLocation();

	SpawnTransform.SetRotation(Player->GetActorRotation().Quaternion());

	SpawnTransform.SetLocation(Location);

	ClonedActor = Player->GetWorld()->SpawnActor<APropCloneActor>(CloneActorClass, SpawnTransform);
	if (ClonedActor)
	{
		ClonedActor->ActorMeshComp->SetStaticMesh(PlayerInterface->GetPlayerMesh());
		ClonedActorArray.Add(ClonedActor);
	}
}

void OnPropClone::End(ACharacter* Player)
{

}

void OnPropClone::RemovePreviousSpawnedMesh()
{
	for (auto  Actors: ClonedActorArray)
	{
		Actors->Destroy();
	}
	ClonedActorArray.Empty();
}
