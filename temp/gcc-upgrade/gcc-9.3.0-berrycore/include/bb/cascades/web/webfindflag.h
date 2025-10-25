/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_webfindflag_h
#define cascades_webfindflag_h

#include <bb/cascades/bbcascades_global.h>

#include <QtDeclarative/qdeclarative.h>
#include <QtCore/QObject>

namespace bb {
  namespace cascades {

   /*!
    * @brief A class to wrap a set of flags that can be passed into @c findText().
    *
    * @see @c findText().
    *
    * @xmlonly
    * <apigrouping group="User interface/Web"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT WebFindFlag
    {
        Q_GADGET
        Q_ENUMS(Type)
        Q_FLAGS(Types)

    public:

        /*!
         * @brief The flags that can be passed into a call to @c findText().
         *
         * @xmlonly
         * <qml>
         * <enum flagsType="bb::cascades::WebFindFlag::Types"/>
         * </qml>
         * @endxmlonly
         *
         * @see @c findText().
         *
         * @since BlackBerry 10.0.0
         */
         enum Type {
             /*! @brief Searches backward instead of forward.
              *
              * @since BlackBerry 10.0.0
              */
             Backward = 0x01,
             /*! @brief Search becomes case sensitive instead of insensitive.
              *
              * @since BlackBerry 10.0.0
              */
             CaseSensitive = 0x02,
             /*! @brief Makes @c findText() wrap at the end of the document.
              *
              * @since BlackBerry 10.0.0
              */
             WrapAroundDocument = 0x04,
             /*! @brief Highlights all existing occurrences of a specific string.
              *
              * @since BlackBerry 10.0.0
              */
             HighlightAllOccurrences = 0x08,
         };

         Q_DECLARE_FLAGS(Types, Type)

    };

  } // namespace cascades
} // namespace bb

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::WebFindFlag::Types)
/*! @endcond */

#endif // cascades_webfindflag_h
