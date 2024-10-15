// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Sessions/FindSessionWidget.h"
#include "Widgets/Base Class/ButtonBaseWidget.h"

void UFindSessionWidget::NativeConstruct()
{
	FindButton->BaseButtonClicked.BindUObject(this, &UFindSessionWidget::OnFindButtonClicked);
}

void UFindSessionWidget::OnFindButtonClicked()
{

}
