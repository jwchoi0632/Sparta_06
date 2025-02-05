// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Platform/APlatform.h"
#include "Components/BoxComponent.h"
#include "TrapPlatform.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPRJ06_API ATrapPlatform : public AAPlatform
{
	GENERATED_BODY()
	
public:
	ATrapPlatform();

	virtual inline void StartAction() { bIsStart = true; }
	virtual inline void StopAction() { bIsStart = false; }
	inline void SetStartLocation(FVector Location) { StartLocation = Location; }
	inline void SetTarget(AActor* Target) { TriggerTarget = Target; }
	void SetTriggerScale(FVector Scale);

protected:
	const float MoveDistance = 20;
	const float MoveSpeed = 1000;
	bool bIsTrigger;
	FVector StartLocation;
	FVector CurrentDirection;
	AActor* TriggerTarget;

	TObjectPtr<class UStaticMeshComponent> Platform;
	TObjectPtr<class UBoxComponent> BoxComponent;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
