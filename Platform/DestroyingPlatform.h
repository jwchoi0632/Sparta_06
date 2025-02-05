// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "Platform/APlatform.h"
#include <vector>
#include "DestroyingPlatform.generated.h"

UENUM(BlueprintType)
enum class ECreateDirection : uint8
{
	PosX = 0,
	PosY,
	//PosZ,
	PosXY,
	PosXZ,
	PosYZ,
	//PosXYZ,
	EEnd
};

UCLASS()
class SPARTAPRJ06_API ADestroyingPlatform : public AAPlatform
{
	GENERATED_BODY()
	
public:	
	ADestroyingPlatform();

	UPROPERTY(EditAnywhere, Category = "DestroySetting")
	float DestroyTime;

	UPROPERTY(EditAnywhere, Category = "DestroySetting")
	int32 PlatformCount;

	UPROPERTY(EditAnywhere, Category = "DestroySetting")
	FVector PlatformScale;

	UPROPERTY(EditAnywhere, Category = "DestroySetting")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = "DestroySetting")
	TSubclassOf<class AActor> Platform;

	UPROPERTY(EditAnywhere, Category = "DestroySetting")
	ECreateDirection CreateDirection;

	UPROPERTY(EditAnywhere, Category = "MoveSetting")
	bool DirectionSign;

	inline void StartAction() override { bIsStart = true; }
	inline void StopAction() override { bIsStart = false; }
	inline EPlatformType GetType() override { return PlatformType; }
	
	inline void SetDestroyTime(float Time) { DestroyTime = Time; }
	inline void SetPlatformCount(int32 Count) { PlatformCount = Count; }
	inline void SetStartLocation(FVector Location) { StartLocation = Location; }
	inline void SetPlatform(TSubclassOf<class AActor> platform) { Platform = platform; }
	inline void SetCreateDirection(ECreateDirection DirectionType) { CreateDirection = DirectionType; }
	inline void SetPlatformScale(FVector Scale) { PlatformScale = Scale; }
	inline void SetDirectionSign(bool Sign) { DirectionSign = Sign; }

	void Action();

protected:
	virtual void BeginPlay() override;

	const float PerSize = 100;
	int32 CreateIndex;
	int32 DestroyIndex;
	std::vector<AActor*> PlatformSet;

	TObjectPtr<class UStaticMeshComponent> PlatformMesh;
	TObjectPtr<class UMaterialInstanceDynamic> PlatformMaterialInstance;

	void InitializePlatformSet();
	void CreatePlatform();
	void DestroyPlatform();
};
