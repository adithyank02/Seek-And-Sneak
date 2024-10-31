// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/TextRenderComponent.h"

#include "LobbyCharacter.generated.h"




UCLASS()
class SEEKANDSNEAK_3D_API ALobbyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
    
	ALobbyCharacter();

	UPROPERTY(EditDefaultsOnly)
	UTextRenderComponent* PlayerNameText;

	void ShowPlayerName(FString PlayerName);

private:

	UFUNCTION(Server,Reliable)
	void SetPlayerName_Server(const FString& PlayerName);

	UFUNCTION(NetMulticast,Reliable)
	void SetPlayerName_Multicast(const FString& PlayerName);


































};
