// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform/DestroyingPlatform.h"
#include "Platform/DestroyingActor.h"

ADestroyingPlatform::ADestroyingPlatform()
{
	bIsStart = false;
	PlatformType = EPlatformType::Destroy;
	CreateIndex = 0;
	DestroyIndex = 0;
}

void ADestroyingPlatform::InitializePlatformSet()
{
	for (int i = 0; i < PlatformCount; i++)
	{
		FVector CreateLocation = StartLocation;
		float NextPos = i * PerSize;
		if (!DirectionSign) NextPos *= -1;

		switch (CreateDirection)
		{
		case ECreateDirection::PosX: CreateLocation += FVector(PlatformScale.X * NextPos, 0, 0); break;
		case ECreateDirection::PosY: CreateLocation += FVector(0, PlatformScale.Y * NextPos, 0); break;
			//case ECreateDirection::PosZ: CreateLocation += FVector(0, 0, PlatformScale.Z * NextPos); break;
		case ECreateDirection::PosXY: CreateLocation += FVector(PlatformScale.X * NextPos, PlatformScale.Y * NextPos, 0); break;
		case ECreateDirection::PosXZ: CreateLocation += FVector(PlatformScale.X * NextPos, 0, PlatformScale.Z * NextPos); break;
		case ECreateDirection::PosYZ: CreateLocation += FVector(0, PlatformScale.Y * NextPos, PlatformScale.Z * NextPos); break;
			//case ECreateDirection::PosXYZ: CreateLocation += FVector(PlatformScale.X * NextPos, PlatformScale.Y * NextPos, PlatformScale.Z * NextPos); break;
		}

		PlatformSet.push_back(GetWorld()->SpawnActor<AActor>(Platform, CreateLocation, FRotator::ZeroRotator));
		PlatformSet[i]->SetActorScale3D(PlatformScale);
		Cast<ADestroyingActor>(PlatformSet[i])->SetBoxScale(PlatformScale);

		PlatformSet[i]->SetActorHiddenInGame(true);
		PlatformSet[i]->SetActorEnableCollision(false);
		PlatformSet[i]->SetActorTickEnabled(false);
	}
}

void ADestroyingPlatform::CreatePlatform()
{
	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			PlatformSet[CreateIndex]->SetActorHiddenInGame(false);
			PlatformSet[CreateIndex]->SetActorEnableCollision(true);
			PlatformSet[CreateIndex]->SetActorTickEnabled(true);

			CreateIndex++;
			if (CreateIndex == PlatformCount - 1) CreateIndex = 0;

		}), DestroyTime, true);
}

void ADestroyingPlatform::DestroyPlatform()
{
	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			PlatformSet[DestroyIndex]->SetActorHiddenInGame(true);
			PlatformSet[DestroyIndex]->SetActorEnableCollision(false);
			PlatformSet[DestroyIndex]->SetActorTickEnabled(false);

			DestroyIndex++;
			if (DestroyIndex == PlatformCount - 1) DestroyIndex = 0;
		}), DestroyTime, true);
}

void ADestroyingPlatform::Action()
{
	if (!bIsStart) return;

	InitializePlatformSet();
	CreatePlatform();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			DestroyPlatform();
		}), DestroyTime * (PlatformCount / 2), false);
}

void ADestroyingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	Action();
}

