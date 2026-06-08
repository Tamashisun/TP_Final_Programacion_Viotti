#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MG_Collectable.generated.h"

UCLASS()
class RECOLECTARYENTREGAR_API AMG_Collectable : public AActor
{
	GENERATED_BODY()

public:
	AMG_Collectable();

	virtual void BeginPlay() override;

	// Mesh visible del objeto
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	// Colision para detectar overlap
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* CollisionSphere;

	// Puntos que vale este objeto
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated)
	int32 PointValue = 1;

	// Si ya fue recogido
	UPROPERTY(ReplicatedUsing = OnRep_IsPickedUp, BlueprintReadOnly)
	bool bIsPickedUp = false;

	UFUNCTION()
	void OnRep_IsPickedUp();

	// Llamado cuando el jugador lo recoge
	UFUNCTION(BlueprintCallable)
	void PickUp();

	// Llamado para reaparecer
	UFUNCTION()
	void Respawn();

	virtual void GetLifetimeReplicatedProps(
		TArray<FLifetimeProperty>& OutLifetimeProps
	) const override;

private:
	FTimerHandle RespawnTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	float RespawnTime = 10.f;
};