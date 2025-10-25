/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_scrollrailspolicy_h
#define cascades_scrollrailspolicy_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

    /*!
     * 
     * @brief Rails policies that can be applied to the scrolling behavior of a scrollable control
     * (for example, a @c ScrollView).
     *
     * A rails policy specifies how scrolling behaves in response to a user's dragging gestures.
     * If scrolling is not locked to an axis, the control will scroll in any direction, emulating
     * the dragging movements of the user. Even if the user's intent is to scroll in a single
     * direction (i.e. vertically), slight movements along the horizontal axis will be reflected as well.
     *
     * If scrolling is locked, and a dragging gesture occurs roughly along a particular axis,
     * railing is enabled and scrolling becomes locked along that axis.
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.2.0
     */
    class BBCASCADES_EXPORT ScrollRailsPolicy
    {
        Q_GADGET
        Q_ENUMS(Type)

    public:
        /*!
         * @brief The rails policies for scrolling.
         *
         * @since BlackBerry 10.2.0
         */
        enum Type
        {
            /*! @brief The default rails policy.
             *
             * The system determines the rails policy.
             *
             * @since BlackBerry 10.2.0
             */
            Default = 0x0,
            /*! @brief No rails policy.
             *
             * Railing is not applied, and free scrolling is permitted.
             *
             * @since BlackBerry 10.2.0
             */
            None = 0x1,
            /*! @brief Enables railing when scrolling occurs along a particular axis.
             *
             * If scrolling is initiated roughly along a single axis, railing is enabled and scrolling
             * will lock to that axis. If scrolling is not initiated along
             * any single axis, scrolling will not lock.
             *
             * @since BlackBerry 10.2.0
             */
            LockNearAxes = 0x2,
        };

    private:
        /*! @cond PRIVATE */  
        ScrollRailsPolicy();
        ~ScrollRailsPolicy();
        /*! @endcond */
    };

  }
}

#endif // cascades_scrollrailspolicy_h
