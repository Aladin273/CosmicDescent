// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDAICharacter.generated.h"

class UStaticMeshComponent;

UCLASS()
class COSMICDESCENT_API ACDAICharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDAICharacter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector ForceVector = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ForceSpeed = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ForceAcceleration = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float ForceAccelerationStep = 0.00015f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float ForceAccelerationMultiplier = 1.025f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ForceUpdateTime = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StuckMultiplier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StuckTime = 0.2f;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void UpdateForce();

	virtual void StartStuck();
    
	virtual void StopStuck();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FTimerHandle StuckTimer;
	FTimerHandle ForceTimer;

	float LastForceSpeed = 0.f;
	float RawForceAcceleration = 0.f;
};
