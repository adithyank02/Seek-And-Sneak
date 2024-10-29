// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveGame/PropHuntSaveGame.h"
#include "Interface/GameInstance/PropHuntGameInstInterface.h"
#include "PropHuntGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UPropHuntGameInstance : public UGameInstance , public IPropHuntGameInstInterface
{
	GENERATED_BODY()

protected:

	void Init()override;

	void SetRoomId(FString RoomID)override;
	FString GetRoomId()override;

	FString GetSaveSlotName()override;

	void SavePlayerName(FString NewName)override;
	FString GetSavedPlayerName()override;

	void SetHostedSessionName(FName SessionName)override;
	FName GetHostedSessionName()override;

private:

	UPROPERTY()
    UPropHuntSaveGame* SaveGameObject;

	//Only Available In Host (Server)
	FName HostSessionName;

   //SaveGame Slot Name
	const FString SlotName = "PropHuntSaveGame_01";

	//Room Code
	FString RoomCode;

	FString LocalPlayerInGameName;

};
