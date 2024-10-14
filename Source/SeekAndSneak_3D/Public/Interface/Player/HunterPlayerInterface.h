// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HunterPlayerInterface.generated.h"


class UPropProximityNotifier;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHunterPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SEEKANDSNEAK_3D_API IHunterPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool CanRun() = 0;
	virtual USkeletalMeshComponent* GetWeaponMeshComp() = 0;
	virtual void SetFireWeaponLoc(FVector& StartPoint, FVector& ControlFrowardVector) = 0 ;

	virtual UPropProximityNotifier* GetPropProximityInstance() = 0;

};
