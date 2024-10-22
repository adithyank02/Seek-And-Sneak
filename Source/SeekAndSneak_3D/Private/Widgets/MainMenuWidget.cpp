// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenuWidget.h"
#include "Widgets/SessionWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/GameInstance/PropHuntGameInstInterface.h"

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

	LongNameWarningText->SetVisibility(ESlateVisibility::Hidden);

	CreateSessionButton->BaseButtonClicked.BindUObject(this, &UMainMenuWidget::OnCreateSessionButtonClicked);
	ExitGameButton->BaseButtonClicked.BindUObject(this, &UMainMenuWidget::OnExitGameButtonClicked);

	SessionWidget = CreateWidget<USessionWidget>(this,SessionWidgetClass);
	WidgetSwitcher->AddChild(SessionWidget);

	EnterNameEditableBox->OnTextCommitted.AddDynamic(this, &UMainMenuWidget::OnPlayerNameCommitted);

	SessionWidget->BackButton->BaseButtonClicked.BindUObject(this, &UMainMenuWidget::SessionWidgetBackButton);
	
}

void UMainMenuWidget::OnPlayerNameCommitted(const FText& Text, ETextCommit::Type CommitType)
{
	FString NameStr = Text.ToString();

	if (NameStr.Len() > 8)
	{
		LongNameWarningText->SetVisibility(ESlateVisibility::Visible);
		//Setting The Limit For Player Name
		EnterNameEditableBox->SetText(FText::FromString(NameStr.Left(PlayerNameMaxLen)));
	}
	PlayerInGameName = NameStr;
}

void UMainMenuWidget::OnCreateSessionButtonClicked()
{
	if (!PlayerInGameName.IsEmpty() && PlayerInGameName.Len() <= PlayerNameMaxLen)
	{
		if (IPropHuntGameInstInterface* InstanceInterface = Cast<IPropHuntGameInstInterface>(GetGameInstance()))
		{
			InstanceInterface->SetPlayerInGameName(PlayerInGameName);
		}

		WidgetSwitcher->SetActiveWidgetIndex(1);
	}
	else
	{
		LongNameWarningText->SetVisibility(ESlateVisibility::Visible);
		EnterNameEditableBox->SetText(FText::FromString(""));
	}
	
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
