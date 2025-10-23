/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_webloadstatus_h
#define cascades_webloadstatus_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>

namespace bb {
  namespace cascades {

   /*!
    * @brief  The load status of a @c WebLoadRequest.
    *
    * A load is considered @c Started once the first bytes of the file
    * being loaded have been received. Once a load has started, it will
    * always eventually reach @c Succeeded or @c Failed status.
    *
    * @xmlonly
    * <apigrouping group="User interface/Web"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT WebLoadStatus
    {
        Q_GADGET
        Q_ENUMS(Type)

    public:

       /*!
        * @brief The load status of a @c WebLoadRequest.
        *
        * @since BlackBerry 10.0.0
        */
        enum Type {
            /*! @brief Loading has started.
             *
             * @since BlackBerry 10.0.0
             */
            Started = 0,
            /*! @brief Loading is finished, and was successful.
             *
             * @since BlackBerry 10.0.0
             */
            Succeeded = 1,
            /*! @brief Loading is finished because the operation failed.
             *
             * @since BlackBerry 10.0.0
             */
            Failed = 2,
        };
    };

  } // namespace cascades
} // namespace bb

#endif // cascades_webloadstatus_h
