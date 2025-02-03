// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform/TrapPlatform.h"

ATrapPlatform::ATrapPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	bIsTrigger = false;
	CurrentDirection = FVector(1, 0, 0);
	StartLocation = GetActorLocation();

	PlatformType = EPlatformType::Trap;
	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrapPlatform"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlatformMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resources/Shapes/Shape_Cube.Shape_Cube'"));

	if (PlatformMesh.Succeeded())
	{
		Platform->SetStaticMesh(PlatformMesh.Object);
	}

	Platform->SetRelativeLocation(FVector::Zero());
	Platform->SetWorldScale3D(FVector::One());
	Platform->SetCollisionResponseToAllChannels(ECR_Block);
	RootComponent = Platform;
	//SetRootComponent(Platform);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->InitBoxExtent(FVector::One());
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Script/Engine.Material'/Game/Resources/Materials/M_Concrete_Grime.M_Concrete_Grime'"));

	if (Material.Succeeded())
	{
		UMaterialInstanceDynamic* PlatformMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, Platform);
		Platform->SetMaterial(0, PlatformMaterialInstance);
	}
}

void ATrapPlatform::SetTriggerScale(FVector Scale)
{
	BoxComponent->SetBoxExtent(BoxComponent->GetScaledBoxExtent() * 30 + FVector(0,0, 100));
}

void ATrapPlatform::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrapPlatform::OnTrigger);
}

void ATrapPlatform::Tick(float DeltaTime)
{
	if (!bIsStart) return;
	if (!bIsTrigger) return;

	if (FVector::Distance(StartLocation, GetActorLocation()) >= MoveDistance)
	{
		CurrentDirection *= -1;
	}

	AddActorWorldOffset(CurrentDirection * MoveSpeed * DeltaTime);
}

void ATrapPlatform::OnTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsStart) return;
	if (bIsTrigger) return;

	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		//if (OtherActor == TriggerTarget)
		{
			bIsTrigger = true;

			FTimerHandle TimerHandle;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
				{
					SetActorHiddenInGame(true);
					SetActorEnableCollision(false);
					SetActorTickEnabled(false);

					GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
						{
							SetActorHiddenInGame(false);
							SetActorEnableCollision(true);
							SetActorTickEnabled(true);
							bIsTrigger = false;
						}), 3.0f, false);
				}), 2.0f, false);
		}
	}
}
