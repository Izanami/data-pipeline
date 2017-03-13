/*
 *Data-Pipeline
 *Copyright © 2017 Adrien Jeser <adrien@jeser.me>
 *
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU Affero General Public License as
 *published by the Free Software Foundation, either version 3 of the
 *License, or (at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU Affero General Public License for more details.
 *
 *You should have received a copy of the GNU Affero General Public License
 *along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "input.h"

DpInput* DpInputNew(void) {
    DpInput* dp_input = g_new(DpInput, 1);
    DpInputCreate(&dp_input);
    return dp_input;
}

void DpInputCreate(DpInput** dp_input) {
    (*dp_input)->pipeline = DpPipelineNew();
    DpInputInit(*dp_input);
}

void DpInputInit(DpInput* self) { DpPipelineInit(self->pipeline); }
