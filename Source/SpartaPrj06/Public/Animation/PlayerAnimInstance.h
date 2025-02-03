// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPARTAPRJ06_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Direction;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
