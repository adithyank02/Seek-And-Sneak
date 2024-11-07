// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ErrorWidget.generated.h"

class UButtonBaseWidget;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UErrorWidget : public UUserWidget
{
	GENERATED_BODY()


	void NativeConstruct();

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* CloseButton;
	
	UFUNCTION()
	void OnCloseButtonClicked();
};
