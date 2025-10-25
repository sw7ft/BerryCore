/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef CASCADES_TEXTFORMAT_H
#define CASCADES_TEXTFORMAT_H

#include <bb/cascades/bbcascades_global.h>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb {
  namespace cascades {
    
    /*!
     * 
     * @brief Defines how a text control should interpret its provided string.
     *
     * @xmlonly
     * <apigrouping group="User interface/Text"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT TextFormat {
      Q_GADGET
      Q_ENUMS (Type)
    public:
      /*!
       * @brief The available formats.
       *
       * @since BlackBerry 10.0.0
       */
      enum Type {
        /*! 
         * @brief The provided string will be interpreted as a regular text string.
         *
         * @since BlackBerry 10.0.0
         */
        Plain = 1, 
        /*! 
         * @brief The provided string will be interpreted as HTML.
         *
         * @since BlackBerry 10.0.0
         */
        Html = 2, 
        /*! 
         * @brief If the provided string is valid HTML, the string will be interpreted
         * as HTML.
         *
         * If the string is not valid HTML, the string is interpreted as plain text.
         *
         * @since BlackBerry 10.0.0
         */
        Auto = 3
      };
      /*! @cond PRIVATE */
    private:
      TextFormat();
      virtual ~TextFormat();
      /*! @endcond */
    };
    
  } // namespace bb::cascades
}
QML_DECLARE_TYPE(bb::cascades::TextFormat::Type)


#endif // CASCADES_TEXTFORMAT_H

