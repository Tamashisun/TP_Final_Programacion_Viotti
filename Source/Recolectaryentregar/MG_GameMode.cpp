#include "MG_GameMode.h"
#include "MG_GameState.h"

AMG_GameMode::AMG_GameMode()
{
}

void AMG_GameMode::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(
        MatchTimerHandle, this,
        &AMG_GameMode::CheckVictoryCondition,
        MatchDuration, false
    );
}

void AMG_GameMode::CheckVictoryCondition()
{
    EndGame(false);
}

void AMG_GameMode::EndGame(bool bWinner)
{
    // Lo completamos en Fase 4
}