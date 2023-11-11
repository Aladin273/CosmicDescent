// Fill out your copyright notice in the Description page of Project Settings.


#include "CDPlatformHub.h"

#include "../Player/CDPaperZDCharacter.h"

// Sets default values
ACDPlatformHub::ACDPlatformHub()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ACDPlatformHub::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACDPlatformHub::OnOverlap);

	Rotation = GetActorRotation();
	Location = GetActorLocation();

	for (int32 Index = 0; Index < Count; ++Index)
		SpawnPlatform();
}

void ACDPlatformHub::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACDPaperZDCharacter>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, "Overlap Box");

		SpawnPlatform();

		if (PlatformArray.Num() > Count)
			DeletePlatform();
	}
}

void ACDPlatformHub::SpawnPlatform()
{
	if (PrevIndex == 0)
	{
		if (PrevRight == true)
		{
			Random = 1;
			PrevRight = true;
		}
		else if (PrevRight == false)
		{
			Random = 2;
			PrevRight = false;
		}
	}
	else if (PrevIndex == 1)
	{
		Random = FMath::RandBool() ? 0 : 2;
		PrevRight = false;
	}
	else if (PrevIndex == 2)
	{
		Random = FMath::RandBool() ? 0 : 1;
		PrevRight = true;
	}

	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(PlatformPayload[Random], Location, Rotation);
	PlatformArray.Add(SpawnedActor);

	FVector Origin;
	FVector BoxExtent;
	SpawnedActor->GetActorBounds(false, Origin, BoxExtent);

	PrevIndex = Random;
	Location.Z -= BoxExtent.Z * 2;

	BoxComponent->SetBoxExtent(BoxExtent * 2);
	BoxComponent->SetWorldLocation(PlatformArray[PlatformArray.Num() - 1]->GetActorLocation());

	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, "Spawned Platform");
}

void ACDPlatformHub::DeletePlatform()
{
	PlatformArray[0]->Destroy();
	PlatformArray.RemoveAt(0);

	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, "Destroyed Platform");
}

// Called every frame
void ACDPlatformHub::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

