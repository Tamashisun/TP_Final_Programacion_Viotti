#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MG_PlayerState.generated.h"

UCLASS()
class RECOLECTARYENTREGAR_API AMG_PlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 IndividualScore = 0;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 TeamID = 0;

    UPROPERTY(ReplicatedUsing = OnRep_PlayerAlive, BlueprintReadOnly)
    bool bIsAlive = true;

    UFUNCTION()
    void OnRep_PlayerAlive();

    virtual void GetLifetimeReplicatedProps(
        TArray<FLifetimeProperty>& OutLifetimeProps
    ) const override;
};