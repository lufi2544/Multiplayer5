// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

//FWD Delcarations

class ATargetPointBase;

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

	//PROPERTIES


	//Targets that the platform will move between
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "PlatformBase")
		TArray<ATargetPointBase*>TargetsToReach;

	// If true The Platform wll move between the given Targets with a random movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformBase")
		bool RandomMovementToTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformBase")
		bool CanMove;



	//GETTERS
	UFUNCTION(BlueprintPure , Category = "PlatformBase")
	float GetPlatformSpeed();





	//FUNCTIONS



	bool PlatformGo(ATargetPointBase* TargetPoint);

	bool PlatformMoveToTatgets(TArray<ATargetPointBase*> Targets, bool bHasRandomMovement);








	//VARIABLES


	bool bIsReaching = false;

	int32 ArrayCounter = 0;

	ATargetPointBase* PlatformReaching;
	ATargetPointBase* LastPlatformReached;
	


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
