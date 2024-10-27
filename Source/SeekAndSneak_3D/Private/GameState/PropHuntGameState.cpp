// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/PropHuntGameState.h"

#include "Net/UnrealNetwork.h"

#include "Runtime/Engine/Public/TimerManager.h"

#include "Kismet/KismetSystemLibrary.h"


APropHuntGameState* APropHuntGameState::GetPropHuntGameState()
{
    return this;
}
void APropHuntGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APropHuntGameState, MatchTimer);
}

void APropHuntGameState::OnRep_MatchTimer()
{
    OnMatchTimerChange.Broadcast(MatchTimer);
}

void APropHuntGameState::StartMatchTimer()
{
    GetWorld()->GetTimerManager().SetTimer(MatchTimerHandle, this, &APropHuntGameState::UpdatMatchTimer, 1, true);
}

void APropHuntGameState::UpdatMatchTimer()
{
    MatchTimer--;
    OnMatchTimerChange.Broadcast(MatchTimer);
    if (MatchTimer == 0)StopMatchTimer();
}

void APropHuntGameState::StopMatchTimer()
{
    GetWorld()->GetTimerManager().ClearTimer(MatchTimerHandle);
}


void APropHuntGameState::StartPreMatchTimer(int32 StartingTimer)
{
    //MatchTimer = StartingTimer;
    StartMatchTimer();
}
