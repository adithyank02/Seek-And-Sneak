// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenuWidget.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateSessionButton->BaseButtonClicked.AddUObject(this, &UMainMenuWidget::OnCreateSessionButtonClicked);

}

void UMainMenuWidget::OnCreateSessionButtonClicked()
{

}
