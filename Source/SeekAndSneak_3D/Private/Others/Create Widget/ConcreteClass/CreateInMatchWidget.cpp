// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/Create Widget/ConcreteClass/CreateInMatchWidget.h"
#include "Blueprint/UserWidget.h"

#include "Widgets/InMatch/HunterInMatchWidget.h"
#include "Widgets/InMatch/PropInMatchWidget.h"

CreateInMatchWidget::CreateInMatchWidget()
{
	//Loading Widget Asset
	HunterInMatchWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/InMatch/BP_HunterInMatchWidget.BP_HunterInMatchWidget_C"));
	PropInMatchWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/InMatch/BP_PropInMatchWidget.BP_PropInMatchWidget_C"));

}

CreateInMatchWidget::~CreateInMatchWidget()
{
}

void CreateInMatchWidget::Begin(APlayerController* PlayerController, ECharacterType CharacterType)
{
	if (CharacterType == ECharacterType::HunterCharacter && HunterInMatchWidgetClass)
	{
		PlayerCharacterType = CharacterType;
		HunterWidget = CreateWidget<UHunterInMatchWidget>(PlayerController, HunterInMatchWidgetClass);
		if (HunterWidget)HunterWidget->AddToViewport();
	}
	else if (CharacterType == ECharacterType::PropCharacter && PropInMatchWidgetClass)
	{
		PlayerCharacterType = CharacterType;
		PropWidget = CreateWidget<UPropInMatchWidget>(PlayerController, PropInMatchWidgetClass);
		if (PropWidget)PropWidget->AddToViewport();
	}

}

void CreateInMatchWidget::End()
{
	if (PlayerCharacterType == ECharacterType::HunterCharacter)
	{
		HunterWidget->RemoveFromParent();
	}
	else
	{
		PropWidget->RemoveFromParent();
	}
	
	//RemovePointerRef();
}

void CreateInMatchWidget::RemovePointerRef()
{
	/*HunterWidget = nullptr;
	PropWidget = nullptr;
	HunterInMatchWidgetClass = nullptr;
	PropInMatchWidgetClass = nullptr;

	delete HunterWidget;
	delete PropWidget;
	delete HunterInMatchWidgetClass;
	delete PropInMatchWidgetClass;*/
}
