// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SessionWidget.generated.h"

class UCreateSessionWidget;
class UFindSessionWidget;
class UButtonBaseWidget;

/**
 * 
 */
UCLASS()
class SEEKANDSNEAK_3D_API USessionWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UCreateSessionWidget* CreateSessionWidget;

	UPROPERTY(meta = (BindWidget))
	UFindSessionWidget* FindSessionWidget;

public:
	UPROPERTY(meta = (BindWidget))
	UButtonBaseWidget* BackButton;

};
