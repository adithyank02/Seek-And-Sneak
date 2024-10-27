// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/PropHuntGameState.h"

#include "Net/UnrealNetwork.h"
#include "GameFramework/GameMode.h"
#include "Interface/GameMode/PropHuntGameModeInterface.h"
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
    //BoradCasting The Change Of Timer To Client
    OnMatchTimerChange.Broadcast(MatchTimer);
}

void APropHuntGameState::StartMatchTimer()
{
    GetWorld()->GetTimerManager().SetTimer(MatchTimerHandle, this, &APropHuntGameState::UpdatMatchTimer, 1, true);
}

void APropHuntGameState::UpdatMatchTimer()
{
    MatchTimer--;
    //Broad Casting The Change Of Timer To Server
    OnMatchTimerChange.Broadcast(MatchTimer);
    if (MatchTimer == 0)StopMatchTimer();
}

void APropHuntGameState::StopMatchTimer()
{
    GetWorld()->GetTimerManager().ClearTimer(MatchTimerHandle);

    //Informing The GameMode About Match Timer Finish
    if (HasAuthority())
    {
        AGameMode* PropHuntGameMode = Cast<AGameMode>(GetWorld()->GetAuthGameMode());
        if (PropHuntGameMode)
        {
            if (IPropHuntGameModeInterface* GameModeInterface = Cast<IPropHuntGameModeInterface>(PropHuntGameMode))
            {
                GameModeInterface->PreMatchTimerEnded();        
            }
        }
    }
}


void APropHuntGameState::StartPreMatchTimer(int32 StartingTimer)
{
    //MatchTimer = StartingTimer;
    StartMatchTimer();
}
