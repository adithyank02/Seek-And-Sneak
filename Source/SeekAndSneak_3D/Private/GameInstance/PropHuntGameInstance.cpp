// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/PropHuntGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UPropHuntGameInstance::Init()
{
	Super::Init();

	if (!UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		SaveGameObject = Cast<UPropHuntSaveGame>(UGameplayStatics::CreateSaveGameObject(UPropHuntSaveGame::StaticClass()));
	}
	else
	{
		SaveGameObject = Cast<UPropHuntSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	}
	
}

void UPropHuntGameInstance::SetRoomId(FString RoomID)
{
	RoomCode = RoomID;
}

FString UPropHuntGameInstance::GetRoomId()
{
	return RoomCode;
}

FString UPropHuntGameInstance::GetSaveSlotName()
{
	return SlotName;
}

void UPropHuntGameInstance::SavePlayerName(FString NewName)
{
	SaveGameObject->PlayerName = NewName;

	UGameplayStatics::SaveGameToSlot(SaveGameObject, SlotName, 0);
}

FString UPropHuntGameInstance::GetSavedPlayerName()
{
	return SaveGameObject->PlayerName;
}

void UPropHuntGameInstance::SetHostedSessionName(FName SessionName)
{
	HostSessionName = SessionName;
}

FName UPropHuntGameInstance::GetHostedSessionName()
{
	return HostSessionName;
}

