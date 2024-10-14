// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "HunterPlayerController.generated.h"

class AHunterPlayer;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API AHunterPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* PlayerMappingContext;

	//InputAction For Ground Movement --WSAD
	UPROPERTY(EditDefaultsOnly)
	UInputAction* JogAction;

	//InputAction For Look Movement --MouseXY
	UPROPERTY(EditDefaultsOnly)
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* FireWeaponAction;


	
};
