// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/MainMenuWidget.h"
#include "MainMenuController.generated.h"

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()

public:

	AMainMenuController();

private:

	void BeginPlay()override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainMenuWidget>MainMenuClass;

	UPROPERTY()
	class UUserWidget* MainMenuWidget;
	
};
