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

	FTimerHandle PlayerCameraViewTimer;
	GetWorld()->GetTimerManager().SetTimer(PlayerCameraViewTimer, [this, NewPlayerController] {SetNewPlayerViewOnCamera(NewPlayerController); }, 0.1,false);

}
	
void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerViewCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(),CameraSpawnTransform);

	if (PlayerViewCamera)
	{
		if (UCameraComponent* CameraComponent = PlayerViewCamera->FindComponentByClass<UCameraComponent>())
		{
			//Setting Full View On Screen
			CameraComponent->bConstrainAspectRatio = false;
		}
	}
}

void ALobbyGameMode::SetNewPlayerViewOnCamera(AController* NewPlayerController)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(NewPlayerController))
	{
		PlayerController->SetViewTarget(PlayerViewCamera);

		SpawnLobbyCharacter(PlayerController);
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Controller Is Null"), true, true, FLinearColor::Red, 5);
	}
}

void ALobbyGameMode::SpawnLobbyCharacter(APlayerController* PlayerController)
{
	int LocationIndex = GetRandomUniqueIndex();
	FTransform CharacterSpawnTransform;

	if (LocationIndex != -1)CharacterSpawnTransform.SetLocation(LobbyPlayerSpawnLocation[LocationIndex]);

	ACharacter* LobbyCharacter =  GetWorld()->SpawnActor<ACharacter>(LobbyCharacterClass, CharacterSpawnTransform);

	LobbyCharacter->PossessedBy(PlayerController);
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
