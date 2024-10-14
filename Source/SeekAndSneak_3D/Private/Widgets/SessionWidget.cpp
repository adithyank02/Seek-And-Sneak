// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SessionWidget.h"
#include "Widgets/Base Class/ButtonBaseWidget.h"

void USessionWidget::NativeConstruct()
{
	BackButton->BaseButtonClicked.AddUObject(this, &USessionWidget::OnBackButtonClicked);
}

void USessionWidget::OnBackButtonClicked()
{

}
