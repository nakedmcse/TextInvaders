// Hiscore
#ifndef TEXTINVADER_HISCORE
#define TEXTINVADER_HISCORE

sqlite3 *createContext();
char **readDbScores(sqlite3 *context, int *rows);
sqlite3 *initHiscores(hiscore *Hiscores);
int checkHiscore(player *Player, hiscore *Hiscores, int wave);
void updateDbScores(sqlite3 *context, hiscore *Hiscores);

#endif
