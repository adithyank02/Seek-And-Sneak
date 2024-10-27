// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Others/EnumClass/CharacterTypeEnum.h"
#include "CharacterPreMatchWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UCharacterPreMatchWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	void NativeConstruct();

	ECharacterType PlayerCharacter;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PreMatchTimer;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharacterTypeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharacterObjectiveText;

	/*For Setting The CharacterType Of The Controller*/
	void SetCharacterType();
	/*Binding The Text To Game State Timer*/
	void SetPreMatchTimer();
	/*Set Text Accoriding To Character Type*/
	void SetWidgetText();
	
};
