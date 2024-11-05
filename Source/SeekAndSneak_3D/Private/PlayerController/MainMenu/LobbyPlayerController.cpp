// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/MainMenu/LobbyPlayerController.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"

#include "Others/LobbyCharacter.h"
#include "Interface/PropHuntPlayerState/PlayerStateInterface.h"
#include "GameFramework/PlayerState.h"

#include "Widgets/LobbyWidget.h"
#include "Kismet/KismetSystemLibrary.h"

ALobbyPlayerController::ALobbyPlayerController()
{
	//Cusotm Trasform For Camera View In The World
	CameraActorSpawnTransform.SetLocation(FVector(450, -40, 180));
	CameraActorSpawnTransform.SetRotation(FQuat::MakeFromRotator(FRotator(-20,0,0)));/*Axis Is YZX*/
	CameraActorSpawnTransform.SetScale3D(FVector(1, 1, 1));

	ConstructorHelpers::FClassFinder<ULobbyWidget>LobbyWidget(TEXT("/Game/Widgets/Menu/BP_LobbyWidget.BP_LobbyWidget_C"));

	if (LobbyWidget.Succeeded())
	{
		LobbyWidgetClass = LobbyWidget.Class;
	}

}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		FTimerHandle SpawnCameraTimer;
		GetWorld()->GetTimerManager().SetTimer(SpawnCameraTimer, this, &ALobbyPlayerController::SpawnCameraActor, 0.01, false);

		FTimerHandle ShowTextTimer;
		GetWorld()->GetTimerManager().SetTimer(ShowTextTimer, this, &ALobbyPlayerController::SetPlayerName, 1, false);
	}
}

void ALobbyPlayerController::SpawnCameraActor()
{
	ACameraActor* CameraActor = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), CameraActorSpawnTransform);

	if (CameraActor)
	{
		if (UCameraComponent* CameraComponent = CameraActor->FindComponentByClass<UCameraComponent>())
		{
			CameraComponent->bConstrainAspectRatio = false;
			SetViewTarget(CameraActor);
		}
	}
	CreateLobbyWidget();
}

void ALobbyPlayerController::CreateLobbyWidget()
{
	if (LobbyWidgetClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), LobbyWidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();

			SetInputModeType(Widget);
		}
	}
}

void ALobbyPlayerController::SetInputModeType(UUserWidget* CreatedWidget)
{
	FInputModeUIOnly InputMode; 

	InputMode.SetWidgetToFocus(CreatedWidget->TakeWidget());
	SetInputMode(InputMode);

	bShowMouseCursor = true;
}

void ALobbyPlayerController::SetPlayerName()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("On Posses Called"), true, true, FLinearColor::Red, 2);

	if (IPlayerStateInterface* PlayerStateInterface = Cast<IPlayerStateInterface>(GetPlayerState<APlayerState>()))
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Game STate Called"), true, true, FLinearColor::Green, 2);
		if (ALobbyCharacter* PlayerCharacter = Cast<ALobbyCharacter>(GetPawn()))
		{
			PlayerCharacter->ShowPlayerName(PlayerStateInterface->GetPlayerName());

			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Pawn Called"), true, true, FLinearColor::White, 2);

		}
		else
		{
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Pawn Not Called"), true, true, FLinearColor::Black, 2);
		}
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Game STate Not Called"), true, true, FLinearColor::Blue, 2);
	}
}

void ALobbyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	
}

