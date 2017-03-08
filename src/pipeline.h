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
    GData* input;       ///< Input pipelines.
    GData* output;      ///< Output pipelines.
    GData* properties;  ///< Properties
    int input_count;    ///< Number of elements on input pipelines.
    int output_count;   ///< Number of elements on output pipelines

    // Events.

    /// \brief Call when DpPipelineGetInput()
    void (*OnGetInput)(struct DpPipeline*, const char*);

    /// \brief Call when DpPipelineGetOuput()
    void (*OnGetOutput)(struct DpPipeline*, const char*);

    /// \brief Call when DpPipelinePushInput()
    void (*OnPushInput)(struct DpPipeline*, const char*);

    /// \brief Call when DpPipelinePushOutput()
    void (*OnPushOutput)(struct DpPipeline*, const char*);

    /// \brief Call when DpPipelineDestroy()
    void (*OnDestroy)(struct DpPipeline*);
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
DpPipeline* DpPipelineGetInput(DpPipeline* self, const char* key)
    __attribute__((nonnull));

/// \brief Getter ouput pipeline.
///
/// \return The data element, or NULL if is not found.
DpPipeline* DpPipelineGetOutput(DpPipeline* self, const char* key)
    __attribute__((nonnull));

/// \brief Returns true is orphan.
///
/// A orphan is a pipeline who has no input and no ouput
gboolean DpPipelineIsOrphan(DpPipeline* self) __attribute__((nonnull));

/// \brief Setter a property
///
/// The value will be copy.
void DpPipelineSetProperty(DpPipeline* self, const char* name_property,
                           char* value) __attribute__((nonnull));

/// \brief Getter a property
GString* DpPipelineGetProperty(DpPipeline* self, const char* name_property)
    __attribute__((nonnull));

/// \brief Set observer "GetInput"
void DpPipelineOnGetInput(DpPipeline* self,
                          void observer(DpPipeline*, const char* key))
    __attribute__((nonnull));

/// \brief Set observer "GetOutput"
void DpPipelineOnGetOutput(DpPipeline* self,
                           void observer(DpPipeline*, const char* key))
    __attribute__((nonnull));

/// \brief Set observer "PushOutput"
void DpPipelineOnPushOutput(DpPipeline* self,
                            void observer(DpPipeline*, const char* key))
    __attribute__((nonnull));

/// \brief Set observer "PushOutput"
void DpPipelineOnPushInput(DpPipeline* self,
                           void observer(DpPipeline*, const char* key))
    __attribute__((nonnull));

/// \brief Set observer "Destroy"
void DpPipelineOnDestroy(DpPipeline* self, void observer(DpPipeline*))
    __attribute__((nonnull));

/*!
 * \}
 */

#endif /* ifndef DP_PIPELINE_H_ */
