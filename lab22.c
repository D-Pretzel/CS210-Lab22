#include <stdio.h>

//For now, you'll test your function using the 10 games listed in main().  This will need to change to 1075 when you read from the file
#define NUM_GAMES 1075
#include "lab22.h"

int main(){

    //These are the IDs for the teams for the game we are predicting
    int team1 = 48;
    int team2 = 39;


    // ----------------------------------------------------------------------------------
    // Step 1:  Read the the contents of games.csv into the parallel arrays above
    // ----------------------------------------------------------------------------------
    int homeIDs[NUM_GAMES] = {0};
    int awayIDs[NUM_GAMES] = {0};
    int homeScores[NUM_GAMES] = {0};
    int awayScores[NUM_GAMES] = {0};
    int homeAssists[NUM_GAMES] = {0};
    int awayAssists[NUM_GAMES] = {0};
    int homeRebounds[NUM_GAMES] = {0};
    int awayRebounds[NUM_GAMES] = {0};
    int homeTeamWins[NUM_GAMES] = {0};
    double homeFgPcts[NUM_GAMES] = {0};
    double awayFgPcts[NUM_GAMES] = {0};
    double homeFg3Pcts[NUM_GAMES] = {0};
    double awayFg3Pcts[NUM_GAMES] = {0};
    double homeFtPcts[NUM_GAMES] = {0};
    double awayFtPcts[NUM_GAMES] = {0};

    FILE *fp = fopen("games.csv", "r");
    if (fp == NULL) {
        puts("Error!!!");
        return -1;
    }

    char line[1024];
    int i = 0;
    fgets(line, 1024, fp);
    // Read values of the file without the first line
    while (!feof(fp)) {
        fscanf(fp, "%d,%d,%d,%lf,%lf,%lf,%d,%d,%d,%lf,%lf,%lf,%d,%d,%d\n", &homeIDs[i], &awayIDs[i], &homeScores[i], &homeFgPcts[i], &homeFtPcts[i], &homeFg3Pcts[i], &homeAssists[i], &homeRebounds[i], &awayScores[i], &awayFgPcts[i], &awayFtPcts[i], &awayFg3Pcts[i], &awayAssists[i], &awayRebounds[i], &homeTeamWins[i]);
        i++;
    }
    fclose(fp);

    // ----------------------------------------------------------------------------------
    // Step 2:  Call the 5 functions and gather their data
    // ----------------------------------------------------------------------------------
    // Call pointDifferentialPerGameOneTeam 2x – once for the home team and once for the away time
    double homePointDifferential = pointDifferentialPerGameOneTeam(team1, homeIDs, awayIDs, homeScores, awayScores, NUM_GAMES);
    double awayPointDifferential = pointDifferentialPerGameOneTeam(team2, homeIDs, awayIDs, homeScores, awayScores, NUM_GAMES);
    // Subtract the home team from the away team to get the pointDifferentialStat
    double pointDifferentialStat =homePointDifferential - awayPointDifferential;
    // Call shootingEffectivenessOneTeam 2x – once for the home team and once for the away time
    double homeShootingEffectiveness = shootingEffectivenessOneTeam(team1, homeIDs, awayIDs, homeFgPcts, awayFgPcts, homeFg3Pcts, awayFg3Pcts, homeFtPcts, awayFtPcts, NUM_GAMES);
    double awayShootingEffectiveness = shootingEffectivenessOneTeam(team2, homeIDs, awayIDs, homeFgPcts, awayFgPcts, homeFg3Pcts, awayFg3Pcts, homeFtPcts, awayFtPcts, NUM_GAMES);
    // Subtract the home team from the away team to get the shootingDifferentialStat
    double shootingDifferentialStat = homeShootingEffectiveness - awayShootingEffectiveness;
    // Call reboundsPerGameComparison once to get the reboundingStat
    double reboundingStat = reboundsPerGameComparison(team1, team2, homeIDs, awayIDs, homeRebounds, awayRebounds, NUM_GAMES);
    // Call assistsPerGameComparison once to get the assistStat
    double assistStat = assistsPerGameComparison(team1, team2, homeIDs, awayIDs, homeAssists, awayAssists, NUM_GAMES);
    // Call headToHeadWL once to get the headToHeadStat
    double headToHeadStat = headToHeadWL(team1, team2, homeIDs, awayIDs, homeTeamWins, NUM_GAMES);

    // ----------------------------------------------------------------------------------
    // Step 3:  Use the following formula to predict the winner
    // (pointDifferentialStat * 0.6) + headToHeadStat + (shootingDifferentialStat * 120) + reboundingStat + (assistStat * 0.75)
    // ----------------------------------------------------------------------------------
    double prediction = (pointDifferentialStat * 0.6) + headToHeadStat + (shootingDifferentialStat * 120) + reboundingStat + (assistStat * 0.75);

    // ----------------------------------------------------------------------------------
    // Print out the output
    // ----------------------------------------------------------------------------------
    // If the value is > 0, then the home team is predicted to win; if the value is <= 0, then the away team is predicted to win
    if (prediction > 0) {
        printf("The final output is %.2f, which means team %d is predicted to win the game.\n", prediction, team1);
    } else {
        printf("The final output is %.2f, which means team %d is predicted to win the game.\n", prediction, team1);
    }
    return 0;
}