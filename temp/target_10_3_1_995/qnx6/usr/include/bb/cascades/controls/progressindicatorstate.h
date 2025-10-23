/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_progressindicatorstate_h
#define cascades_progressindicatorstate_h

#include <QObject>

#include <bb/cascades/bbcascades_global.h>

namespace bb {
    namespace cascades {

    /*!
     * 
     * @brief Represents the different states of a progress indicator.
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ProgressIndicatorState {
        Q_GADGET
        Q_ENUMS(Type)

    public:
        /*!
         * @brief Specifies the status of a progress indicator.
         *
         * @since BlackBerry 10.0.0
         */
        enum Type {
           /*! @brief Indicates an operation is progressing normally.
            *
            * @since BlackBerry 10.0.0
            */
            Progress = 0,
            /*! @brief Indicates the time or effort for an operation is not known (yet).
             *
             * @since BlackBerry 10.0.0
             */
            Indeterminate = 1,
            /*! @brief Indicates an operation is paused or stalled.
             *
             * @since BlackBerry 10.0.0
             */
            Pause = 2,
            /*! @brief Indicates an error has occurred.
             *
             * @since BlackBerry 10.0.0
             */
            Error = 3,
            /*! @brief Indicates an operation has completed.
             *
             * @since BlackBerry 10.0.0
             */
            Complete = 4
        };

    private:
      /*! \cond PRIVATE */
        ProgressIndicatorState();
        ~ProgressIndicatorState();
      /*! \endcond */
    };

}
}

#endif    // cascades_progressindicatorstate_h
