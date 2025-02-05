// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "Platform/APlatform.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include "MovePlatform.generated.h"

UENUM(BlueprintType)
enum class EMoveType : uint8
{
	MoveOnly = 0,
	RotateOnly,
	MoveAndRotate,
	EEnd
};

UENUM(BlueprintType)
enum class EDirectionType : uint8
{
	X = 0,
	Y,
	Z,
	XY,
	XZ,
	YZ,
	//XYZ,
	EEnd
};

UCLASS()
class SPARTAPRJ06_API AMovePlatform : public AAPlatform
{
	GENERATED_BODY()
	
public:	
	AMovePlatform();

	UPROPERTY(EditAnywhere, Category = "MoveSetting")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "MoveSetting")
	float RotateSpeed;

	UPROPERTY(EditAnywhere, Category = "MoveSetting")
	float MoveDistance;

	UPROPERTY(EditAnywhere, Category = "MoveSetting")
	bool bIsReturn;

	UPROPERTY(EditAnywhere, Category = "MoveSetting")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = "MoveSetting")
	FVector PlatformScale;

	UPROPERTY(EditAnywhere, Category = "MoveSetting")
	EMoveType MoveType;

	UPROPERTY(EditAnywhere, Category = "MoveSetting")
	EDirectionType MoveDirection;

	UPROPERTY(EditAnywhere, Category = "MoveSetting")
	EDirectionType RotateDirection;

	UPROPERTY(EditAnywhere, Category = "MoveSetting")
	bool DirectionSign;

	inline void StartAction() override { bIsStart = true; }
	inline void StopAction() override { bIsStart = false; }
	inline EPlatformType GetType() override { return PlatformType; }
	inline void SetMoveType(EMoveType Type) { MoveType = Type; }
	void SetMoveDistance(float Distance);
	inline void SetMoveSpeed(float Speed) { MoveSpeed = Speed; }
	inline void SetRotateSpeed(float Speed) { RotateSpeed = Speed; }
	inline void SetIsReturn(bool IsReturn) { bIsReturn = IsReturn; }
	inline void SetDirectionSign(bool Sign) { DirectionSign = Sign; }
	void SetStartLocation(FVector Location) { StartLocation = Location; SetActorLocation(StartLocation); }
	inline void SetBoxScale(FVector Scale) { BoxComponent->SetBoxExtent(Scale); }

	void SetMoveDirection(EDirectionType Direction);
	void SetRotateDirection(EDirectionType Direction);

protected:
	TObjectPtr<class UStaticMeshComponent> Platform;
	TObjectPtr<class UBoxComponent> BoxComponent;

	FVector CurrentDirection;
	FVector TargetLocation;
	FRotator CurrentRotate;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Move(float DeltaTime);
	void Rotate(float DeltaTime);
};
