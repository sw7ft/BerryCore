/* Copyright (C) 2014 BlackBerry Limited. All rights reserved. */

#ifndef cascades_headermode_h
#define cascades_headermode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

   /*!
    *
    * @brief A class that represents the different modes of a @c Header.
    *
    * The supported modes of a Header include @c %Default, @c %Plain, and @c %Interactive.
    *
    * The @c %Default mode selects the mode automatically based on
    * whether there's a slot connected to the @c onClicked() signal or not.
    *
    * In @c %Plain mode, the header supports a title and a subtitle.
    *
    * In @c %Interactive mode, the header supports a title, a subtitle, and a clickable button.
    *
    * @xmlonly
    * <apigrouping group="User interface/List"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.3.0
    */
  class BBCASCADES_EXPORT HeaderMode {
    Q_GADGET
    Q_ENUMS (Type)

    public:

     /*!
      * @brief Specifies the different modes of a @c Header.
      *
      * @since BlackBerry 10.3.0
      */
      enum Type {
        /*! @brief Default mode for a @c Header.
         *
         * @since BlackBerry 10.3.0
         */
        Default = 0,

        /*! @brief A plain, non-interactive @c Header.
         *
         * @since BlackBerry 10.3.0
         */
        Plain = 1,

        /*! @brief A clickable @c Header.
         *
         * @since BlackBerry 10.3.0
         */
        Interactive = 2
      };

    private:

      HeaderMode();
      ~HeaderMode();
  };
}
}

#endif // cascades_headermode_h
