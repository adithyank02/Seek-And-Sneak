// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/PropHuntGameState.h"

#include "Net/UnrealNetwork.h"

void APropHuntGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APropHuntGameState, PreMatchTimer);
}

int32 APropHuntGameState::GetPreMatchTimerVariable()
{
    return PreMatchTimer;
}
