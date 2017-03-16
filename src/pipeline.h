/*!
 * \file pipeline.h
 * \brief Pipeline struct.
 * \author Adrien Jeser
 * \copyright GPLv3
 */

#ifndef DP_PIPELINE_H_
#define DP_PIPELINE_H_

#include "glib.h"

/*! \defgroup pipeline Pipeline
 * \brief « Pipeline » is a primitive type.
 *
 * It can be connected to other inputs or outputs.
 *  \{
 */

/// \brief Create a new pipeline.
#define DP_NEW_CLASS(TYPENAME)                                                \
    void DpPipelineCreate(TYPENAME**) __attribute__((nonnull, overloadable)); \
    void DpPipelineInit(TYPENAME*) __attribute__((nonnull, overloadable));    \
    void DpPipelineDestroy(TYPENAME**) __attribute__((nonnull, overloadable));

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

    /// \brief Call when input pipeline uploaded.
    void (*OnUploadedInput)(struct DpPipeline*);
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
void DpPipelineCreate(DpPipeline**) __attribute__((nonnull, overloadable));

/// \brief Destroy a pipeline.
void DpPipelineDestroy(DpPipeline**)
    __attribute__((nonnull,
                   overloadable  /// Attribute : Overload
                   ));

/// \brief Initialize of pipeline.
void DpPipelineInit(DpPipeline* self) __attribute__((nonnull, overloadable));

/// \brief Deallocation memory of data in pipeline.
void DpPipelineFree(DpPipeline* self) __attribute__((nonnull, overloadable));

/// \brief Push pipeline on inputs channel.
///
///  If the key exists, pipeline is replaced.
gboolean DpPipelinePushInput(DpPipeline* self, const char* key,
                             DpPipeline* pipeline_input)
    __attribute__((nonnull, overloadable));

gboolean DpPipelinePushInput(DpPipeline* self, const char* key,
                             DpPipeline* pipeline_input)
    __attribute__((nonnull, overloadable));

/// \brief Push pipeline on output channel.
///
///  If the key exists, pipeline is replaced.
gboolean DpPipelinePushOutput(DpPipeline* self, const char* key,
                              DpPipeline* pipeline_output)
    __attribute__((nonnull, overloadable));

/// \brief Getter input pipeline.
///
/// \return The data element, or NULL if is not found.
DpPipeline* DpPipelineGetInput(DpPipeline* self, const char* key)
    __attribute__((nonnull, overloadable));

/// \brief Getter ouput pipeline.
///
/// \return The data element, or NULL if is not found.
DpPipeline* DpPipelineGetOutput(DpPipeline* self, const char* key)
    __attribute__((nonnull, overloadable));

/// \ brief Remove a input pipeline.
void DpPipelineRemoveInput(DpPipeline* self, const char* key)
    __attribute__((nonnull, overloadable));

/// \ brief Remove a output pipeline.
void DpPipelineRemoveOutput(DpPipeline* self, const char* key)
    __attribute__((nonnull, overloadable));

/// \brief Returns true is orphan.
///
/// A orphan is a pipeline who has no input and no ouput
gboolean DpPipelineIsOrphan(DpPipeline* self)
    __attribute__((nonnull, overloadable));

/// \brief Setter a property
///
/// The value will be copy.
void DpPipelineSetProperty(DpPipeline* self, const char* name_property,
                           char* value) __attribute__((nonnull, overloadable));

/// \brief Getter a property
GString* DpPipelineGetProperty(DpPipeline* self, const char* name_property)
    __attribute__((nonnull, overloadable));

/// \brief Set observer "GetInput"
void DpPipelineOnGetInput(DpPipeline* self,
                          void observer(DpPipeline*, const char* key))
    __attribute__((nonnull, overloadable));

/// \brief Set observer "GetOutput"
void DpPipelineOnGetOutput(DpPipeline* self,
                           void observer(DpPipeline*, const char* key))
    __attribute__((nonnull, overloadable));

/// \brief Set observer "PushOutput"
void DpPipelineOnPushOutput(DpPipeline* self,
                            void observer(DpPipeline*, const char* key))
    __attribute__((nonnull, overloadable));

/// \brief Set observer "PushOutput"
void DpPipelineOnPushInput(DpPipeline* self,
                           void observer(DpPipeline*, const char* key))
    __attribute__((nonnull, overloadable));

/// \brief Set observer "Destroy"
void DpPipelineOnDestroy(DpPipeline* self, void observer(DpPipeline*))
    __attribute__((nonnull, overloadable));

/// \brief Set observer "UploadedInput"
void DpPipelineOnUploadedInput(DpPipeline* self, void observer(DpPipeline*))
    __attribute__((nonnull, overloadable));

/// \brief Returns true, if the input pipeline exits
gboolean DpPipelineIsInputExists(DpPipeline* self, const char* key)
    __attribute__((nonnull, overloadable));

/// \brief Returns true, if the output pipeline exits
gboolean DpPipelineIsOutputExists(DpPipeline* self, const char* key)
    __attribute__((nonnull, overloadable));

/// \brief Side effect, when pipeline is uploaded.
void DpPipelineDidUploaded(DpPipeline* self)
    __attribute__((nonnull, overloadable));

/*!
 * \}
 */

#endif /* ifndef DP_PIPELINE_H_ */
