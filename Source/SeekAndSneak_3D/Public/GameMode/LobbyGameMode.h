// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()

private:

	void OnPostLogin(AController* NewPlayerController)override;

 	void BeginPlay() override;

	UPROPERTY()
	ACameraActor* PlayerViewCamera;

	UPROPERTY(EditDefaultsOnly)
	FTransform CameraSpawnTransform;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacter>LobbyCharacterClass;

	TArray<int>UsedLocationIndex;

	//Total Player Can Play Match Count Location Count Will Add
	UPROPERTY(EditDefaultsOnly)
	TArray<FVector>LobbyPlayerSpawnLocation;

	void SetNewPlayerViewOnCamera(AController* NewPlayerController);

	void SpawnLobbyCharacter(APlayerController* PlayerController);

	int GetRandomUniqueIndex();
	
};
