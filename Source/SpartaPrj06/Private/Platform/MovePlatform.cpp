// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform/MovePlatform.h"


// Sets default values
AMovePlatform::AMovePlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	PlatformType = EPlatformType::Move;
	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MovePlatForm"));;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlatformMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resources/Shapes/Shape_Cube.Shape_Cube'"));

	if (PlatformMesh.Succeeded())
	{
		Platform->SetStaticMesh(PlatformMesh.Object);
	}
	
	Platform->SetRelativeLocation(FVector::Zero());
	Platform->SetWorldScale3D(FVector::One());
	Platform->SetCollisionResponseToAllChannels(ECR_Block);
	
	SetRootComponent(Platform);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->InitBoxExtent(FVector::One());
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Block);
	BoxComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Script/Engine.Material'/Game/Resources/Materials/M_Ceramic_Tile_Checker.M_Ceramic_Tile_Checker'"));

	if (Material.Succeeded())
	{
		UMaterialInstanceDynamic* PlatformMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, Platform);
		Platform->SetMaterial(0, PlatformMaterialInstance);
	}

	bIsStart = false;
}

void AMovePlatform::Move(float DeltaTime)
{
	if (FVector::Distance(StartLocation * CurrentDirection, GetActorLocation() * CurrentDirection) >= MoveDistance)
	{
		if (!bIsReturn) return;
		CurrentDirection *= -1;
	}

	AddActorWorldOffset(CurrentDirection * MoveSpeed * DeltaTime);
}

void AMovePlatform::Rotate(float DeltaTime)
{
	AddActorWorldRotation(CurrentRotate * RotateSpeed * DeltaTime);
}

void AMovePlatform::SetMoveDirection(EDirectionType Direction)
{
	switch (Direction)
	{
	case EDirectionType::X: CurrentDirection = FVector(1, 0, 0); break;
	case EDirectionType::Y: CurrentDirection = FVector(0, 1, 0); break;
	case EDirectionType::Z: CurrentDirection = FVector(0, 0, 1); break;
	case EDirectionType::XY: CurrentDirection = FVector(1, 1, 0); break;
	case EDirectionType::XZ: CurrentDirection = FVector(1, 0, 1); break;
	case EDirectionType::YZ: CurrentDirection = FVector(0, 1, 1); break;
	//case EDirectionType::XYZ: CurrentDirection = FVector(1, 1, 1); break;
	}

	if (!DirectionSign) CurrentDirection *= -1;
}

void AMovePlatform::SetRotateDirection(EDirectionType Direction)
{
	switch (Direction)
	{
	case EDirectionType::X: CurrentRotate = FRotator(1, 0, 0); break;
	case EDirectionType::Y: CurrentRotate = FRotator(0, 1, 0); break;
	case EDirectionType::Z: CurrentRotate = FRotator(0, 0, 1); break;
	case EDirectionType::XY: CurrentRotate = FRotator(1, 1, 0); break;
	case EDirectionType::XZ: CurrentRotate = FRotator(1, 0, 1); break;
	case EDirectionType::YZ: CurrentRotate = FRotator(0, 1, 1); break;
	//case EDirectionType::XYZ: CurrentRotate = FRotator(1, 1, 1); break;
	}

	if (!DirectionSign) CurrentRotate *= -1;
}

void AMovePlatform::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(StartLocation);
	SetActorScale3D(PlatformScale);
}

void AMovePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsStart) return;

	switch (MoveType)
	{
	case EMoveType::MoveOnly:
		Move(DeltaTime);
		break;

	case EMoveType::RotateOnly:
		Rotate(DeltaTime);
		break;

	case EMoveType::MoveAndRotate:
		Move(DeltaTime);
		Rotate(DeltaTime);
		break;
	}
	
}

