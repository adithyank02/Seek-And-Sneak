// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interface/PropHuntPlayerState/PlayerStateInterface.h"
#include "PropHuntPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API APropHuntPlayerState : public APlayerState , public IPlayerStateInterface
{
	GENERATED_BODY()

	void SetPlayerName(FString NewName)override;
	FString GetPlayerName()override;

	FString PlayerName;
	
};
