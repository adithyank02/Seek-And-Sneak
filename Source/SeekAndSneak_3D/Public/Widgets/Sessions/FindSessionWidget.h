// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FindSessionWidget.generated.h"

class UEditableTextBox;
class UButtonBaseWidget;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UFindSessionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct()override;

private:

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* EnterSessionCode_TextBox;

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* FindButton;

	UFUNCTION()
	void OnFindButtonClicked();
	
};
