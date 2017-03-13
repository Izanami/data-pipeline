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

#ifndef DP_FILE_H_
#define DP_FILE_H_

#include "pipeline.h"

/*! \defgroup file_pipeline File pipeline.
 *
 *  \{
 */

/// \brief Factory of file pipeline.
DpPipeline* DpFileNew(void) __attribute__((warn_unused_result));

/// \brief Constructor of file pipeline.
void DpFileCreate(DpPipeline**) __attribute__((nonnull));

/// \brief Initialize of file pipeline.
void DpFileInit(DpPipeline* self) __attribute__((nonnull));

/*!
 * \}
 */
/*!
 * \}
 */

#endif /* ifndef DP_FILE_H_ */
