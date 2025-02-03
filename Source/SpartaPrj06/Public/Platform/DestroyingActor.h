// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Platform/APlatform.h"
#include "Components/BoxComponent.h"
#include "DestroyingActor.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPRJ06_API ADestroyingActor : public AAPlatform
{
	GENERATED_BODY()
	
public:
	ADestroyingActor();

	inline void StartAction() override { bIsStart = true; }
	inline void StopAction() override { bIsStart = false; }
	inline EPlatformType GetType() override { return PlatformType; }
	inline void SetBoxScale(FVector Scale) { BoxComponent->SetBoxExtent(Scale); }

protected:
	virtual void BeginPlay() override;

	TObjectPtr<class UStaticMeshComponent> Platform;
	TObjectPtr<class UBoxComponent> BoxComponent;
};
