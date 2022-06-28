// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_ProjectileNotify.h"

void UAnim_ProjectileNotify :: Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AMainCharacter* Player = Cast<AMainCharacter>(MeshComp->GetOwner());
	if (Player) {
		Player->SpawnProjectile();
	}
}