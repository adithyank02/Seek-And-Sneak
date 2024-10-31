// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayerState/PropHuntPlayerState.h"

void APropHuntPlayerState::SetPlayerName(FString NewName)
{
	PlayerName = NewName;
}

FString APropHuntPlayerState::GetPlayerName()
{
	return PlayerName;
}
