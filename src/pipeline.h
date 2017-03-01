/*!
 * \file pipeline.h
 * \brief Pipeline struct.
 * \author Adrien Jeser
 * \copyright GPLv3
 */

#ifndef DP_PIPELINE_H_
#define DP_PIPELINE_H_

#include "glib.h"

/// \brief Pipeline class.
typedef struct DpPipeline {
    GData* input;   ///< Input pipelines.
    GData* output;  ///< Output pipelines.
} DpPipeline;

/// \brief Constructor of pipeline.
///
/// Pipeline MUST freed with DpPipelineDestroy()
///
/// Example:
/// \code
///  DpPipeline *pipeline = NULL;
///  DpPipeline *pipeline_output = NULL;
///
///  DpPipelineCreate(&pipeline);
///  DpPipelineCreate(&pipeline_output);
///
///  DpPipelinePushOutput(pipeline, "foo", pipeline_ouput);
///
///  DpPipelineDestroy(&pipeline_ouput);
///  DpPipelineDestroy(&pipeline);
/// \endcode

void DpPipelineCreate(DpPipeline**);

/// \brief Destructor of pipeline.
void DpPipelineDestroy(DpPipeline**);

/// \brief Initialize of pipeline.
void DpPipelineInit(DpPipeline* self);

/// \brief Deallocation memory of data in pipeline.
void DpPipelineFree(DpPipeline* self);

/// \brief Push pipeline on inputs channel.
///
///  If the key exists, pipeline is replaced.
gboolean DpPipelinePushInput(DpPipeline* self, const char* name,
                             DpPipeline* pipeline_input);

/// \brief Push pipeline on output channel.
///
///  If the key exists, pipeline is replaced.
gboolean DpPipelinePushOutput(DpPipeline* self, const char* name,
                              DpPipeline* pipeline_output);

#endif /* ifndef DP_PIPELINE_H_ */
