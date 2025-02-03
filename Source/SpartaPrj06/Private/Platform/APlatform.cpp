// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform/APlatform.h"

AAPlatform::AAPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AAPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}