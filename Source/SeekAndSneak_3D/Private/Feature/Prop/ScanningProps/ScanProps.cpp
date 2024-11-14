// Fill out your copyright notice in the Description page of Project Settings.


#include "Feature/Prop/ScanningProps/ScanProps.h"
#include "GameFramework/Character.h"
#include "PropPlayer/PropPlayer.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

ScanProps::ScanProps(TArray<UStaticMesh*> PropArray, ACharacter* PlayerCharacter) : MorphableMeshArray(PropArray) , Player(PlayerCharacter)
{
	bMeshhighlighted = false;

	TraceQuery.AddIgnoredActor(PlayerCharacter);
}

ScanProps::~ScanProps()
{
}

void ScanProps::StartScanning()
{
	if (bMeshhighlighted)
	{
		Highlightedmeshcomp->SetRenderCustomDepth(false);
		bMeshhighlighted = false;
	}

	StartPoint =  Player->GetActorLocation();
	EndPoint = StartPoint;

	Player->GetWorld()->SweepSingleByObjectType(TraceHitResult, StartPoint, EndPoint, FQuat::Identity, ObjectQueryParams, FCollisionShape::MakeSphere(TraceRadius),TraceQuery);

	DrawDebugSphere(Player->GetWorld(), EndPoint, TraceRadius, 6, FColor::Blue, false, 1);

	/*for (const FHitResult& HitResult: TraceHitArray)
	{*/
		if (UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(TraceHitResult.GetComponent()))
		{
			if (MorphableMeshArray.Contains(MeshComponent->GetStaticMesh()))
			{
				MeshComponent->SetRenderCustomDepth(true);
				Highlightedmeshcomp = MeshComponent;
				bMeshhighlighted = true;
			}
		}
	//}
}

void ScanProps::ResetHighlightedMesh()
{
	
}
