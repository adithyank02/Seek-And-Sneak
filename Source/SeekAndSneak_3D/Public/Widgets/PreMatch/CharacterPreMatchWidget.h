// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Others/EnumClass/CharacterTypeEnum.h"
#include "CharacterPreMatchWidget.generated.h"

class UTextBlock;
class UImage;
class IGameStateInterface;

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

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ShowTimerText;

	//Prop Power Up components 

	UPROPERTY(meta = (BindWidget))
	UImage* PropPowerUpImage_1;

	UPROPERTY(meta = (BindWidget))
	UImage* PropPowerUpImage_2;

	UPROPERTY(meta = (BindWidget))
	UImage* PropPowerUpImage_3;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PropPowerUpText_1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PropPowerUpText_2;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PropPowerUpText_3;

	/*For Setting The CharacterType Of The Controller*/
	void SetCharacterType();

	/*Set Text Accoriding To Character Type*/
	void SetWidgetText();

	/*Binded To Game State Delegate And Set the Updated Value To Text*/
	void SetTextOnMatchTimerUpdate(int32 MatchTimer);
	
};
