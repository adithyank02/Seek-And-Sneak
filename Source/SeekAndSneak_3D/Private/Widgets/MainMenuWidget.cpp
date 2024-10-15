// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenuWidget.h"
#include "Widgets/SessionWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateSessionButton->BaseButtonClicked.BindUObject(this, &UMainMenuWidget::OnCreateSessionButtonClicked);
	ExitGameButton->BaseButtonClicked.BindUObject(this, &UMainMenuWidget::OnExitGameButtonClicked);

//	WidgetSwitcher->AddChild(this);
	WidgetSwitcher->AddChild(SessionWidget);	

	SessionWidget->BackButton->BaseButtonClicked.BindUObject(this, &UMainMenuWidget::SessionWidgetBackButton);

}

void UMainMenuWidget::OnCreateSessionButtonClicked()
{
	WidgetSwitcher->SetActiveWidget(SessionWidget);
}

void UMainMenuWidget::OnExitGameButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),nullptr, EQuitPreference::Quit, false);
}

void UMainMenuWidget::SessionWidgetBackButton()
{
	WidgetSwitcher->SetActiveWidgetIndex(0);
}
