// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameStateInterface.generated.h"

class APropHuntGameState;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SEEKANDSNEAK_3D_API IGameStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void StartPreMatchTimer(int32 StartingTimer) = 0; 
	virtual void StartInMatchTimer(int32 StartingTimer) = 0;
	virtual void SetTeamInfo(int TotalHunterPlayer, int TotalPropPlayer) = 0;
	virtual void GetTeamInfo(int& TotalHunterPlayer, int& TotalPropPlayer) = 0;
	virtual void OnPropPlayerCaught() = 0;
	virtual APropHuntGameState* GetPropHuntGameState() = 0;

};
