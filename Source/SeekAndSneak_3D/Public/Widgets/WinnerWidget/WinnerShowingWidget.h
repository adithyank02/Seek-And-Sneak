// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Others/EnumClass/CharacterTypeEnum.h"
#include "WinnerShowingWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UWinnerShowingWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct()override;

	ECharacterType MatchWinnerCharacterType;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WinnerAnnouncingText;

	void SetAnnouncingText();

	FString HunterWinningText = FString("Hunters Have Won The Match");
	FString PropWinningText = FString("Props Have Won The Match");

};
