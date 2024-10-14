// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PropCloneActor.generated.h"

UCLASS()
class SEEKANDSNEAK_3D_API APropCloneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APropCloneActor();

	UStaticMeshComponent* ActorMeshComp;

};
