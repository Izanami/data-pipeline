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
 *
 */

#ifndef DP_INPUT_H_
#define DP_INPUT_H_

#include "pipeline.h"

/*! \defgroup input_pipeline Input
 * \brief File pipeline
 *
 *  \{
 */

typedef struct { DpPipeline* pipeline; } DpInput;

/// \brief Factory of input pipeline.
DpInput* DpInputNew(void) __attribute__((warn_unused_result));

/// \brief Constructor of input pipeline.
void DpInputCreate(DpInput**) __attribute__((nonnull));

/// \brief Initialize of input pipeline.
void DpInputInit(DpInput* self) __attribute__((nonnull));

/*!
 * \}
 */

#endif /* ifndef DP_INPUT_H_ */