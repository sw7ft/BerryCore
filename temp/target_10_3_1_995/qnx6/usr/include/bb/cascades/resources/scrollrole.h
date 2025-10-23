/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef cascades_scrollrole_h
#define cascades_scrollrole_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

   /*!
    * @brief Specifies the @c scrollRole of a scrollable @c Control.
    *
    * A @c scrollRole is an abstract concept that indicates to the framework
    * which scrollable control can be considered as main scrollable,
    * and is connected to various appropriate features such as
    * automatically hiding the Action bar.
    *
    * @see ListView::scrollRole, ScrollView::scrollRole
    *
    * @since BlackBerry 10.1.0
    *
    * @xmlonly
    * <apigrouping group="User interface/Resources"/>
    * @endxmlonly
    */
   class BBCASCADES_EXPORT ScrollRole {
        Q_GADGET
        Q_ENUMS (Type)

    public:

       /*!
        * @brief Specifies the scroll role of a @c Control on a @c Page.
        *
        * @since BlackBerry 10.1.0
        */
        enum Type {
            /*!
             * @brief Default scroll role behavior.
             * This control may be considered as the main scrollable @c Control by the @c Page
             * if it satisfies default requirements of the main scrollable control.
             *
             * @since BlackBerry 10.1.0
             */
            Default,
            /*!
             * @brief This control can't be the main scrollable control of the page
             *
             * @since BlackBerry 10.1.0
             */
            None,
            /*!
             * @brief Control considered as the main scrollable control by the page.
             *
             * @since BlackBerry 10.1.0
             */
            Main
        };

    private:
        /*! @cond PRIVATE */
        ScrollRole();
        ~ScrollRole();
        /*! @endcond */
    };
}
}

#endif // cascades_scrollrole_h
