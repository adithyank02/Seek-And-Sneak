// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Interface/GameState/GameStateInterface.h"

#include "PropHuntGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchTimerChanges,int32);

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API APropHuntGameState : public AGameState , public IGameStateInterface
{
	GENERATED_BODY()

public:

	//Delegate For Server To Inform TimerValue Changes
	FOnMatchTimerChanges OnMatchTimerChange;

private:

	//Interface Function
	void StartPreMatchTimer(int32 StartingTimer)override;
	APropHuntGameState* GetPropHuntGameState()override;

//---------------------------------------------------

	UPROPERTY(ReplicatedUsing = OnRep_MatchTimer)
	int32 MatchTimer = 30;

	UFUNCTION()
	void OnRep_MatchTimer();

	FTimerHandle MatchTimerHandle;

//---------------------------------------------------
	void StartMatchTimer();
	void UpdatMatchTimer();
	void StopMatchTimer();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	

};
