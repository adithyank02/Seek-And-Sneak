// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PropHuntSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UPropHuntSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPropHuntSaveGame();

	UPROPERTY()
	FString PlayerName;
	
};
