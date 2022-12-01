#pragma once

/// <summary>
/// Uma classe simples representando um Countdown Timer
/// para controle de tempo dos jogadores. � um timer que
/// come�a em X segundos e vai decrementando at� chegar em 0.
/// </summary>
class CountdownTimer {
private:
    long _seconds;
    long _startedAt;
    bool _isStarted;
    bool _isPaused;

public:
    /// <summary>
    /// Cria um timer de "seconds" segundos.
    /// </summary>
    /// <param name="seconds">segundos do timer</param>
    CountdownTimer(int seconds);
    
    void Start();
    void Pause();
    void Resume();
    bool IsPaused();
    long GetRemainingSeconds();
    
    /// <summary>
    /// Obtem o tempo restante como uma string amig�vel.
    /// </summary>
    /// <returns>Uma string formatada "MM:SS" do tempo restante </returns>
    String GetRemainingTime();
};