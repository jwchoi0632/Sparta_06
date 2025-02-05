// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform/RandomSpawner.h"

// Sets default values
ARandomSpawner::ARandomSpawner()
{

}

void ARandomSpawner::BeginPlay()
{
	Super::BeginPlay();
	StartRandomSpawn();
}

void ARandomSpawner::StartRandomSpawn()
{
	NextLocation = StartLocation;
	InitializeMap();
	StartActionAllPlatform();
}

void ARandomSpawner::InitializeMap()
{
	for (int i = 0; i < CreateCount; i++)
	{
		PlatformSet.push_back(RandomSpawn());
		InitializePlatforms(i);
	}
}

void ARandomSpawner::StartActionAllPlatform()
{
	for (int i = 0; i < PlatformSet.size(); i++)
	{
		PlatformSet[i]->StartAction();
		if (PlatformSet[i]->GetType() == EPlatformType::Destroy) Cast<ADestroyingPlatform>(PlatformSet[i])->Action();
	}
}

/*
void ARandomSpawner::StartActionAtPlatform(int32 index)
{

}
*/

AAPlatform* ARandomSpawner::RandomSpawn()
{
	int32 RandomValue = FMath::RandRange(0, 100);

	if (RandomValue < 40) return GetWorld()->SpawnActor<AStaticPlatform>(StaticPlatform, FVector::Zero(), FRotator::ZeroRotator);
	else if (RandomValue < 70) return GetWorld()->SpawnActor<AMovePlatform>(MovePlatform, FVector::Zero(), FRotator::ZeroRotator);
	else if (RandomValue < 90) return GetWorld()->SpawnActor<ATrapPlatform>(TrapPlatform, FVector::Zero(), FRotator::ZeroRotator);

	return GetWorld()->SpawnActor<ADestroyingPlatform>(DestroyingPlatform, FVector::Zero(), FRotator::ZeroRotator);
}

void ARandomSpawner::InitializePlatforms(int32 index)
{
	float RandScale_X = FMath::RandRange(MinScale.X, MaxScale.X);
	float RandScale_Y = FMath::RandRange(MinScale.Y, MaxScale.Y);
	float RandScale_Z = FMath::RandRange(MinScale.Z, MaxScale.Z);

	float RandPos_X = FMath::RandRange(NextLocation.X, NextLocation.X + CreateDistance.X);
	float RandPos_Y = FMath::RandRange(NextLocation.Y, NextLocation.Y + CreateDistance.Y);
	float RandPos_Z = FMath::RandRange(NextLocation.Z, NextLocation.Z + CreateDistance.Z);

	FVector CurrentLocation = FVector(RandPos_X, RandPos_Y, RandPos_Z);
	FVector ActorScale = FVector(RandScale_X, RandScale_Y, RandScale_Z);

	NextLocation = CurrentLocation + ActorScale * PerSize;

	switch (PlatformSet[index]->GetType()) //타입별 초기화 부분
	{
	case EPlatformType::Static: InitializeStaticPlatform(index, CurrentLocation, ActorScale); break;
	case EPlatformType::Move: InitializeMovePlatform(index, CurrentLocation, ActorScale); break;
	case EPlatformType::Destroy: InitializeDestroyingPlatform(index, CurrentLocation, ActorScale); break;
	case EPlatformType::Trap: InitializeTrapPlatform(index, CurrentLocation, ActorScale); break;
	}
}

void ARandomSpawner::InitializeStaticPlatform(int32 index, FVector startPos, FVector scale)
{
	AStaticPlatform* platform = Cast<AStaticPlatform>(PlatformSet[index]);

	platform->SetActorLocation(startPos);
	platform->SetActorScale3D(scale);
	platform->SetBoxScale(scale);
}

void ARandomSpawner::InitializeMovePlatform(int32 index, FVector startPos, FVector scale)
{
	AMovePlatform* platform = Cast<AMovePlatform>(PlatformSet[index]);

	EMoveType type = EMoveType::MoveAndRotate;
	int32 RandomValue = FMath::RandRange(0, 100);

	if (RandomValue < 60) type = EMoveType::MoveOnly;
	else if (RandomValue < 90) type = EMoveType::RotateOnly;

	bool DirectionSign = (bool)FMath::RandRange(0, 1);
	platform->SetMoveType(type);
	platform->SetStartLocation(startPos);
	platform->SetActorScale3D(scale);
	platform->SetDirectionSign(DirectionSign);
	platform->SetBoxScale(scale);

	if (type != EMoveType::RotateOnly) //only move || mvoe and rotate
	{
		EDirectionType DirectionType = (EDirectionType)FMath::RandRange((int32)EDirectionType::X, (int32)EDirectionType::EEnd - 1);
		int32 Distance = FMath::RandRange(300, 600);
		platform->SetMoveDirection(DirectionType);
		platform->SetMoveDistance(Distance);
		platform->SetMoveSpeed(FMath::RandRange(200, 400));
		platform->SetIsReturn(true); // 임시

		int32 Sign = 1;

		if (!DirectionSign) Sign = -1;

		switch (DirectionType)
		{
		case EDirectionType::X: NextLocation += FVector(Distance, 0, 0) * Sign; break;
		case EDirectionType::Y: NextLocation += FVector(0, Distance, 0) * Sign; break;
		case EDirectionType::Z: NextLocation += FVector(0, 0, Distance) * Sign; break;
		case EDirectionType::XY: NextLocation += FVector(Distance, Distance, 0) * Sign; break;
		case EDirectionType::XZ: NextLocation += FVector(Distance, 0, Distance) * Sign; break;
		case EDirectionType::YZ: NextLocation += FVector(0, Distance, Distance) * Sign; break;
		//case EDirectionType::XYZ: NextLocation += FVector(Distance, Distance, Distance); break;
		}
	}

	if (type != EMoveType::MoveOnly) //only rotate || move and rotate
	{
		platform->SetRotateDirection((EDirectionType)FMath::RandRange((int32)EDirectionType::X, (int32)EDirectionType::EEnd - 1));
		platform->SetRotateSpeed(FMath::RandRange(30, 90));
		NextLocation += FVector::One() * PerSize;
	}
}

void ARandomSpawner::InitializeDestroyingPlatform(int32 index, FVector startPos, FVector scale)
{
	ADestroyingPlatform* platform = Cast<ADestroyingPlatform>(PlatformSet[index]);
	
	int32 PlatformCount = FMath::RandRange(5, 15);
	bool DirectionSign = (bool)FMath::RandRange(0, 1);
	ECreateDirection CreateDirection = (ECreateDirection)FMath::RandRange((int32)ECreateDirection::PosX, (int32)ECreateDirection::EEnd - 1);

	platform->SetPlatform(DestroyingActor);
	platform->SetDestroyTime(FMath::RandRange(1.0f, 1.5f));
	platform->SetPlatformCount(PlatformCount);
	platform->SetStartLocation(startPos);
	platform->SetDirectionSign((bool)DirectionSign);
	platform->SetCreateDirection(CreateDirection);
	platform->SetPlatformScale(scale);

	if (!DirectionSign) PlatformCount *= -1;

	switch (CreateDirection)
	{
	case ECreateDirection::PosX: NextLocation += scale * PerSize * FVector(PlatformCount - 1, 0, 0); break;
	case ECreateDirection::PosY: NextLocation += scale * PerSize * FVector(0, PlatformCount - 1, 0); break;
	//case ECreateDirection::PosZ: NextLocation += scale * PerSize * FVector(0, 0, PlatformCount - 1); break;
	case ECreateDirection::PosXY: NextLocation += scale * PerSize * FVector(PlatformCount - 1, PlatformCount - 1, 0); break;
	case ECreateDirection::PosXZ: NextLocation += scale * PerSize * FVector(PlatformCount - 1, 0, PlatformCount - 1); break;
	case ECreateDirection::PosYZ: NextLocation += scale * PerSize * FVector(0, PlatformCount - 1, PlatformCount - 1); break;
	//case ECreateDirection::PosXYZ: NextLocation += scale * PerSize * FVector(PlatformCount - 1, PlatformCount - 1, PlatformCount - 1); break;
	}
}

void ARandomSpawner::InitializeTrapPlatform(int32 index, FVector startPos, FVector scale)
{
	ATrapPlatform* platform = Cast<ATrapPlatform>(PlatformSet[index]);

	platform->SetStartLocation(startPos);
	platform->SetTriggerScale(scale);
	platform->SetActorLocation(startPos);
	platform->SetActorScale3D(scale);
	//platform->SetTarget(GetWorld()->Pawn);
}

