// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoidHuntersCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AVoidHuntersCharacter : public ACharacter {
	GENERATED_UCLASS_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	AVoidHuntersCharacter();

	void Destroyed() override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AVoidHuntersProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

protected:
	virtual void BeginPlay();

	UFUNCTION(Server, Reliable, WithValidation)
	void TriggerFire();

	UFUNCTION()
	void LaunchFire();

	UFUNCTION(Server, Reliable, WithValidation)
	void TriggerScan();

	UFUNCTION(Client, Reliable, Category = Gameplay)
	void LaunchScan();

	UFUNCTION(BlueprintImplementableEvent, Category = Gameplay)
	void OnScan();

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = Gameplay)
	void SetDetected();

	UFUNCTION()
	void ClearDetected();

	UFUNCTION(NetMulticast, Reliable)
	void UpdateDetected(bool bNewDetected);

	UPROPERTY(BlueprintReadOnly, Category = Gameplay)
	bool bIsDetected = false;

	FTimerHandle DetectionTimer;

	UFUNCTION(BlueprintImplementableEvent, Category = Gameplay)
	void OnDetectionUpdate();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "!VH: Settings")
	float DetectionTime = 5.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "!VH: Settings")
	float FireCooldown = 2.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "!VH: Settings")
	float ScanCooldown = 2.f;

	float LastFireTime = 0.f;
	float LastScanTime = 0.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "!VH: Settings")
	float Health = 4.f;

	UPROPERTY(ReplicatedUsing=OnHealthUpdated, BlueprintReadWrite, Category = "!VH: Character")
	float CurrentHealth;

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthUpdated();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "!VH: Settings")
	float Damage = 1.f;

};

