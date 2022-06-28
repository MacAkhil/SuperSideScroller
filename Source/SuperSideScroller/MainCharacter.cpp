// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "PlayerProjectile.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Animation/AnimInstance.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMainCharacter::AMainCharacter()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::StopSprinting);
	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &AMainCharacter::ThrowProjectile);
	
}

void AMainCharacter::Sprint()
{
	if (!bIsSprinting) {
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	}
}

void AMainCharacter::StopSprinting()
{
	if (bIsSprinting) {
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}

void AMainCharacter::ThrowProjectile()
{
	if (ThrowMontage) {
		bool bIsMontagePlaying = GetMesh()->GetAnimInstance()->Montage_IsPlaying(ThrowMontage);
		if (!bIsMontagePlaying) {
			GetMesh()->GetAnimInstance()->Montage_Play(ThrowMontage, 2.0f);
		}
	}
}

void AMainCharacter::SpawnProjectile()
{
	if (PlayerProjectile) {
		UWorld* world = GetWorld();
		if (world) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			FVector SpawnLocation = GetMesh()->GetSocketLocation(TEXT("ProjectileSocket"));
			FRotator SpawnRotation = GetActorForwardVector().Rotation();

			APlayerProjectile* Projectile = world->SpawnActor<APlayerProjectile>
				(PlayerProjectile, SpawnLocation, SpawnRotation, SpawnParams);

			if (Projectile) {
				//Projectile->CollisionComponent->MoveIgnoreActors.Add(SpawnParams.Owner);
			}
		}
	}
}
