// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenuWidget.h"
#include "Widgets/SessionWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<USessionWidget>WidgetClass(TEXT("/Game/Widgets/BP_SessionWidget.BP_SessionWidget_C"));

	if (WidgetClass.Succeeded())
	{
		SessionWidgetClass = WidgetClass.Class;
	}
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateSessionButton->BaseButtonClicked.BindUObject(this, &UMainMenuWidget::OnCreateSessionButtonClicked);
	ExitGameButton->BaseButtonClicked.BindUObject(this, &UMainMenuWidget::OnExitGameButtonClicked);

	SessionWidget = CreateWidget<USessionWidget>(this,SessionWidgetClass);
	WidgetSwitcher->AddChild(SessionWidget);

	SessionWidget->BackButton->BaseButtonClicked.BindUObject(this, &UMainMenuWidget::SessionWidgetBackButton);
	
}

void UMainMenuWidget::OnCreateSessionButtonClicked()
{
	WidgetSwitcher->SetActiveWidgetIndex(1);
}

void UMainMenuWidget::OnExitGameButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),nullptr, EQuitPreference::Quit, false);
}

void UMainMenuWidget::SessionWidgetBackButton()
{
	//Back To Main Menu Widget
	WidgetSwitcher->SetActiveWidgetIndex(0);
}
