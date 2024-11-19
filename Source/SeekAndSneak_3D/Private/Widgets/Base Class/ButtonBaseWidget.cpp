// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Base Class/ButtonBaseWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SlateCore.h"




void UButtonBaseWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	ButtonText->SetText(Text);
	ButtonText->SetFont(FontInfo);

	BaseButton->SetStyle(ButtonStyle);

}

void UButtonBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BaseButton->OnReleased.AddDynamic(this, &UButtonBaseWidget::OnBaseButtonClicked);

}

void UButtonBaseWidget::OnBaseButtonClicked()
{
	BaseButtonClicked.ExecuteIfBound();


}
