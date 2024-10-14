// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Base Class/ButtonBaseWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	void NativeConstruct()override;

	//Using The Button Widget In Main Widget
	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* CreateSessionButton;

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* JoinSessionButton;

	void OnCreateSessionButtonClicked();
	
};
