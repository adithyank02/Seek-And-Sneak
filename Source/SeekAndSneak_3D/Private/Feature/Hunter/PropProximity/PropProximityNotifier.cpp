// Fill out your copyright notice in the Description page of Project Settings.


#include "Feature/Hunter/PropProximity/PropProximityNotifier.h"
#include "GameFramework/Character.h"
#include "PropPlayer/PropPlayer.h"
#include "Runtime/Engine/Public/TimerManager.h"



void UPropProximityNotifier::Start(ACharacter* Player)
{
	GetPlayer = Player;
	TraceParams.AddIgnoredActor(Player);

	FTimerHandle ProximityTimer;
	Player->GetWorld()->GetTimerManager().SetTimer(ProximityTimer, this, &UPropProximityNotifier::CheckProximity, 1,true);
}

void UPropProximityNotifier::CheckProximity()
{
	StartPoint = GetPlayer->GetActorLocation();
	EndPoint = StartPoint;

	bIsHit = GetPlayer->GetWorld()->SweepSingleByChannel(HitResult, StartPoint, EndPoint,
		                                                FQuat::Identity, ECC_Visibility,
		                                                FCollisionShape::MakeSphere(Radius),TraceParams);

	if (bIsHit && HitResult.GetActor()->IsA(APropPlayer::StaticClass()))
	{
		bProximityChangeOccur = DoesProximityNeedToUpdate(FVector::Dist(StartPoint, HitResult.GetActor()->GetActorLocation()));
	}
	else
	{
		bProximityChangeOccur =  DoesProximityNeedToUpdate(-1);
	}
	//Only Executing If The Player Is Changed The Proximity Zone Area -- Avoiding Unecessary Calls
	if (bProximityChangeOccur)ProximityNotifierDelegate.ExecuteIfBound(CurrentRange);

}

//---------Helper Function-------------

bool UPropProximityNotifier::DoesProximityNeedToUpdate(double Distance)
{
	if (Distance == -1)
	{
		if (CurrentRange != EProximityRange::Cold)CurrentRange = EProximityRange::Cold; return true;
	}

	else if (Distance <= Hot + Tolarance)
	{
		if (CurrentRange != EProximityRange::Hot)CurrentRange = EProximityRange::Hot; return true;
	}

	else if (Distance <= Warm + Tolarance)
	{
		if (CurrentRange != EProximityRange::Warm)CurrentRange = EProximityRange::Warm; return true;
	}

	else
	{
		if (CurrentRange != EProximityRange::Cool)CurrentRange = EProximityRange::Cool; return true;
	}

	return false;
}


