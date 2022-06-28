// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void AEnemyBase::DestroyEnemy() {
	Destroy();
	UWorld* world = GetWorld();
	if (world) {
		if (DeathEffect) {
			UGameplayStatics::SpawnEmitterAtLocation(world, DeathEffect, GetActorTransform());
		}
		if (ExplosionSoundCue) {
			UGameplayStatics::SpawnSoundAtLocation(world, ExplosionSoundCue, GetActorLocation());
		}
	}
}

