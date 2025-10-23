/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_scrollindicatormode_h
#define cascades_scrollindicatormode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

   /*!
    *
    * @brief Represents different types of scroll indicator modes.
    *
    * Used on @c ListView::scrollIndicatorMode to specify if and how a
    * @c ListView should show a scroll indicator. A scroll indicator shows
    * the current scroll position, and cannot be interacted with.
    *
    * @xmlonly
    * <apigrouping group="User interface/Core controls"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT ScrollIndicatorMode
    {
        Q_GADGET
        Q_ENUMS(Type)

    public:
       /*!
        * @brief Specifies if and how a scroll indicator should be shown.
        *
        * @since BlackBerry 10.0.0
        */
        enum Type
        {
            /*! @brief The framework determines the appearance of the scroll
             *  indicator.
             *
             * @since BlackBerry 10.0.0
             */
            Default = 0x0,
            /*! @brief No scroll indicator is shown.
             *
             * @since BlackBerry 10.0.0
             */
            None = 0x1,
            /*!
             * @brief A scroll indicator is shown in the form of a bar with
             * a size that is proportional to how much of the content is visible.
             * In vertically scrollable layouts, the indicator is shown as a
             * vertical bar to the right. In horizontally scrollable layouts,
             * the indicator is shown as a horizontal bar at the bottom. The
             * scroll indicator is not shown if half or more of the content
             * is currently visible.
             *
             * @since BlackBerry 10.0.0
             */
            ProportionalBar = 0x2
        };

    private:
        ScrollIndicatorMode();
        ~ScrollIndicatorMode();
    };
  }
}

#endif // cascades_scrollindicatormode_h

