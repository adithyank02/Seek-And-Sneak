// Fill out your copyright notice in the Description page of Project Settings.


#include "PropPlayer/PropPlayer.h"
#include "Components/CapsuleComponent.h"

#include "PlayerState/MotionState/PlayerMove/PlayerMove.h"
#include "PlayerState/MotionState/PlayerLook/PlayerLook.h"

#include "PlayerState/InputState/Prop/OnPropMorph.h"
#include "PlayerState/InputState/Prop/OnPropClone.h"



#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Interface/GameMode/PropHuntGameModeInterface.h"
#include "GameFramework/GameMode.h"

#include "NiagaraFunctionLibrary.h"


void APropPlayer::SetPlayerMesh(UStaticMesh* NewMesh)
{
	if (PlayerMesh->GetStaticMesh() != NewMesh)
	{
		PlayerMesh->SetStaticMesh(NewMesh);
		PropMeshChanged.ExecuteIfBound();
	}
}

UStaticMesh* APropPlayer::GetPlayerMesh()
{
	return PlayerMesh->GetStaticMesh();
}

//Re sizing The Prop Collsion Component
void APropPlayer::SetCapsuleSize(float Radius, float Height)
{
	GetCapsuleComponent()->SetCapsuleRadius(Radius);
	GetCapsuleComponent()->SetCapsuleHalfHeight(Height);
}

void APropPlayer::PlayerGetDamaged(float DamageCaused)
{
	if (IsLocallyControlled())
	{
		PropHealth -= DamageCaused;
		PropPlayerDamaged.Broadcast(DamageCaused);
		if (PropHealth <= 0)
		{
			//Stoping The ScanningMorphFunction
			GetWorld()->GetTimerManager().ClearTimer(ScanningPropsTimer);

			PropMeshChanged.Unbind();

			//Player Caught
			OnPropPlayerCaught();

		}
	}
	
}

TArray<UStaticMesh*> APropPlayer::GetMorphableMeshArray()
{
	return MorphMeshArray;
}

APropPlayer* APropPlayer::GetPropPlayerRef()
{
	return this;
}

void APropPlayer::OnPlayerWidgetUpdate(EPropWidgetUpdate UpdateType, bool IsReset)
{
	PropWidgetUpdate.ExecuteIfBound(UpdateType, IsReset);
}

// Sets default values
APropPlayer::APropPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(RootComponent);

	TPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	TPSCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actual Mesh"));
	PlayerMesh->SetupAttachment(GetMesh());
	
	MotinStateLibrary.Add(MotionEnum::OnMove,MakeUnique<PlayerMove>());
	MotinStateLibrary.Add(MotionEnum::OnLook,MakeUnique<PlayerLook>());

	InputStateLibrary.Add(InputStateEnum::OnPropMorph,MakeUnique<OnPropMorph>());
	InputStateLibrary.Add(InputStateEnum::OnPropClone, MakeUnique<OnPropClone>());

	

	MorphMaxCoolDownTime = 15.0f;
	TotalCloneCount = 5.0f;

	//Load The Bomb Particle
	SmokeBombParticle = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Other_BP/NiagraParticle/NS_SmokeBomb.NS_SmokeBomb"));
	PlayerCaughtParticle = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Other_BP/NiagraParticle/NS_PropPlayerCaught.NS_PropPlayerCaught"));

	PropHealth = 10.0f;

}


// Called when the game starts or when spawned
void APropPlayer::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle ScanningTimer;
	GetWorld()->GetTimerManager().SetTimer(ScanningTimer, this, &APropPlayer::SetScanningProp,ScanningPropInitialTimer, false);
}

void APropPlayer::StartScanningProps()
{
	if (ScanPropClass)
	{
		GetWorld()->GetTimerManager().SetTimer(ScanningPropsTimer, this, &APropPlayer::ScanningPropsForMorphing,0.5,true);
	}
}

void APropPlayer::ScanningPropsForMorphing()
{
	ScanPropClass->StartScanning();
}

void APropPlayer::SetScanningProp()
{
	if (IsLocallyControlled())
	{
		ScanPropClass = MakeUnique<ScanProps>(MorphMeshArray,this);
		StartScanningProps();
	}
}


// Called every frame
void APropPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APropPlayer::MoveFunction(const FInputActionValue& InputValue)
{
	MotinStateLibrary[MotionEnum::OnMove]->Begin(this, InputValue);
}

void APropPlayer::LookFunction(const FInputActionValue& InputValue)
{
	MotinStateLibrary[MotionEnum::OnLook]->Begin(this, InputValue);
}

void APropPlayer::StartJumpFunction()
{
	Jump();
}

void APropPlayer::StopJumpFunction()
{
	StopJumping();
}


//---------------------------------------------------------------------------------------------->>>>> ( Prop Morph Function )
void APropPlayer::MorphObjectFunction()
{
	if (MorphCoolDownTime == 0)
	{
		if (HasAuthority())
		{
			MorphObject_Multicast();
		}
		else
		{
			MorphObject_Server();
		}
		MorphCoolDownTime = MorphMaxCoolDownTime;

		//Reseting Cloned Count when New Mesh Get Morph
		ClonedCount = 0; 

		//Updating The Widget Accoridng 
		PropWidgetUpdate.ExecuteIfBound(EPropWidgetUpdate::OnMorphUpdate, false);
		PropWidgetUpdate.ExecuteIfBound(EPropWidgetUpdate::OnCloneUpdate, true);

		GetWorld()->GetTimerManager().SetTimer(MorphCoolDownTimer, this, &APropPlayer::UpdateMorphCoolDownTime, 1, true);
	}
}

void APropPlayer::MorphObject_Server_Implementation()
{
	MorphObject_Multicast();
}

void APropPlayer::MorphObject_Multicast_Implementation()
{
	InputStateLibrary[InputStateEnum::OnPropMorph]->Begin(this);
}

void APropPlayer::UpdateMorphCoolDownTime()
{
	MorphCoolDownTime--;
	if (MorphCoolDownTime == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(MorphCoolDownTimer);

		PropWidgetUpdate.ExecuteIfBound(EPropWidgetUpdate::OnMorphUpdate, true);
	}
}

//----------------------------------------------------------------------------------------------->>>>>

//----------------------------------------------------------------------------------------------->>>>> ( Prop Clone Function )
void APropPlayer::PropCloneFunction()
{
	if (ClonedCount < TotalCloneCount)
	{
		if (HasAuthority())
		{
			PropClone_Multicast();
		}
		else
		{
			PropClone_Server();
		}
		ClonedCount++;

		if (ClonedCount == TotalCloneCount)PropWidgetUpdate.ExecuteIfBound(EPropWidgetUpdate::OnCloneUpdate, false);
	}
}

void APropPlayer::PropClone_Server_Implementation()
{
	PropClone_Multicast();
}
void APropPlayer::PropClone_Multicast_Implementation()
{
	InputStateLibrary[InputStateEnum::OnPropClone]->Begin(this);
	if (bMorphMeshArrayPassed)MorphMeshArray.Empty(); bMorphMeshArrayPassed = false;
}
//---------------------------------------------------------------------------------------------->>>>> ( Prop Clone Function )

//---------------------------------------------------------------------------------------------->>>>> ( Prop Smoke Bomb )

void APropPlayer::SmokeBombFunction()
{
	if (TotalSmokeBombCount > 0)
	{
		if (HasAuthority())
		{
			SmokeBombOnMulticast();
		}
		else
		{
			SmokeBombOnServer();
		}
		TotalSmokeBombCount--;

		if (TotalSmokeBombCount == 0)PropWidgetUpdate.ExecuteIfBound(EPropWidgetUpdate::OnSmokeBombUpdate, false);
	}
	
}


void APropPlayer::SmokeBombOnServer_Implementation()
{
	SmokeBombOnMulticast();
}

void APropPlayer::SmokeBombOnMulticast_Implementation()
{
	if (SmokeBombParticle)UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SmokeBombParticle, GetActorLocation(), 
		                  FRotator(0.0f), FVector(1.0f), true, true, ENCPoolMethod::AutoRelease);
}
//---------------------------------------------------------------------------------------------->>>>> ( Prop Smoke Bomb )

void APropPlayer::OnPropPlayerCaught()
{
	if (HasAuthority())
	{
		//Calling Sharing The Information To GameMode
		if (IPropHuntGameModeInterface* GameModeInterface = Cast<IPropHuntGameModeInterface>(GetWorld()->GetAuthGameMode()))
		{
			GameModeInterface->OnPropPlayerCaught(GetController());
		}
		OnPlayerCaught_Multicast(GetController());
	}
	else
	{
		OnPlayerCaught_Server(GetController());
	}
}


void APropPlayer::OnPlayerCaught_Server_Implementation(AController* PlayerController)
{
	if (IPropHuntGameModeInterface* GameModeInterface = Cast<IPropHuntGameModeInterface>(GetWorld()->GetAuthGameMode()))
	{
		GameModeInterface->OnPropPlayerCaught(GetController());
	}
	OnPlayerCaught_Multicast(PlayerController);
}

void APropPlayer::OnPlayerCaught_Multicast_Implementation(AController* PlayerController)
{
	//Caught Indicating Niagara Particle
	if(PlayerCaughtParticle)UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),PlayerCaughtParticle, GetActorLocation(),
		FRotator(0.0f), FVector(1.0f), true, true, ENCPoolMethod::AutoRelease);

	//Temporary
	PlayerMesh->SetVisibility(false);
	PlayerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}


