// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Others/EnumClass/CharacterWidgetUpdateEnum.h"
#include "PropInMatchWidget.generated.h"

class UTextBlock;
class UWidgetSwitcher;
class UProgressBar;
class UImage;
class UPauseGameWidget;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UPropInMatchWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPropInMatchWidget(const FObjectInitializer& ObjectInitializer);

	void NativeConstruct()override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InMatchTimerText_Seconds;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InMatchTimerText_Minutes;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HunterTotalAliveCount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PropTotalAliveCount;

	UPROPERTY(meta = (BindWidget))
    UProgressBar* PlayerHealthBar;

	UPROPERTY(meta = (BindWidget))
	UImage* MorphAbilityImage;

	UPROPERTY(meta = (BindWidget))
	UImage* CloneAbilityImage;

	UPROPERTY(meta = (BindWidget))
	UImage* SmokeBombAbilityImage;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	float TotalPercentage;

	//Avoiding Re-Intialization On Each Time
	int Minutes;
	int Seconds;

	void SetTextOnMatchTimerUpdate(int32 TimerValue);

public:

	void SetPlayerHealthOnDamage(float DamageCaused);

	void OnHunterPlayerTotalCountChange(int HunterPlayerCount);
	void OnPropPlayerTotalCountChange(int PropPlayerCount);

	void OnWidgetUpdate(ECharacterWidgetUpdate UpdateType, bool IsReset);

};
