// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Others/ErrorWidget.h"
#include "Widgets/Base Class/ButtonBaseWidget.h"

void UErrorWidget::NativeConstruct()
{
	CloseButton->BaseButtonClicked.BindUObject(this, &UErrorWidget::OnCloseButtonClicked);
}

void UErrorWidget::OnCloseButtonClicked()
{
	RemoveFromParent();
}
