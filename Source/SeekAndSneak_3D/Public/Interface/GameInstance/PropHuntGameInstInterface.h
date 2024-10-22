// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PropHuntGameInstInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPropHuntGameInstInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SEEKANDSNEAK_3D_API IPropHuntGameInstInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void SetRoomId(FString RoomID) = 0;
	virtual FString GetRoomId() = 0;

	virtual void SetPlayerInGameName(FString NewName) = 0;

};
