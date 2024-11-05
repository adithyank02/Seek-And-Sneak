// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyGameMode.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"

#include "Kismet/KismetSystemLibrary.h"

void ALobbyGameMode::OnPostLogin(AController* NewPlayerController)
{
	Super::OnPostLogin(NewPlayerController);

	SpawnLobbyCharacter(NewPlayerController);

}
	
void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALobbyGameMode::SpawnLobbyCharacter(AController* NewPlayerController)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(NewPlayerController))
	{
		int LocationIndex = GetRandomUniqueIndex();
		FTransform CharacterSpawnTransform;

		if (LocationIndex != -1)CharacterSpawnTransform.SetLocation(LobbyPlayerSpawnLocation[LocationIndex]);

		ACharacter* LobbyCharacter = GetWorld()->SpawnActor<ACharacter>(LobbyCharacterClass, CharacterSpawnTransform);

		LobbyCharacter->PossessedBy(PlayerController);
	}
}

int ALobbyGameMode::GetRandomUniqueIndex()
{
	if (UsedLocationIndex.Num() >= LobbyPlayerSpawnLocation.Num())return -1;

	int Index = FMath::RandRange(0, LobbyPlayerSpawnLocation.Num() - 1);

	// Keep Generating A New Index Until Unique One Is Found
	while (UsedLocationIndex.Contains(Index))
	{
		Index = FMath::RandRange(0, LobbyPlayerSpawnLocation.Num() - 1);
	}

	UsedLocationIndex.Add(Index);

	return Index;
}
