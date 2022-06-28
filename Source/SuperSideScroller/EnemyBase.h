// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScrollerCharacter.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API AEnemyBase : public ASuperSideScrollerCharacter
{
	GENERATED_BODY()

public:

	void DestroyEnemy();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USoundBase* ExplosionSoundCue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UParticleSystem* DeathEffect;

};
