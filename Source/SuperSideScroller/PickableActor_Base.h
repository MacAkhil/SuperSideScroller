// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainCharacter.h"
#include "PickableActor_Base.generated.h"

UCLASS()
class SUPERSIDESCROLLER_API APickableActor_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableActor_Base();

	virtual void PlayerPickedUp(class AMainCharacter* Actor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleDefaultsOnly, Category = Pickable)
		class USphereComponent* CollisionComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Pickable)
		class UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Pickable)
		class URotatingMovementComponent* RotatingComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound)
		class USoundBase* PickUpSound;

private:
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

};
