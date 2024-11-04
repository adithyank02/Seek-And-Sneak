// Fill out your copyright notice in the Description page of Project Settings.


#include "Feature/Hunter/PropProximity/PropProximityNotifier.h"
#include "GameFramework/Character.h"
#include "PropPlayer/PropPlayer.h"
#include "Runtime/Engine/Public/TimerManager.h"



void UPropProximityNotifier::Start(ACharacter* Player)
{
	GetPlayer = Player;


	FTimerHandle ProximityTimer;
	Player->GetWorld()->GetTimerManager().SetTimer(ProximityTimer, this, &UPropProximityNotifier::CheckProximity, 2,true);
}

void UPropProximityNotifier::CheckProximity()
{
	StartPoint = GetPlayer->GetActorLocation();
	EndPoint = StartPoint;

	bIsHit = GetPlayer->GetWorld()->SweepMultiByObjectType(HitResultArray, StartPoint, EndPoint, FQuat::Identity, ObjectQueryParams, FCollisionShape::MakeSphere(Radius));

	if (bIsHit && HitResultArray.Num() > 0)
	{
		if (!DoesPlayerDetect())
		{
			bProximityChangeOccur = DoesProximityNeedToUpdate(-1);
		}
	}

	//Only Executing If The Player Is Changed The Proximity Zone Area -- Avoiding Unecessary Calls
	if (bProximityChangeOccur)ProximityNotifierDelegate.ExecuteIfBound(CurrentRange);

}

//---------Helper Function-------------

bool UPropProximityNotifier::DoesPlayerDetect()
{
	for (const FHitResult& HitResult : HitResultArray)
	{
		if (HitResult.GetActor()->IsA(APropPlayer::StaticClass()))
		{
			bProximityChangeOccur = DoesProximityNeedToUpdate(FVector::Dist(StartPoint, HitResult.GetActor()->GetActorLocation()));
			return true;
		}
	}
	return false;
}

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


