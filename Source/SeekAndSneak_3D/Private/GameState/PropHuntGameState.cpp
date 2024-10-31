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
void APropHuntGameState::SetTeamInfo(int TotalHunterPlayer, int TotalPropPlayer)
{
    TotalNumberOfHunterPlayer = TotalHunterPlayer;
    TotalNumberOfPropPlayer = TotalPropPlayer;

    //Broadcasting To Server , Cause It Won't Replicate To Server
    OnHunterPlayerCountChange.Broadcast(TotalNumberOfHunterPlayer);
    OnPropPlayerCountChange.Broadcast(TotalNumberOfPropPlayer);
}

void APropHuntGameState::UpdatePropTeamInfo()
{
    TotalNumberOfPropPlayer--;
    OnPropPlayerCountChange.Broadcast(TotalNumberOfPropPlayer);
}


void APropHuntGameState::OnRep_PropPlayerCountUpdate()
{
    OnPropPlayerCountChange.Broadcast(TotalNumberOfPropPlayer);
}
void APropHuntGameState::OnRep_HunterPlayerCountUpdate()
{
    OnHunterPlayerCountChange.Broadcast(TotalNumberOfHunterPlayer);
}

void APropHuntGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APropHuntGameState, PreMatchTimer);
    DOREPLIFETIME(APropHuntGameState, InMatchTimer);
    DOREPLIFETIME(APropHuntGameState, TotalNumberOfHunterPlayer);
    DOREPLIFETIME(APropHuntGameState, TotalNumberOfPropPlayer);
}

void APropHuntGameState::OnRep_PreMatchTimer()
{
    //BoradCasting The Change Of Timer To Client
    OnMatchTimerChange.Broadcast(PreMatchTimer);
}

void APropHuntGameState::OnRep_InMatchTimer()
{
    OnInMatchTimerChange.Broadcast(InMatchTimer);
}

void APropHuntGameState::StartPreMatchTimer(int32 StartingTimer)
{
    PreMatchTimer = StartingTimer;
    StartPreMatchTimer();
}


void APropHuntGameState::StartPreMatchTimer()
{
    GetWorld()->GetTimerManager().SetTimer(MatchTimerHandle, this, &APropHuntGameState::UpdatePreMatchTimer, 1, true);
}

void APropHuntGameState::UpdatePreMatchTimer()
{
    PreMatchTimer--;
    //Broad Casting The Change Of Timer To Server
    OnMatchTimerChange.Broadcast(PreMatchTimer);
    if (PreMatchTimer == 0)StopPreMatchTimer();
}

void APropHuntGameState::StopPreMatchTimer()
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

void APropHuntGameState::StartInMatchTimer(int32 StartingTimer)
{
    InMatchTimer = StartingTimer;
    StartInMatchTimer();
}



void APropHuntGameState::StartInMatchTimer()
{
    GetWorld()->GetTimerManager().SetTimer(MatchTimerHandle, this, &APropHuntGameState::UpdateInMatchTimer, 1, true);
}


void APropHuntGameState::UpdateInMatchTimer()
{
    InMatchTimer--;
    OnInMatchTimerChange.Broadcast(InMatchTimer);
    if (InMatchTimer == 0)StopInMatchTimer();
}
void APropHuntGameState::StopInMatchTimer()
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
                GameModeInterface->OnMatchEnded();
            }
        }
    }
}
