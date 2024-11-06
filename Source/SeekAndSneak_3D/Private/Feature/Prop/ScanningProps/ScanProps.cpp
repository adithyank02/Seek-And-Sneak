// Fill out your copyright notice in the Description page of Project Settings.


#include "Feature/Prop/ScanningProps/ScanProps.h"
#include "GameFramework/Character.h"
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
	UKismetSystemLibrary::PrintString(PlayerCharacter->GetWorld(), TEXT("Mesh Array Got Stored"));

	MorphableMeshArray = PropArray;
	Player = PlayerCharacter;

	TraceQuery.AddIgnoredActor(PlayerCharacter);
}
void ScanProps::StartScanning()
{
	if (!HighlightedMeshArray.IsEmpty())
	{
		ResetHighlightedMesh();
	}

	StartPoint =  Player->GetActorLocation();
	EndPoint = StartPoint;

	Player->GetWorld()->SweepMultiByObjectType(TraceHitArray, StartPoint, EndPoint, FQuat::Identity, ObjectQueryParams, FCollisionShape::MakeSphere(TraceRadius),TraceQuery);

	DrawDebugSphere(Player->GetWorld(), EndPoint, TraceRadius, 6, FColor::Blue, false, 1);

	for (const FHitResult& HitResult: TraceHitArray)
	{
		UKismetSystemLibrary::PrintString(Player->GetWorld(), HitResult.GetActor()->GetActorLabel(), true, true, FLinearColor::Yellow);
		if (UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(HitResult.GetComponent()))
		{
			if(MorphableMeshArray.Contains(MeshComponent->GetStaticMesh()))
			{
				MeshComponent->bRenderCustomDepth = true;
				MeshComponent->SetCustomDepthStencilValue(1);

				UKismetSystemLibrary::PrintString(Player->GetWorld(), TEXT("Render Custom dept to True"),true,true,FLinearColor::Red);

				HighlightedMeshArray.AddUnique(MeshComponent);
			}
			else
			{
				UKismetSystemLibrary::PrintString(Player->GetWorld(), TEXT("Morph mesh array not contain mesh"), true, true, FLinearColor::Blue);
			}
		}
		else
		{
			UKismetSystemLibrary::PrintString(Player->GetWorld(), TEXT("Casted Falide on staticmeshcomponent"), true, true, FLinearColor::White);
		}
	}


}

void ScanProps::ResetHighlightedMesh()
{
	for (auto Mesh : HighlightedMeshArray)
	{
		Mesh->bRenderCustomDepth = false;
	}
}
