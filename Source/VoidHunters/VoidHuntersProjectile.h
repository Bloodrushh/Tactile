// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoidHuntersProjectile.generated.h"

UCLASS(config=Game)
class AVoidHuntersProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

public:
	AVoidHuntersProjectile();

	void PreInitializeComponents() override;

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "!VH: Settings")
	float Speed = 100.f;

	void SetShooter(AActor* InShooter);

	UFUNCTION(BlueprintCallable, Category = "!VH: Gameplay")
	AActor* GetShooter() const;

protected:
	UPROPERTY()
	AActor* Shooter = nullptr;

};

