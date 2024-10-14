// Fill out your copyright notice in the Description page of Project Settings.


#include "HunterPlayer/HunterPlayer.h"
#include "Net/UnrealNetwork.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/CharacterMovementReplication.h"

#include "PlayerState/MotionState/PlayerMove/PlayerMove.h"
#include "PlayerState/MotionState/PlayerLook/PlayerLook.h"

#include "PlayerState/InputState/Hunter/OnPlayerFire.h"

#include "Interface/Feature/Hunter/PropProximityInterface.h"
#include "Runtime/Engine/Public/TimerManager.h"

#include "Kismet/KismetSystemLibrary.h"

#include "PlayerController/HunterPlayerController.h"

bool AHunterPlayer::CanRun()
{
	return IsPlayerRunning;
}

USkeletalMeshComponent* AHunterPlayer::GetWeaponMeshComp()
{
	return WeaponMesh;
}

void AHunterPlayer::SetFireWeaponLoc(FVector& StartPoint, FVector& ControlFrowardVector)
{
	StartPoint = FPSCamera->GetComponentLocation();
	ControlFrowardVector = FPSCamera->GetComponentRotation().Vector();
}

UPropProximityNotifier* AHunterPlayer::GetPropProximityInstance()
{
	return PropProximity;
}

void AHunterPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHunterPlayer, IsPlayerRunning);
}

// Sets default values
AHunterPlayer::AHunterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetReplicateMovement(true);

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FPSCamera->SetupAttachment(GetMesh(), TEXT("head"));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKMesh"));
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("WeaponHoldPosition"));

	MotionStateLibrary.Add(MotionEnum::OnMove, MakeUnique<PlayerMove>());
	MotionStateLibrary.Add(MotionEnum::OnLook, MakeUnique<PlayerLook>());

	InputStateLibrary.Add(InputStateEnum::OnHunterFire, MakeUnique<OnPlayerFire>());

	MaxBulletCount = 30;
	WeaponBulletCount = MaxBulletCount;

	WeaponFireRate = 0.15f;
}


// Called when the game starts or when spawned
void AHunterPlayer::BeginPlay()
{
	Super::BeginPlay();

	PropProximity = NewObject<UPropProximityNotifier>();

	if (IsLocallyControlled())
	{
		StartPropProximity();
	}

}

// Called every frame
void AHunterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHunterPlayer::StartPropProximity()
{
	if (IPropProximityInterface* Interface = Cast<IPropProximityInterface>(PropProximity))
	{
		Interface->Start(this);
	}
}

void AHunterPlayer::PlayerJogFunction(const FInputActionValue& InputValue)
{
	MotionStateLibrary[MotionEnum::OnMove]->Begin(this, InputValue);
}

void AHunterPlayer::LookFunction(const FInputActionValue& InputValue)
{
	MotionStateLibrary[MotionEnum::OnLook]->Begin(this, InputValue);
}

//---------------------------------------------------------------------------------------->>>>>> ( Sprint Function )
void AHunterPlayer::StartSprintFunction()
{
	if (GetVelocity().Size() != 0)
	{
		if (HasAuthority())Sprint_OnMulticast(500.0f, true);
		else Sprint_OnServer(500.0f, true);
	}
}

void AHunterPlayer::StopSprintFunction()
{
	if (HasAuthority())Sprint_OnMulticast(250.0f, false);
	else Sprint_OnServer(200.0f, false);
}

void AHunterPlayer::Sprint_OnServer_Implementation(float WalkSpeed,bool CanSprint)         /*Server*/
{
	Sprint_OnMulticast(WalkSpeed, CanSprint);
}

void AHunterPlayer::Sprint_OnMulticast_Implementation(float WalkSpeed,bool CanSprint)      /*Multicast*/
{
	IsPlayerRunning = CanSprint;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
//------------------------------------------------------------------------------------------>>>>>


//------------------------------------------------------------------------------------------>>>>> ( Firing Weapon )
void AHunterPlayer::StartFiringWeapon()
{
	GetWorld()->GetTimerManager().SetTimer(FiringWeaponTimer, this, &AHunterPlayer::OnWeaponFiring,WeaponFireRate,true);
}

void AHunterPlayer::OnWeaponFiring()
{
	if (WeaponBulletCount > 0)
	{
		if (HasAuthority())
		{
			FireWeapon_OnMulticast(FPSCamera->GetComponentLocation(),FPSCamera->GetForwardVector());
		}
		else
		{
			FireWeapon_OnServer(FPSCamera->GetComponentLocation(), FPSCamera->GetForwardVector());
		}
		WeaponBulletCount--;
	}
}


void AHunterPlayer::StopFiringWeapon()
{
	GetWorld()->GetTimerManager().ClearTimer(FiringWeaponTimer);
	
}
void AHunterPlayer::FireWeapon_OnServer_Implementation(FVector StartPoint, FVector EndPoint)
{
	FireWeapon_OnMulticast(StartPoint,EndPoint);
}
void AHunterPlayer::FireWeapon_OnMulticast_Implementation(FVector StartPoint, FVector EndPoint)
{	
	
	InputStateLibrary[InputStateEnum::OnHunterFire]->SetLocation(StartPoint, EndPoint);
	InputStateLibrary[InputStateEnum::OnHunterFire]->Begin(this);
}
