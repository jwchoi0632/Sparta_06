// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform/StaticPlatform.h"

// Sets default values
AStaticPlatform::AStaticPlatform()
{
	PlatformType = EPlatformType::Static;
	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticPlatform"));

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

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Script/Engine.Material'/Game/Resources/Materials/M_Brick_Hewn_Stone.M_Brick_Hewn_Stone'"));

	if (Material.Succeeded())
	{
		UMaterialInstanceDynamic* PlatformMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, Platform);
		Platform->SetMaterial(0, PlatformMaterialInstance);
	}
}

// Called when the game starts or when spawned
void AStaticPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}
