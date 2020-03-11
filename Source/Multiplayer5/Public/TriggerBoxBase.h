// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBoxBase.generated.h"

//FWD Declarations

class AMovingPlatform;

/**
 * 
 */
UCLASS()
class MULTIPLAYER5_API ATriggerBoxBase : public ATriggerBox
{
	GENERATED_BODY()


public:
		ATriggerBoxBase();

		UPROPERTY(EditAnyWhere , BlueprintReadWrite, Category = "TriggerBoxBase")
			AMovingPlatform* PlatformOnButton;

	
};
