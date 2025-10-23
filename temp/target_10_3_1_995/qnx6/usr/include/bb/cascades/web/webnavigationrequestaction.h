/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_webnavigationrequestaction_h
#define cascades_webnavigationrequestaction_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>

namespace bb {
  namespace cascades {

  /*!
   * @brief The response action of a navigation request.
   *
   * @see @c WebNavigationRequest and @c WebView::navigationRequested().
   *
   * @xmlonly
   * <apigrouping group="User interface/Web"/>
   * @endxmlonly
   *
   * @since BlackBerry 10.0.0
   */
    class BBCASCADES_EXPORT WebNavigationRequestAction
    {
        Q_GADGET
        Q_ENUMS(Type)

    public:

        /*!
         * @brief The response action of a navigation request.
         *
         * @since BlackBerry 10.0.0
         */
         enum Type {
              /*!
               * @brief Accept the navigation request.
               *
               * @since BlackBerry 10.0.0
               */
              Accept,
              /*!
               * @brief Ignore the navigation request.
               *
               * @since BlackBerry 10.0.0
               */
              Ignore
         };
    };

  } // namespace cascades
} // namespace bb

#endif // cascades_webnavigationrequestaction_h
