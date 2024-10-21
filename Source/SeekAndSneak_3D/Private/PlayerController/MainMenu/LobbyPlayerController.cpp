// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/MainMenu/LobbyPlayerController.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"

#include "Kismet/KismetSystemLibrary.h"

ALobbyPlayerController::ALobbyPlayerController()
{
	//Cusotm Trasform For Camera View In The World
	CameraActorSpawnTransform.SetLocation(FVector(450, -40, 180));
	CameraActorSpawnTransform.SetRotation(FQuat::MakeFromRotator(FRotator(-20,0,0)));/*Axis Is YZX*/
	CameraActorSpawnTransform.SetScale3D(FVector(1, 1, 1));
}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		FTimerHandle SpawnCameraTimer;
		GetWorld()->GetTimerManager().SetTimer(SpawnCameraTimer, this, &ALobbyPlayerController::SpawnCameraActor, 0.1, false);
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
}

