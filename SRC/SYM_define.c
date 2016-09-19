/*
 * SYM_define.c
 *
 *  Created on: 2016Äê9ÔÂ17ÈÕ
 *      Author: voidman
 */

#include "SYM_app.h"

// Global var definition
gc_SYM_ECAT_CMD_ALL		go_SYM_ECAT_CMD;
gc_SYM_ECAT_DOWN_DATA	go_SYM_ECAT_DOWN_DATA;
gc_SYM_ECAT_DOWN_DATA_DECODED	go_SYM_ECAT_DOWN_DATA_DECODED;

gc_SYM_MC_SVPWM_MOD go_SYM_MC_SVPWM_MOD;
int gi_seq_cnt = 0;
int gi_test_vect[8] = {0, 1, 2, 1, 0, -1, -2, -1};
//int gi_test_vect[8] = {-2,-2,-2,-2,-2,-2,-2,-2};
int gi_polarity_flag = 0;


int gi_Vector[3][7][3] = {
		{ {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}, {0, 1, 1}, {0, 0, 1}, {1, 0, 1} },
		{ {0, 0, 0}, {2, 0, 1}, {2, 1, 0}, {1, 2, 0}, {0, 2, 1}, {0, 1, 2}, {1, 0, 2} },
		{ {0, 0, 0}, {2, 0, 0}, {2, 2, 0}, {0, 2, 0}, {0, 2, 2}, {0, 0, 2}, {2, 0, 2} }
};

int gi_Tree[81][3][3] = {
        {    {1, 1, 1},
                {1, INF, INF},
                {1, INF, INF } },

        {    {1, 1, 1},
                {1, INF, INF},
                {INF, 1, INF } },

        {    {1, 1, 1},
                {1, INF, INF},
                {INF, INF, 1 } },

        {    {1, 1, 1},
                {INF, 1, INF},
                {1, INF, INF } },

        {    {1, 1, 1},
                {INF, 1, INF},
                {INF, 1, INF } },

        {    {1, 1, 1},
                {INF, 1, INF},
                {INF, INF, 1 } },

        {    {1, 1, 1},
                {INF, INF, 1},
                {1, INF, INF } },

        {    {1, 1, 1},
                {INF, INF, 1},
                {INF, 1, INF } },

        {    {1, 1, 1},
                {INF, INF, 1},
                {INF, INF, 1 } },

        {    {1, 1, INF},
                {1, INF, 1},
                {1, INF, INF } },

        {    {1, 1, INF},
                {1, INF, 1},
                {INF, 1, INF } },

        {    {1, 1, INF},
                {1, INF, 1},
                {INF, INF, 1 } },

        {    {1, 1, INF},
                {1, INF, INF},
                {1, INF, 1 } },

        {    {1, 1, INF},
                {1, INF, INF},
                {INF, 1, 1 } },

        {    {1, 1, INF},
                {INF, 1, 1},
                {1, INF, INF } },

        {    {1, 1, INF},
                {INF, 1, 1},
                {INF, 1, INF } },

        {    {1, 1, INF},
                {INF, 1, 1},
                {INF, INF, 1 } },

        {    {1, 1, INF},
                {INF, 1, INF},
                {1, INF, 1 } },

        {    {1, 1, INF},
                {INF, 1, INF},
                {INF, 1, 1 } },

        {    {1, 1, INF},
                {INF, INF, 1},
                {1, INF, 1 } },

        {    {1, 1, INF},
                {INF, INF, 1},
                {INF, 1, 1 } },

        {    {1, INF, 1},
                {1, 1, INF},
                {1, INF, INF } },

        {    {1, INF, 1},
                {1, 1, INF},
                {INF, 1, INF } },

        {    {1, INF, 1},
                {1, 1, INF},
                {INF, INF, 1 } },

        {    {1, INF, 1},
                {1, INF, INF},
                {1, 1, INF } },

        {    {1, INF, 1},
                {1, INF, INF},
                {INF, 1, 1 } },

        {    {1, INF, 1},
                {INF, 1, 1},
                {1, INF, INF } },

        {    {1, INF, 1},
                {INF, 1, 1},
                {INF, 1, INF } },

        {    {1, INF, 1},
                {INF, 1, 1},
                {INF, INF, 1 } },

        {    {1, INF, 1},
                {INF, 1, INF},
                {1, 1, INF } },

        {    {1, INF, 1},
                {INF, 1, INF},
                {INF, 1, 1 } },

        {    {1, INF, 1},
                {INF, INF, 1},
                {1, 1, INF } },

        {    {1, INF, 1},
                {INF, INF, 1},
                {INF, 1, 1 } },

        {    {1, INF, INF},
                {1, 1, 1},
                {1, INF, INF } },

        {    {1, INF, INF},
                {1, 1, 1},
                {INF, 1, INF } },

        {    {1, INF, INF},
                {1, 1, 1},
                {INF, INF, 1 } },

        {    {1, INF, INF},
                {1, 1, INF},
                {1, INF, 1 } },

        {    {1, INF, INF},
                {1, 1, INF},
                {INF, 1, 1 } },

        {    {1, INF, INF},
                {1, INF, 1},
                {1, 1, INF } },

        {    {1, INF, INF},
                {1, INF, 1},
                {INF, 1, 1 } },

        {    {1, INF, INF},
                {1, INF, INF},
                {1, 1, 1 } },

        {    {1, INF, INF},
                {INF, 1, 1},
                {1, 1, INF } },

        {    {1, INF, INF},
                {INF, 1, 1},
                {1, INF, 1 } },

        {    {1, INF, INF},
                {INF, 1, INF},
                {1, 1, 1 } },

        {    {1, INF, INF},
                {INF, INF, 1},
                {1, 1, 1 } },

        {    {INF, 1, 1},
                {1, 1, INF},
                {1, INF, INF } },

        {    {INF, 1, 1},
                {1, 1, INF},
                {INF, 1, INF } },

        {    {INF, 1, 1},
                {1, 1, INF},
                {INF, INF, 1 } },

        {    {INF, 1, 1},
                {1, INF, 1},
                {1, INF, INF } },

        {    {INF, 1, 1},
                {1, INF, 1},
                {INF, 1, INF } },

        {    {INF, 1, 1},
                {1, INF, 1},
                {INF, INF, 1 } },

        {    {INF, 1, 1},
                {1, INF, INF},
                {1, 1, INF } },

        {    {INF, 1, 1},
                {1, INF, INF},
                {1, INF, 1 } },

        {    {INF, 1, 1},
                {INF, 1, INF},
                {1, 1, INF } },

        {    {INF, 1, 1},
                {INF, 1, INF},
                {1, INF, 1 } },

        {    {INF, 1, 1},
                {INF, INF, 1},
                {1, 1, INF } },

        {    {INF, 1, 1},
                {INF, INF, 1},
                {1, INF, 1 } },

        {    {INF, 1, INF},
                {1, 1, 1},
                {1, INF, INF } },

        {    {INF, 1, INF},
                {1, 1, 1},
                {INF, 1, INF } },

        {    {INF, 1, INF},
                {1, 1, 1},
                {INF, INF, 1 } },

        {    {INF, 1, INF},
                {1, 1, INF},
                {1, INF, 1 } },

        {    {INF, 1, INF},
                {1, 1, INF},
                {INF, 1, 1 } },

        {    {INF, 1, INF},
                {1, INF, 1},
                {1, 1, INF } },

        {    {INF, 1, INF},
                {1, INF, 1},
                {INF, 1, 1 } },

        {    {INF, 1, INF},
                {1, INF, INF},
                {1, 1, 1 } },

        {    {INF, 1, INF},
                {INF, 1, 1},
                {1, 1, INF } },

        {    {INF, 1, INF},
                {INF, 1, 1},
                {1, INF, 1 } },

        {    {INF, 1, INF},
                {INF, 1, INF},
                {1, 1, 1 } },

        {    {INF, 1, INF},
                {INF, INF, 1},
                {1, 1, 1 } },

        {    {INF, INF, 1},
                {1, 1, 1},
                {1, INF, INF } },

        {    {INF, INF, 1},
                {1, 1, 1},
                {INF, 1, INF } },

        {    {INF, INF, 1},
                {1, 1, 1},
                {INF, INF, 1 } },

        {    {INF, INF, 1},
                {1, 1, INF},
                {1, INF, 1 } },

        {    {INF, INF, 1},
                {1, 1, INF},
                {INF, 1, 1 } },

        {    {INF, INF, 1},
                {1, INF, 1},
                {1, 1, INF } },

        {    {INF, INF, 1},
                {1, INF, 1},
                {INF, 1, 1 } },

        {    {INF, INF, 1},
                {1, INF, INF},
                {1, 1, 1 } },

        {    {INF, INF, 1},
                {INF, 1, 1},
                {1, 1, INF } },

        {    {INF, INF, 1},
                {INF, 1, 1},
                {1, INF, 1 } },

        {    {INF, INF, 1},
                {INF, 1, INF},
                {1, 1, 1 } },

        {    {INF, INF, 1},
                {INF, INF, 1},
                {1, 1, 1 } }
};

