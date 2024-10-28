// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PropInMatchWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UPropInMatchWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

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

	//Avoiding Re-Intialization On Each Time
	int Minutes;
	int Seconds;

	void SetTextOnMatchTimerUpdate(int32 TimerValue);

};
