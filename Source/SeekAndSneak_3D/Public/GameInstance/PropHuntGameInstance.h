// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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
	void SetRoomId(FString RoomID)override;
	FString GetRoomId()override;

	void SetPlayerInGameName(FString NewName)override;

private:
	FString RoomCode;

	FString LocalPlayerInGameName;

};
