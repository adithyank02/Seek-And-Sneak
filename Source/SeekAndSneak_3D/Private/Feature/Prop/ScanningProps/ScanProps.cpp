// Fill out your copyright notice in the Description page of Project Settings.


#include "Feature/Prop/ScanningProps/ScanProps.h"
#include "GameFramework/Character.h"
#include "PropPlayer/PropPlayer.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

ScanProps::ScanProps()
{

}

ScanProps::~ScanProps()
{
}

void ScanProps::CacheData(TArray<UStaticMesh*> PropArray, ACharacter* PlayerCharacter)
{
	MorphableMeshArray = PropArray;
	Player = PlayerCharacter;

	TraceQuery.AddIgnoredActor(PlayerCharacter);
}
void ScanProps::StartScanning()
{
	if (!HighlightedMeshSet.IsEmpty())
	{
		ResetHighlightedMesh();
	}

	StartPoint =  Player->GetActorLocation();
	EndPoint = StartPoint;

	Player->GetWorld()->SweepMultiByObjectType(TraceHitArray, StartPoint, EndPoint, FQuat::Identity, ObjectQueryParams, FCollisionShape::MakeSphere(TraceRadius),TraceQuery);

	DrawDebugSphere(Player->GetWorld(), EndPoint, TraceRadius, 6, FColor::Blue, false, 1);

	for (const FHitResult& HitResult: TraceHitArray)
	{
		if (UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(HitResult.GetComponent()))
		{
			if (MorphableMeshArray.Contains(MeshComponent->GetStaticMesh()))
			{
				MeshComponent->SetRenderCustomDepth(true);
				HighlightedMeshSet.Add(MeshComponent);
			}
		}
	}
}

void ScanProps::ResetHighlightedMesh()
{
	for (auto Mesh : HighlightedMeshSet)
	{
		Mesh->SetRenderCustomDepth(false);
		HighlightedMeshSet.Remove(Mesh);
	}
}
