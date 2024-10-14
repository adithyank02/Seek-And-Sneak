// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Feature/Hunter/PropProximity/PropProximityNotifier.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct() override;

protected:

	UPROPERTY(meta = (BindWidget))
	UImage* Corsshairpng;

    UPROPERTY(meta = (BindWidget))
	UTextBlock* PropProximityText;

	void UpdateProximityTextAndColor(const FText Text, const FLinearColor Color);
	
private:

	/*Function That Listen To Event Delegate From The UPropProximityNotifier*/
	void OnProximityChange(EProximityRange CurrentRange);

	//Proximity Properties
	const FText HotText  = FText::FromString("HOT");
	const FText WarmText = FText::FromString("WARM");
	const FText CoolText = FText::FromString("COOL");
	const FText ColdText = FText::FromString("COLD");

	//Pre defining Proximity Text Color
	const FLinearColor HotTextColor  = FLinearColor(219.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f);    //Red Color
	const FLinearColor WarmTextColor = FLinearColor(232.0f / 255.0f, 155.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f);  //Orange Color
	const FLinearColor CoolTextColor = FLinearColor(0.0f / 255.0f, 189.0f / 255.0f, 239.0f / 255.0f, 255.0f / 255.0f);  //SkyBlue Color
	const FLinearColor ColdTextColor = FLinearColor(0.0f / 255.0f, 92.0f / 255.0f, 239.0f / 255.0f, 255.0f / 255.0f);   //Blue Color

};
