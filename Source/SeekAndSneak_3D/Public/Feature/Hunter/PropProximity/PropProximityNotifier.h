// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interface/Feature/Hunter/PropProximityInterface.h"
#include "PropProximityNotifier.generated.h"

/**
 * 
 */

enum class EProximityRange : uint8
{
	Hot,
	Warm,
	Cool,
	Cold,
};


DECLARE_DELEGATE_OneParam(FOnProximityNotifier, EProximityRange);

UCLASS()
class SEEKANDSNEAK_3D_API UPropProximityNotifier : public UObject , public IPropProximityInterface
{
	GENERATED_BODY()

public:

	void Start(ACharacter* Player) override;

	FOnProximityNotifier ProximityNotifierDelegate;
	
protected:

	bool DoesProximityNeedToUpdate(double Distance);

private:

	EProximityRange CurrentRange;

	bool bProximityChangeOccur;

	//Proxmity Range 
	const float Hot = 900.0f;
	const float Warm = 1900.0f;
	const float Tolarance = 2.0f;


	UPROPERTY()
	ACharacter* GetPlayer;

	void CheckProximity();

	//Trace Variables
	bool bIsHit;
	const float Radius = 2900.0f;
	FHitResult HitResult;
	FVector StartPoint;
	FVector EndPoint;
	FCollisionQueryParams TraceParams;

};
