// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SEEKANDSNEAK_3D_API ScanProps
{
public:
	ScanProps(TArray<UStaticMesh*> PropArray, ACharacter* PlayerCharacter);
	~ScanProps();

	TArray<UStaticMesh*>MorphableMeshArray;
     ACharacter* Player;
	

	bool bMeshhighlighted;
	UStaticMeshComponent* Highlightedmeshcomp;

	void StartScanning();

private:


	void ResetHighlightedMesh();

	const float TraceRadius = 150.0f;
	FVector StartPoint;
	FVector EndPoint;
	FHitResult TraceHitResult;
	FCollisionQueryParams  TraceQuery;
	FCollisionObjectQueryParams ObjectQueryParams = ECollisionChannel::ECC_WorldDynamic;

};
