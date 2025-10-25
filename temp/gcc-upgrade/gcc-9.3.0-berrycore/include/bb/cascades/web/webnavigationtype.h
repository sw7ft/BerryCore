/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_webnavigationtype_h
#define cascades_webnavigationtype_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>

namespace bb {
  namespace cascades {

   /*!
    * @brief The type of navigation from one location to another.
    *
    * @see @c WebNavigationRequest and @c navigationRequested().
    *
    * @xmlonly
    * <apigrouping group="User interface/Web"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT WebNavigationType
    {
        Q_GADGET
        Q_ENUMS(Type)

    public:

        /*!
         * @brief The type of navigation that caused a navigation requested signal to be emitted.
         *
         * @since BlackBerry 10.0.0
         */
         enum Type {
             /**
              * @brief The user clicked on a link or pressed return on a focused link.
              *
              * @since BlackBerry 10.0.0
              */
             LinkClicked = 0,
             /**
              * @brief The user activated a submit button for an HTML form.
              *
              * @since BlackBerry 10.0.0
              */
             FormSubmitted = 1,
             /**
              * @brief The user activated a back or forward action.
              *
              * @since BlackBerry 10.0.0
              */
             BackForward = 2,
             /**
              * @brief The user activated the reload action.
              *
              * @since BlackBerry 10.0.0
              */
             Reload = 3,
             /**
              * @brief The user submitted an HTML form a second time.
              *
              * @since BlackBerry 10.0.0
              */
             FormResubmitted = 4,
             /**
              * @brief The user navigated to another document using a method not listed above.
              *
              * @since BlackBerry 10.0.0
              */
             Other = 5,
             /**
              * @brief A @c window.open event (or similar) occurred and wants to create a new tab.
              *
              * @since BlackBerry 10.0.0
              */
             OpenWindow = 1000,
         };
    };

  } // namespace cascades
} // namespace bb

#endif // cascades_webnavigationtype_h
