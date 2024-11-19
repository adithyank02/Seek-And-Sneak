// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/LobbyCharacter.h"


// Sets default values
ALobbyCharacter::ALobbyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PlayerNameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PlayerName"));
	PlayerNameText->SetupAttachment(RootComponent);

	PlayerNameText->SetVisibility(false);
}

void ALobbyCharacter::ShowPlayerName(FString PlayerName)
{
	if (IsLocallyControlled())
	{
		if (HasAuthority())
		{
			SetPlayerName_Multicast(PlayerName);
		}
		else
		{
			SetPlayerName_Server(PlayerName);
		}
	}
}

void ALobbyCharacter::SetPlayerName_Server_Implementation(const FString& PlayerName)
{
	SetPlayerName_Multicast(PlayerName);
}

void ALobbyCharacter::SetPlayerName_Multicast_Implementation(const FString& PlayerName)
{
	PlayerNameText->SetText(FText::FromString(PlayerName));
	PlayerNameText->SetVisibility(true);

}



