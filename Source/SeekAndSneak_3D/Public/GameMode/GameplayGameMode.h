// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Interface/GameMode/PropHuntGameModeInterface.h"
#include "GameplayGameMode.generated.h"

class IControllerInterface;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API AGameplayGameMode : public AGameMode , public IPropHuntGameModeInterface
{
	GENERATED_BODY()
	
	void OnPostLogin(AController* NewController)override;

	void BeginPlay()override;

	/*Interface Function*/
	void PreMatchTimerEnded()override;

	//Storing Controller Interface - - Avoiding Re-Casting
	TArray<TScriptInterface<IControllerInterface>>ControllerInterfaceArray;

	//Storing All Joined Controller
    UPROPERTY()
	TArray<AController*>JoinedPlayerController;

	//For Spawning And Possesing Prop Character
	void SetUpPropCharacter();

	//For Spawning And Possesing Hunter Character
	void SetupHunterCharacter(TArray<AController*>RemainingController);

	void CallPreMatchWidget();

	//Function To Store Controller Interface
	void StoreControllerInterface(AController* PlayerController, IControllerInterface* InterfaceRef);

	//Random Index For Selecting Player
	int GetRandomIndex(int Min, int Max);

//--------------- UPROPERTY VARIABLES------------------

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APropPlayer>PropCharacterClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHunterPlayer>HunterCharacterClass;

	UPROPERTY(EditDefaultsOnly)
	TArray<FTransform>PropCharacterSpawnTranform;

	UPROPERTY(EditDefaultsOnly)
	TArray<FTransform>HunterCharacterSpawnTranform;

};