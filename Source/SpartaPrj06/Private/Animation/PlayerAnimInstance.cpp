// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerAnimInstance.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;

	FVector Velocity(Pawn->GetVelocity().X, Pawn->GetVelocity().Y, 0);

	Speed = Velocity.Size();//Pawn->GetVelocity().Size();
	Direction = CalculateDirection(Velocity, Pawn->GetActorRotation());//Pawn->GetVelocity(), Pawn->GetActorRotation());
}
