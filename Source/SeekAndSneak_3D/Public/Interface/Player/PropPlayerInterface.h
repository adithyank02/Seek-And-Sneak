// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PropPlayerInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPropPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SEEKANDSNEAK_3D_API IPropPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void SetPlayerMesh(UStaticMesh* NewMesh) = 0;
	virtual UStaticMesh* GetPlayerMesh() = 0;
	virtual void SetCapsuleSize(float Radius, float Height) = 0;
};
