// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Sessions/CreateSessionWidget.h"
#include "Widgets/Base Class/ButtonBaseWidget.h"

void UCreateSessionWidget::NativeConstruct()
{
	CreateButton->BaseButtonClicked.AddUObject(this, &UCreateSessionWidget::OnCreateButtonClicked);
}

void UCreateSessionWidget::OnCreateButtonClicked()
{

}
