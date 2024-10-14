// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreateSessionWidget.generated.h"

class USizeBox;
class UBorder;
class UEditableTextBox;
class UButtonBaseWidget;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API UCreateSessionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	USizeBox* SizeBox;

	UPROPERTY(meta  = (BindWidget))
	UBorder* Border;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* TotalPlayerNum_TextBox;

	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* CreateButton;

	UFUNCTION()
	void OnCreateButtonClicked();
	
};
