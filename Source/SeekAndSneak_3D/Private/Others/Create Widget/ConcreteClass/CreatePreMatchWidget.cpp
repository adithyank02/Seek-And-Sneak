// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/Create Widget/ConcreteClass/CreatePreMatchWidget.h"
#include "Widgets/PreMatch/CharacterPreMatchWidget.h"
#include "Blueprint/UserWidget.h"

CreatePreMatchWidget::CreatePreMatchWidget()
{
	PreMatchWidgetClass = LoadClass<UCharacterPreMatchWidget>(nullptr, TEXT("/Game/Widgets/BP_CharacterPreMatchWidget.BP_CharacterPreMatchWidget_C"));
}

CreatePreMatchWidget::~CreatePreMatchWidget()
{
}

void CreatePreMatchWidget::Begin(APlayerController* PlayerController, ECharacterType CharacterType)
{
	if (PreMatchWidgetClass && PlayerController->IsLocalController())
	{
		UCharacterPreMatchWidget* PreMatchWidget = CreateWidget<UCharacterPreMatchWidget>(PlayerController, PreMatchWidgetClass);
		if (PreMatchWidget)
		{
			PreMatchWidget->AddToViewport();
		}
		
	}

}
