// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProjectile.h"
#include "EnemyBase.h"
#include "Components/AudioComponent.h"
#include "Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerProjectile::APlayerProjectile()
{
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("BlockAll");
	CollisionComponent->OnComponentHit.AddDynamic(this, &APlayerProjectile::OnHit);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = CollisionComponent;
	MovementComponent->InitialSpeed = 800.0f;
	MovementComponent->MaxSpeed = 800.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	InitialLifeSpan = 3.0f;

	ProjectileAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ProjectileAudio"));
	ProjectileAudio->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	ProjectileVFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileVFX"));
	ProjectileVFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
}

void APlayerProjectile::ExploadProjectile()
{
	Destroy();
	UWorld* world = GetWorld();
	if (world) {
		UGameplayStatics::SpawnSoundAtLocation(world, DestroySound, GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(world, DestroyVFX, GetActorTransform());
	}
}

void APlayerProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AEnemyBase* Enemy;
	Enemy = Cast<AEnemyBase>(OtherActor);
	if (Enemy) {
		Enemy->DestroyEnemy();
	}
	ExploadProjectile();
}
