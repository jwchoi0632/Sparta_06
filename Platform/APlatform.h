// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "APlatform.generated.h"

UENUM(BlueprintType)
enum class EPlatformType : uint8
{
	Static = 0,
	Move,
	Destroy,
	Trap,
	EEnd
};

UCLASS(Abstract)
class SPARTAPRJ06_API AAPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AAPlatform();

	UPROPERTY(EditAnywhere, Category = "PlatformStert")
	bool bIsStart;

	virtual inline EPlatformType GetType() { return PlatformType; }
	virtual inline void StartAction() PURE_VIRTUAL(AAPlatform::StartAction, ;);
	virtual inline void StopAction() PURE_VIRTUAL(AAPlatform::StopAction, ;);
	//virtual void InitializePlatform(FVector Scale) PURE_VIRTUAL(AAPlatform, ;);

protected:
	EPlatformType PlatformType;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
