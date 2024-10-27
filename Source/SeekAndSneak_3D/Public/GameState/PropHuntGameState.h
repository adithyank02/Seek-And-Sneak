// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Interface/GameState/GameStateInterface.h"

#include "PropHuntGameState.generated.h"

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API APropHuntGameState : public AGameState , public IGameStateInterface
{
	GENERATED_BODY()

	UPROPERTY(Replicated)
	int32 PreMatchTimer;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;
	
	int32 GetPreMatchTimerVariable()override;

};
