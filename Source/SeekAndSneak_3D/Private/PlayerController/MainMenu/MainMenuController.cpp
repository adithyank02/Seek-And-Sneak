// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/MainMenu/MainMenuController.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"

AMainMenuController::AMainMenuController()
{	
	static ConstructorHelpers::FClassFinder<UUserWidget>WidgetClass(TEXT("/Game/Widgets/BP_MainMenuWidget.BP_MainMenuWidget_C"));

	if (WidgetClass.Succeeded())
	{
		MainMenuClass = WidgetClass.Class;
	}
}

void AMainMenuController::BeginPlay()
{
	

	FTimerHandle DeleyTimer;
	GetWorld()->GetTimerManager().SetTimer(DeleyTimer, this, &AMainMenuController::DeleyFunction, 0.1);
}

void AMainMenuController::DeleyFunction()
{
	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
			SetInputModeType(MainMenuWidget);
		}
		
	}
	ACameraActor* CamActor = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), FTransform::Identity);

	if (CamActor)
	{
		if (UCameraComponent* CamComp = CamActor->GetComponentByClass<UCameraComponent>())
		{
			CamComp->bConstrainAspectRatio = false;
		}
		SetViewTarget(CamActor);

	}
}

void AMainMenuController::SetInputModeType(UUserWidget* CreatedWidget)
{
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(CreatedWidget->TakeWidget());

	SetInputMode(InputMode);

	bShowMouseCursor = true;
}
