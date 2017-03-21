/*!
 * \file store.h
 * \brief Store struct.
 * \author Adrien Jeser
 * \copyright GPLv3
 */

#ifndef DP_STORE_H_
#define DP_STORE_H_

#include "glib.h"

/*! \defgroup store Store
 * \brief « Store » about handle data.
 *
 *  \{
 */

/// \brief List types can be in store.
typedef enum { kInteger = 0, kString } DpType;

/// \brief Store class.
typedef struct {
    DpType type;  ///< Type of data. See DpType.
    int padding;  ///< Padding
    void* data;   ///< Data.
} DpStore;

/// \brief Factory of store.
DpStore* DpStoreNew(DpType type, void* data)
    __attribute__((warn_unused_result,
                   overloadable  /// Overloadable
                   ));

/// \brief Factory of store, with integer.
DpStore* DpStoreNew(int* data)
    __attribute__((warn_unused_result, overloadable));

/// \brief Factory of store, with string.
DpStore* DpStoreNew(char* data)
    __attribute__((warn_unused_result, overloadable));

/// \brief Constructor of store.
///
/// You SHOULD NOT used. Prefer DpStoreNew().
///
/// Pipeline MUST freed with DpStoreDestroy().
void DpStoreCreate(DpStore**, DpType type, void* data) __attribute__((nonnull));

/// \brief Destroy a store.
void DpStoreDestroy(DpStore**) __attribute__((nonnull));

/// \brief Initialize a store.
void DpStoreInit(DpStore* self, DpType type, void* data)
    __attribute__((nonnull));

/// \brief Deallocation memory of data in pipeline.
void DpStoreFree(DpStore* self) __attribute__((nonnull));

/// \brief Returns true, if type data is same.
gboolean DpStoreIs(DpStore* self, DpType) __attribute__((nonnull));

/// \brief Returns true, if type data is same.
gboolean DpStoreSame(DpStore* self, int*)
    __attribute__((nonnull, overloadable));

/*!
 * \}
 */

#endif /* ifndef DP_STORE_H_ */
