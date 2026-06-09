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
    float TimeRemaining = 180.f;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 GlobalScore = 0;

    // Puntaje por equipo
    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 ScoreTeamRed = 0;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 ScoreTeamBlue = 0;

    UPROPERTY(ReplicatedUsing = OnRep_GameActive, BlueprintReadOnly)
    bool bGameActive = false;

    UFUNCTION()
    void OnRep_GameActive();
};