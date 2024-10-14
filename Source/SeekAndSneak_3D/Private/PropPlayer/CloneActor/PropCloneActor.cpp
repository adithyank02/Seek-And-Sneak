// Fill out your copyright notice in the Description page of Project Settings.


#include "PropPlayer/CloneActor/PropCloneActor.h"

// Sets default values
APropCloneActor::APropCloneActor()
{
	PrimaryActorTick.bCanEverTick = false;

	ActorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ActorMeshComp->SetupAttachment(RootComponent);
	
	ActorMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}


