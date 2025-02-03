// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Platform/DestroyingPlatform.h"
#include "Platform/MovePlatform.h"
#include "Platform/StaticPlatform.h"
#include "Platform/DestroyingActor.h"
#include "Platform/TrapPlatform.h"
#include "RandomSpawner.generated.h"

UCLASS()
class SPARTAPRJ06_API ARandomSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ARandomSpawner();

	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	TSubclassOf<class ADestroyingPlatform> DestroyingPlatform;

	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	TSubclassOf<class AMovePlatform> MovePlatform;

	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	TSubclassOf<class AStaticPlatform> StaticPlatform;

	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	TSubclassOf<class ADestroyingActor> DestroyingActor;

	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	TSubclassOf<class ATrapPlatform> TrapPlatform;

	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	FVector CreateDistance;

	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	FVector MinScale;

	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	FVector MaxScale;

	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	int32 CreateCount;

	void InitializeMap();
	void StartActionAllPlatform();
	//void StartActionAtPlatform(int32 index);
	void StartRandomSpawn();

protected:
	const float PerSize = 100.0f;

	FVector NextLocation;
	std::vector<AAPlatform*> PlatformSet;

	virtual void BeginPlay() override;

	AAPlatform* RandomSpawn();
	
	void InitializePlatforms(int32 index);
	void InitializeStaticPlatform(int32 index, FVector startPos, FVector scale);
	void InitializeMovePlatform(int32 index, FVector startPos, FVector scale);
	void InitializeDestroyingPlatform(int32 index, FVector startPos, FVector scale);
	void InitializeTrapPlatform(int32 index, FVector startPos, FVector scale);
};
