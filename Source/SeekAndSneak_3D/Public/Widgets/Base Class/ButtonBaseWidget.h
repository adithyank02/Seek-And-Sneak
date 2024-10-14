// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonBaseWidget.generated.h"

class UButton;
class UTextBlock;



/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnButtonClicked);

UCLASS()
class SEEKANDSNEAK_3D_API UButtonBaseWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	void SynchronizeProperties()override;
	
	void NativeConstruct()override;

	UPROPERTY(meta = (BindWidget))
	UButton* BaseButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;

	UFUNCTION()
	void OnBaseButtonClicked();

public:

	FOnButtonClicked BaseButtonClicked;

	UPROPERTY(BlueprintReadWrite,EditInstanceOnly)
	FButtonStyle ButtonStyle;

	UPROPERTY(BlueprintReadWrite,EditInstanceOnly)
	FText Text;

	UPROPERTY(BlueprintReadWrite,EditInstanceOnly)
	FSlateFontInfo FontInfo;
};
