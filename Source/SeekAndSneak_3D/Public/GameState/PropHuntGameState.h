// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Interface/GameState/GameStateInterface.h"

#include "PropHuntGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchTimerChanges,int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInMatchTimerChanges, int32);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPropPlayerCountUpdate,int);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHunterPlayerCountUpdate, int);

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
	FOnInMatchTimerChanges OnInMatchTimerChange;

	FOnPropPlayerCountUpdate OnPropPlayerCountChange;
	FOnHunterPlayerCountUpdate OnHunterPlayerCountChange;

private:

	//Interface Function
	void StartPreMatchTimer(int32 StartingTimer)override;
	void StartInMatchTimer(int32 StartingTimer)override;
	void UpdatePropTeamInfo()override;
	void SetTeamInfo(int TotalHunterPlayer, int TotalPropPlayer)override;

	APropHuntGameState* GetPropHuntGameState()override;

//---------------------------------------------------

	UPROPERTY(ReplicatedUsing = OnRep_PreMatchTimer)
	int32 PreMatchTimer;

	UPROPERTY(ReplicatedUsing = OnRep_InMatchTimer)
	int32 InMatchTimer;

	UFUNCTION()
	void OnRep_PreMatchTimer();

	UFUNCTION()
	void OnRep_InMatchTimer();

	FTimerHandle MatchTimerHandle;

	//Since Hunter Won't die there number won't change
	//UPROPERTY(Replicated)
	UPROPERTY(ReplicatedUsing = OnRep_HunterPlayerCountUpdate)
	int TotalNumberOfHunterPlayer;

	UFUNCTION()
	void OnRep_HunterPlayerCountUpdate();

	UPROPERTY(ReplicatedUsing = OnRep_PropPlayerCountUpdate)
	//UPROPERTY(Replicated)
	int TotalNumberOfPropPlayer;

	UFUNCTION()
	void OnRep_PropPlayerCountUpdate();

//---------------------------------------------------
	void StartPreMatchTimer();
	void UpdatePreMatchTimer();
	void StopPreMatchTimer();

	void StartInMatchTimer();
	void UpdateInMatchTimer();
	void StopInMatchTimer();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	

};
