/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_textalign_h
#define cascades_textalign_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 * 
 * @brief A set of text alignment configurations to use with text controls.
 *
 * Has to be a @c QObject derivative in order to be accessible from QML.
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TextAlign {
    Q_GADGET
    Q_ENUMS (Type)
public:
   /*!
    * @brief Specifies the alignment of text in a @c Container.
    *
    * @since BlackBerry 10.0.0
    */
    enum Type {
        /*!
         * @brief The framework decides the alignment for the current locale.
         *
         * At the moment the locale alignment is ignored.
         *
         * @since BlackBerry 10.0.0
         */
        Default,
        
        /*!
         * @brief Aligns text to the center.
         *
         * @since BlackBerry 10.0.0
         */
        Center,

        /*!
         * @brief Aligns text to the left.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Left,

        /*!
         * @brief Aligns text to the right.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Right,

        /*!
         * @brief Justified alignment.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Justify

    };
    
private:
    TextAlign();
    ~TextAlign();
};

}
}
   
#endif // cascades_textalign_h

