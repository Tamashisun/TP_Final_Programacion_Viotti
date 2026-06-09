#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MG_Collectable.generated.h"

UENUM(BlueprintType)
enum class EFruitType : uint8
{
	Banana      UMETA(DisplayName = "Banana"),
	Apple     UMETA(DisplayName = "Apple"),
	Strawberry    UMETA(DisplayName = "Strawberry")
};

UCLASS()
class RECOLECTARYENTREGAR_API AMG_Collectable : public AActor
{
	GENERATED_BODY()

public:
	AMG_Collectable();
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* CollisionSphere;

	// Tipo de fruta — define el PointValue automáticamente
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated)
	EFruitType FruitType = EFruitType::Banana;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated)
	int32 PointValue = 1;

	UPROPERTY(ReplicatedUsing = OnRep_IsPickedUp, BlueprintReadOnly)
	bool bIsPickedUp = false;

	UFUNCTION()
	void OnRep_IsPickedUp();

	UFUNCTION(BlueprintCallable)
	void PickUp();

	// Ya no hace respawn — el spawner crea una nueva
	void SelfDestroy();

	virtual void GetLifetimeReplicatedProps(
		TArray<FLifetimeProperty>& OutLifetimeProps
	) const override;
};