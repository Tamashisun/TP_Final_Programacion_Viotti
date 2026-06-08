#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MG_GameState.generated.h"

UCLASS()
class RECOLECTARYENTREGAR_API AMG_GameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    UPROPERTY(Replicated, BlueprintReadOnly)
    float TimeRemaining = 120.f;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 GlobalScore = 0;

    UPROPERTY(ReplicatedUsing = OnRep_GameActive, BlueprintReadOnly)
    bool bGameActive = false;

    UFUNCTION()
    void OnRep_GameActive();

    virtual void GetLifetimeReplicatedProps(
        TArray<FLifetimeProperty>& OutLifetimeProps
    ) const override;
};