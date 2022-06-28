// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Base.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
APickableActor_Base::APickableActor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(30.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");
	RootComponent = CollisionComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingComponent"));

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APickableActor_Base::BeginOverlap);
}

// Called when the game starts or when spawned
void APickableActor_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickableActor_Base::BeginOverlap(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult) {

	AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
	if (Player) {
		PlayerPickedUp(Player);
	}
	UE_LOG(LogTemp, Warning, TEXT("Player not casted"));
}

void APickableActor_Base::PlayerPickedUp(AMainCharacter* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerPickedup"));
	UWorld* world = GetWorld();
	if (world) {
		UGameplayStatics::SpawnSoundAtLocation(world, PickUpSound, GetActorLocation());
		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("World FOund"));
	}
}

