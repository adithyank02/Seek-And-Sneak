// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "PropPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API APropPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* PlayerMappingContext;

	//InputAction For Ground Movement --WSAD
	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;

	//InputAction For Look Movement --MouseXY
	UPROPERTY(EditDefaultsOnly)
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MorphAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* CloneAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* SmokeBombAction;
	
};
