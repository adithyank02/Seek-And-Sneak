// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SEEKANDSNEAK_3D_API ScanProps
{
public:
	ScanProps();
	~ScanProps();


     ACharacter* Player;
	TArray<UStaticMesh*>MorphableMeshArray;

	TArray<UStaticMeshComponent*>HighlightedMeshArray;

	void CacheData(TArray<UStaticMesh*>PropArray , ACharacter* PlayerCharacter);

	void StartScanning();

	void ResetHighlightedMesh();

private:

	const float TraceRadius = 150.0f;
	FVector StartPoint;
	FVector EndPoint;
	TArray<FHitResult>TraceHitArray;
	FCollisionQueryParams  TraceQuery;
	FCollisionObjectQueryParams ObjectQueryParams = ECollisionChannel::ECC_WorldDynamic;

};
