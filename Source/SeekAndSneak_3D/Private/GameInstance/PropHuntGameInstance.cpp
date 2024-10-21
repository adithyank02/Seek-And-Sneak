// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/PropHuntGameInstance.h"

void UPropHuntGameInstance::SetRoomId(FString RoomID)
{
	RoomCode = RoomID;
}

FString UPropHuntGameInstance::GetRoomId()
{
	return RoomCode;
}
