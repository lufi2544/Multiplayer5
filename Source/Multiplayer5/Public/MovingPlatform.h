// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

USTRUCT(BlueprintType)
struct FMySparseClassData
{
	GENERATED_BODY();


	FMySparseClassData()
		:fSpeed(1.f)


	{}

	//The Platform Speed
	UPROPERTY(EditDefaultsOnly, meta = (GetByRef)  , meta =(DisplayName = "Speed") ,meta = (ClampMin = -3) , meta = (ClampMax = 3) , Category = "PlatformBase")
		float fSpeed;

};

/**
 * 
 */
UCLASS(BlueprintType, SparseClassDataTypes = MySparseClassData)
class MULTIPLAYER5_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:


	//GETTERS
	UFUNCTION(BlueprintPure , Category = "PlatformBase")
	float GetPlatformSpeed();

	//FUNCTIONS

	//DELEGATES


	AMovingPlatform();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;


#if WITH_EDITOR



public:

	virtual void MoveDataToSparseClassDataStruct() const override;




	
#endif
	

#if WITH_EDITORONLY_DATA

private:

	//The Platform Speed
	UPROPERTY()
		float fSpeed_DEPRECATED;

#endif






};
