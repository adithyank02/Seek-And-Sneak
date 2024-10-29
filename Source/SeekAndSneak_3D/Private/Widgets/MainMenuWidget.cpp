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
	static ConstructorHelpers::FClassFinder<USessionWidget>WidgetClass(TEXT("/Game/Widgets/Menu/BP_SessionWidget.BP_SessionWidget_C"));

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

	CheckForSavedPlayerName();
}

void UMainMenuWidget::OnPlayerNameCommitted(const FText& Text, ETextCommit::Type CommitType)
{
	Player_InGameName = Text.ToString();

	if (Player_InGameName.Len() > PlayerNameMaxLen || DoesContainWhiteSpace())
	{
		//Show As Erro And Setting The Limit For Player Name
		ShowPlayerNameError();
	}
	
}

void UMainMenuWidget::OnCreateSessionButtonClicked()
{
	if (!Player_InGameName.IsEmpty() && Player_InGameName.Len() <= PlayerNameMaxLen &&!DoesContainWhiteSpace())
	{
		if (IPropHuntGameInstInterface* InstanceInterface = Cast<IPropHuntGameInstInterface>(GetGameInstance()))
		{
			InstanceInterface->SavePlayerName(Player_InGameName);
			SavedPlayerName = Player_InGameName;
		}
		WidgetSwitcher->SetActiveWidgetIndex(1);
	}
	else
	{
		//Giving Error For Player And Reducing Size
		ShowPlayerNameError();
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

//---------Helper Function --------------


void UMainMenuWidget::ShowPlayerNameError()
{
	LongNameWarningText->SetVisibility(ESlateVisibility::Visible);
	EnterNameEditableBox->SetText(FText::FromString(Player_InGameName.Left(PlayerNameMaxLen)));
}


void UMainMenuWidget::CheckForSavedPlayerName()
{
	if (IPropHuntGameInstInterface* InstanceInterface = Cast<IPropHuntGameInstInterface>(GetGameInstance()))
	{
		if (UGameplayStatics::DoesSaveGameExist(InstanceInterface->GetSaveSlotName(), 0))
		{
			FString StoredName = InstanceInterface->GetSavedPlayerName();
			EnterNameEditableBox->SetText(FText::FromString(StoredName));
			Player_InGameName = StoredName;
		}
	}
}


bool UMainMenuWidget::DoesContainWhiteSpace()
{
	for (int itr = 0; itr < Player_InGameName.Len(); itr++)
	{
		if (FChar::IsWhitespace(Player_InGameName[itr]))return true;
	}
	return false;
}
