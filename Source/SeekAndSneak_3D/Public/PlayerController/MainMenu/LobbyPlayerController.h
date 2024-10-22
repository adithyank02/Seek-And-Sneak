// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

class ULobbyWidget;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ALobbyPlayerController();

	FTransform CameraActorSpawnTransform;

protected:

	void  BeginPlay()override;

	TSubclassOf<ULobbyWidget>LobbyWidgetClass;
	
	void SpawnCameraActor();
	void CreateLobbyWidget();
	void SetInputModeType(UUserWidget* CreatedWidget);
	
};
