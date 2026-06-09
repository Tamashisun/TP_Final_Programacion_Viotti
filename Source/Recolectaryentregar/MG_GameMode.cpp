#include "MG_GameMode.h"
#include "MG_GameState.h"

AMG_GameMode::AMG_GameMode()
{
}

void AMG_GameMode::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(
        CountdownTimerHandle, this,
        &AMG_GameMode::TickCountdown,
        1.f, true, 1.f
    );
}

void AMG_GameMode::TickCountdown()
{
    AMG_GameState* GS = GetGameState<AMG_GameState>();
    if (!GS) return;

    GS->SetCountdownValue(CurrentCountdown);
    GS->SetMatchPhase(EMatchPhase::Countdown);

    CurrentCountdown--;

    if (CurrentCountdown < 0)
    {
        GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
        GS->SetMatchPhase(EMatchPhase::Playing);

        GetWorldTimerManager().SetTimer(
            MatchTimerHandle, this,
            &AMG_GameMode::TickMatchTimer,
            1.f, true
        );
    }
}

void AMG_GameMode::TickMatchTimer()
{
    AMG_GameState* GS = GetGameState<AMG_GameState>();
    if (!GS) return;

    GS->SetMatchTimer(GS->TimeRemaining - 1.f);

    if (GS->TimeRemaining <= 0.f)
    {
        GS->SetMatchTimer(0.f);
        GetWorldTimerManager().ClearTimer(MatchTimerHandle);
        EndGame();
    }
}

void AMG_GameMode::EndGame()
{
    AMG_GameState* GS = GetGameState<AMG_GameState>();
    if (!GS) return;

    GS->SetMatchPhase(EMatchPhase::Finished);

    // Log del ganador
    if (GS->ScoreTeamRed > GS->ScoreTeamBlue)
    {
        UE_LOG(LogTemp, Warning, TEXT("Gano el equipo ROJO: %d pts"), GS->ScoreTeamRed);
    }
    else if (GS->ScoreTeamBlue > GS->ScoreTeamRed)
    {
        UE_LOG(LogTemp, Warning, TEXT("Gano el equipo AZUL: %d pts"), GS->ScoreTeamBlue);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Empate!"));
    }
}