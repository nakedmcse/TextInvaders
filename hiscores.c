// Hiscores
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#ifdef _WIN32
#include "sqlite3.h"
#else
#include<sqlite3.h>
#endif
#include "types.h"

sqlite3 *createContext() {
    int rc;
    char *createSql = "CREATE TABLE IF NOT EXISTS HISCORES(ID INT PRIMARY KEY NOT NULL, SCORE INT NOT NULL, WAVE INT NOT NULL, NAME CHAR(3));";
    char *errMsg = 0;
    sqlite3 *context = NULL;
    rc = sqlite3_open("invaders.db", &context);
    if (rc==SQLITE_OK) {
        rc = sqlite3_exec(context, createSql, NULL, 0, &errMsg);
        if (rc!=SQLITE_OK) {
            sqlite3_free(errMsg);
            sqlite3_close(context);
            context = NULL;
        }
    }
    return context;
}

char **readDbScores(sqlite3 *context, int *rows) {
    int rc, cols;
    char *readSql = "SELECT ID,SCORE,WAVE,NAME FROM HISCORES;";
    char *errMsg = 0;
    char **results = 0;

    if (context) {
        rc = sqlite3_get_table(context, readSql, &results, rows, &cols, &errMsg);
        if (rc!=SQLITE_OK) {
            sqlite3_free(errMsg);
            sqlite3_free_table(results);
            return NULL;
        }
    }
    return results;
}

sqlite3 *initHiscores(hiscore *Hiscores) {
    int i, rows;
    char **results = 0;
    sqlite3 *context = createContext();

    results = readDbScores(context, &rows);
    for(i = 0; i < MAX_HISCORES; i++) {
        if(results && i<rows) {
            int baseRow = (i+1)*4;
            sprintf(Hiscores[i].name, "%s", results[baseRow+3]);
            Hiscores[i].score = atoi(results[baseRow+1]);
            Hiscores[i].wave = atoi(results[baseRow+2]);
            continue;
        }
        sprintf(Hiscores[i].name, "---");
        Hiscores[i].score = 0;
        Hiscores[i].wave = 0;
    }
    if(results) sqlite3_free_table(results);
    return context;
}

int checkHiscore(player *Player, hiscore *Hiscores, int wave) {
    int i;
    for(i = 0; i < MAX_HISCORES; i++) {
        if (Player->score + wave > Hiscores[i].score + Hiscores[i].wave) {
            Hiscores[i].score = Player->score;
            Hiscores[i].wave = wave;
            break;
        }
    }
    return i;
}

void updateDbScores(sqlite3 *context, hiscore *Hiscores) {
    int i, rc;
    sqlite3_stmt* stmt = 0;
    char *insertSql = "REPLACE INTO HISCORES(ID,SCORE,WAVE,NAME) VALUES (?,?,?,?);";
    for(i = 0; i < MAX_HISCORES; i++) {
        if(context) {
            rc = sqlite3_prepare_v2(context, insertSql, -1, &stmt, NULL);
            rc = rc | sqlite3_bind_int(stmt, 1, i+1);  // id
            rc = rc | sqlite3_bind_int(stmt, 2, Hiscores[i].score);  // score
            rc = rc | sqlite3_bind_int(stmt, 3, Hiscores[i].wave);  // wave
            rc = rc | sqlite3_bind_text(stmt, 4, Hiscores[i].name, 3, NULL); // name
            if (rc == SQLITE_OK) sqlite3_step(stmt);
            sqlite3_clear_bindings(stmt);
            sqlite3_finalize(stmt);
        }
    }
}
