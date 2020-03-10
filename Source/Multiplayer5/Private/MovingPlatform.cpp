// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Components/StaticMeshComponent.h"


AMovingPlatform::AMovingPlatform() 
{

	PrimaryActorTick.bCanEverTick = true;

	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);

	

}

void AMovingPlatform::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (HasAuthority())
	{

		FVector vCurrentLocation = GetActorLocation();
		float fNewLocationX = vCurrentLocation.X + 1 * GetfSpeed();
		SetActorLocation(FVector(fNewLocationX, vCurrentLocation.Y, vCurrentLocation.Z));

		

	}
}

void AMovingPlatform::BeginPlay()
{

	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}



}

//GETTERS

float AMovingPlatform::GetPlatformSpeed()
{
	return GetfSpeed();
}

//SPARSECLASSDATA

#if WITH_EDITOR

	void AMovingPlatform::MoveDataToSparseClassDataStruct() const 
	{
		UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass());
		if (BPClass == nullptr || BPClass->bIsSparseClassDataSerializable == true)
		{
			return;
		}

		Super::MoveDataToSparseClassDataStruct();
	
	
	
	

#if WITH_EDITORONLY_DATA
	// Unreal Header Tool (UHT) will create GetMySparseClassData automatically.
	FMySparseClassData* SparseClass = GetMySparseClassData();

	// Modify these lines to include all Sparse Class Data properties.
	SparseClass->fSpeed = fSpeed_DEPRECATED;
	

#endif
}

#endif // WITH_EDITOR


