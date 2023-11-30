// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDPlatformHub.generated.h"

class UBoxComponent;
class ACDPlatform;

UENUM(BlueprintType)
enum class ECDPlatformDirection : uint8
{
	None,
	Left,
	Right,
	Up,
	Down,
};

USTRUCT(BlueprintType)
struct FCDPlatfromPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	ECDPlatformDirection PlatformDirection;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACDPlatform> PlatformClass;
};

UCLASS()
class COSMICDESCENT_API ACDPlatformHub : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDPlatformHub();

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	TArray<FCDPlatfromPayload> PlatformPayload;

	UPROPERTY(EditAnywhere)
    int32 PlatformCount = 10;

protected:
	virtual void BeginPlay() override;

	void SpawnPlatform(int32 Index = 0);

	void DeletePlatform(int32 Index = 0);

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FRotator PlatformRotation;
	FVector PlatformLocation;
	TArray<AActor*> PlatformArray;
	ECDPlatformDirection PlatformState = ECDPlatformDirection::None;
	ECDPlatformDirection PlatformDirection = ECDPlatformDirection::None;
};
