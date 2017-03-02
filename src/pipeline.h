/*!
 * \file pipeline.h
 * \brief Pipeline struct.
 * \author Adrien Jeser
 * \copyright GPLv3
 */

#ifndef DP_PIPELINE_H_
#define DP_PIPELINE_H_

#include "glib.h"
#include "job.h"

/// \brief Pipeline class.
typedef struct DpPipeline {
    GData* input;   ///< Input pipelines.
    GData* output;  ///< Output pipelines.
    DpJob* job;     ///< Job.
} DpPipeline;

/// \brief Builder of pipeline.
///
/// Pipeline MUST freed with DpPipelineDestroy().
///
/// Example:
/// \code
///
///  DpPipeline* pipeline = DpPipelineNew();
///  DpPipeline* pipeline_output = DpPipelineNew();
///
///  DpPipelinePushOutput(pipeline, "foo", pipeline_ouput);
///
///  DpPipelineDestroy(&pipeline_ouput);
///  DpPipelineDestroy(&pipeline);
/// \endcode
DpPipeline* DpPipelineNew(void);

/// \brief Constructor of pipeline.
///
/// Prefer use DpPipelinesNew().
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
gboolean DpPipelinePushInput(DpPipeline* self, const char* key,
                             DpPipeline* pipeline_input);

/// \brief Push pipeline on output channel.
///
///  If the key exists, pipeline is replaced.
gboolean DpPipelinePushOutput(DpPipeline* self, const char* key,
                              DpPipeline* pipeline_output);

/// \brief Getter input pipeline.
///
/// \return The data element, or NULL if is nout found.
gpointer DpPipelineGetInput(DpPipeline* self, const char* key);

/// \brief Getter ouput pipeline.
///
/// \return The data element, or NULL if is nout found.
gpointer DpPipelineGetOutput(DpPipeline* self, const char* key);

#endif /* ifndef DP_PIPELINE_H_ */
