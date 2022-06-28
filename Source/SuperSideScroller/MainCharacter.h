// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScrollerCharacter.h"
#include "PlayerProjectile.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API AMainCharacter : public ASuperSideScrollerCharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	void SpawnProjectile();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Sprint();
	void StopSprinting();
	void ThrowProjectile();
	

private:
	bool bIsSprinting;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* ThrowMontage;
	UPROPERTY(EditAnywhere)
		TSubclassOf<APlayerProjectile> PlayerProjectile;

};
