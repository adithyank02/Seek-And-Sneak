// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameplayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API AGameplayGameMode : public AGameMode
{
	GENERATED_BODY()
	
	void OnPostLogin(AController* NewController)override;

	void BeginPlay()override;

    UPROPERTY()
	TArray<AController*>JoinedPlayerController;

	void SetUpPropCharacter();

	void SetupHunterCharacter(TArray<AController*>RemainingController);


	int GetRandomIndex(int Min, int Max);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APropPlayer>PropCharacterClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHunterPlayer>HunterCharacterClass;

	UPROPERTY(EditDefaultsOnly)
	TArray<FTransform>PropCharacterSpawnTranform;

	UPROPERTY(EditDefaultsOnly)
	TArray<FTransform>HunterCharacterSpawnTranform;

};
