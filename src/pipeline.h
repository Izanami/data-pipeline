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

/*! \defgroup pipeline Pipeline
 *  \{
 */

/// \brief Pipeline class.
typedef struct DpPipeline {
    GData* input;      ///< Input pipelines.
    GData* output;     ///< Output pipelines.
    int input_count;   ///< Number of elements on input pipelines.
    int output_count;  ///< Number of elements on output pipelines.
} DpPipeline;

/// \brief Factory of pipeline.
///
/// You SHOULD NOT used. Prefer DpJobPipelineNew().
//
/// Pipeline MUST freed with DpPipelineDestroy().
///
/// Example:
/// \code
///  DpPipeline* pipeline = DpPipelineNew();
///  DpPipeline* pipeline_output = DpPipelineNew();
///
///  DpPipelinePushOutput(pipeline, "foo", pipeline_ouput);
///
///  DpPipelineDestroy(&pipeline_ouput);
///  DpPipelineDestroy(&pipeline);
/// \endcode
DpPipeline* DpPipelineNew(void) __attribute__((warn_unused_result));

/// \brief Constructor of pipeline.
///
/// You SHOULD NOT used. Prefer DpJobPipelineNew().
///
/// Pipeline MUST freed with DpPipelineDestroy().
void DpPipelineCreate(DpPipeline**) __attribute__((nonnull));

/// \brief Destructor of pipeline.
void DpPipelineDestroy(DpPipeline**) __attribute__((nonnull));

/// \brief Initialize of pipeline.
void DpPipelineInit(DpPipeline* self) __attribute__((nonnull));

/// \brief Deallocation memory of data in pipeline.
void DpPipelineFree(DpPipeline* self) __attribute__((nonnull));

/// \brief Push pipeline on inputs channel.
///
///  If the key exists, pipeline is replaced.
gboolean DpPipelinePushInput(DpPipeline* self, const char* key,
                             DpPipeline* pipeline_input)
    __attribute__((nonnull));

/// \brief Push pipeline on output channel.
///
///  If the key exists, pipeline is replaced.
gboolean DpPipelinePushOutput(DpPipeline* self, const char* key,
                              DpPipeline* pipeline_output)
    __attribute__((nonnull));

/// \brief Getter input pipeline.
///
/// \return The data element, or NULL if is not found.
gpointer DpPipelineGetInput(DpPipeline* self, const char* key)
    __attribute__((nonnull));

/// \brief Getter ouput pipeline.
///
/// \return The data element, or NULL if is not found.
gpointer DpPipelineGetOutput(DpPipeline* self, const char* key)
    __attribute__((nonnull));

/*!
 * \}
 */

#endif /* ifndef DP_PIPELINE_H_ */
