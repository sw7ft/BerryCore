/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_resourcestate_h
#define cascades_resourcestate_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

/*!
 * @brief Exposes resource state enum to QML
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT ResourceState {
    Q_GADGET
    Q_ENUMS (Type)

public:

    /*!
    * @brief Definitions of the resource states.
    *
    * @xmlonly
    * <apigrouping group="User interface/Resources"/>
    * @endxmlonly    
     *
     * @since BlackBerry 10.0.0
    */
    enum Type {
        /*! @brief The state is not known.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown,
        /*! @brief The resource is being loaded (for example, it's downloading or decoding, etc).
         *
         * @since BlackBerry 10.0.0
         */
        Loading,
        /*! @brief The resource is loaded and is ready to be used.
         *
         * @since BlackBerry 10.0.0
         */
        Loaded,
        /*! @brief The resource is not found (for example, the given path is invalid).
         *
         * @since BlackBerry 10.0.0
         */
        ErrorNotFound,
        /*! @brief The resource is found but could not be recognized (for example, the data is corrupt or has an unhandled format).
         *
         * @since BlackBerry 10.0.0
         */
        ErrorInvalidFormat,
        /*! @brief There's not enough memory to decode the resource.
         *
         * @since BlackBerry 10.0.0
         */
        ErrorMemory
    };

private:
    /*! \cond PRIVATE */
    ResourceState();
    ~ResourceState();
    /*! \endcond */
};
    }
}
#endif  // cascades_resourcestate_h
