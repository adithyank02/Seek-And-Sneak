// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Feature/Hunter/PropProximity/PropProximityNotifier.h"
#include "HunterInMatchWidget.generated.h"

class UImage;
class UTextBlock;
class UWidgetSwitcher;
class UPauseGameWidget;


/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UHunterInMatchWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UHunterInMatchWidget(const FObjectInitializer& ObjectInitializer);

	void NativeConstruct() override;

protected:

	UPROPERTY(meta = (BindWidget))
	UImage* Corsshairpng;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PropProximityText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InMatchTimerText_Seconds;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InMatchTimerText_Minutes;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HunterTotalAliveCount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PropTotalAliveCount;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	TSubclassOf<UPauseGameWidget>PauseGameWidgetClass;

	UPauseGameWidget* PauseGameWidget;

	int HunterPlayerCount = 0;
	int PropPlayerCount = 0;

	void UpdateProximityTextAndColor(const FText Text, const FLinearColor Color);

private:

	//Avoiding Re-Intialization On Each Time
	int Minutes = 0;
	int Seconds = 0;

	void SetTextOnMatchTimerUpdate(int32 TimerValue);

	/*Function That Listen To Event Delegate From The UPropProximityNotifier*/
	void OnProximityChange(EProximityRange CurrentRange);

	//Proximity Properties
	const FText HotText = FText::FromString("HOT");
	const FText WarmText = FText::FromString("WARM");
	const FText CoolText = FText::FromString("COOL");
	const FText ColdText = FText::FromString("COLD");

	//Pre defining Proximity Text Color
	const FLinearColor HotTextColor = FLinearColor(219.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f);    //Red Color
	const FLinearColor WarmTextColor = FLinearColor(232.0f / 255.0f, 155.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f);  //Orange Color
	const FLinearColor CoolTextColor = FLinearColor(0.0f / 255.0f, 189.0f / 255.0f, 239.0f / 255.0f, 255.0f / 255.0f);  //SkyBlue Color
	const FLinearColor ColdTextColor = FLinearColor(0.0f / 255.0f, 92.0f / 255.0f, 239.0f / 255.0f, 255.0f / 255.0f);   //Blue Color

public:

	void ChangeIndexOnWidgetSwitcher(int Index);
	
	void OnPropPlayerCaught(int HunterCount , int PropCount);
};
