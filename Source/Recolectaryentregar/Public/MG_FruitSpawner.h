#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MG_Collectable.h"
#include "MG_FruitSpawner.generated.h"

UCLASS()
class RECOLECTARYENTREGAR_API AMG_FruitSpawner : public AActor
{
	GENERATED_BODY()

public:
	AMG_FruitSpawner();
	virtual void BeginPlay() override;

	// Clases de frutas a spawnear (asignar en Blueprint)
	UPROPERTY(EditDefaultsOnly, Category = "Fruits")
	TSubclassOf<AMG_Collectable> BananaClass;

	UPROPERTY(EditDefaultsOnly, Category = "Fruits")
	TSubclassOf<AMG_Collectable> AppleClass;

	UPROPERTY(EditDefaultsOnly, Category = "Fruits")
	TSubclassOf<AMG_Collectable> StrawberryClass;

	// Máximo de frutas en el mapa al mismo tiempo
	UPROPERTY(EditDefaultsOnly, Category = "Fruits")
	int32 MaxFruits = 20;

	// Radio del área de spawn alrededor del actor
	UPROPERTY(EditDefaultsOnly, Category = "Fruits")
	float SpawnRadius = 300.f;

private:
	void ScheduleNextSpawn(EFruitType Type);
	void SpawnFruit(EFruitType Type);
	int32 CountFruitsInWorld() const;

	FTimerHandle BananaTimer;
	FTimerHandle AppleTimer;
	FTimerHandle StrawberryTimer;
};