/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef cascades_titlebarscrollbehavior_h
#define cascades_titlebarscrollbehavior_h

#include <QObject>

namespace bb {
    namespace cascades {

   /*!
    * @brief Represents the different types of scroll behavior used for the @c TitleBar.
    *
    * Use the @c %TitleBarScrollBehavior::Type enum values to set a specific scroll behavior for the @c %Page titlebar.
    * The default behavior is @c TitleBarScrollBehavior::Default.
    *
    * Here's an example of how to specify the @c %TitleBarScrollBehavior, in QML.
    * @code
    * Page {
    *    titleBar: TitleBar {
    *     title: "Page"
    *     scrollBehavior: TitleBarScrollBehavior.NonSticky
    *    }
    * }
    * @endcode
    *
    * Here's an example of setting the scroll behavior in C++:
    * @code
    * TitleBar* titleBar = TitleBar::create(TitleBarScrollBehavior::NonSticky, TitleBarKind::Default).title("Test");
    * @endcode
    *
    * @xmlonly
    * <apigrouping group="User interface/Core controls"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.1.0
    */
    class TitleBarScrollBehavior : public QObject {
        Q_GADGET
        Q_ENUMS (Type)

    public:

        /*!
        * @brief Different types of scroll behavior available for the TitleBar:
        *
        * @since BlackBerry 10.1.0
        */
        enum Type {
            /*!
             * @brief Default behavior can be sticky or scrollable depending on device type.
             *
             * @since BlackBerry 10.1.0
             */
            Default,
            /*!
             * @brief TitleBar is sticked on the top of the page.
             *
             * @since BlackBerry 10.1.0
             */
            Sticky,
            /*!
             * @brief TitleBar is scrollable.
             *
             * @since BlackBerry 10.1.0
             */
            NonSticky
        };

    private:

      TitleBarScrollBehavior();
      virtual ~TitleBarScrollBehavior();

    };
}
}

#endif // cascades_titlebarscrollbehavior_h
