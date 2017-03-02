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

#ifndef DP_JOB_H_
#define DP_JOB_H_

#include "glib.h"

/// \brief Job class.
typedef struct { GSList* pipelines; } DpJob;

/// \brief Builder of job.
DpJob* DpJobNew(void);

/// \brief Constructor of job.
void DpJobCreate(DpJob**);

/// \brief Destructor of job.
void DpJobDestroy(DpJob**);

/// \brief Initalize data in job
void DpJobInit(DpJob*);

/// \brief Deallocation memory of job.
void DpJobFree(DpJob*);

/// \brief Build a pipeline.
gpointer DpJobPipelineNew(DpJob*);

/// \brief Returns all orhpans pipelines.
GSList* DpJobOrphan(DpJob*);

/// \brief Destroy all orphans pipelines.
void DpJobOrphanDestroy(DpJob*);

#endif /* ifndef DP_JOB_H_ */
