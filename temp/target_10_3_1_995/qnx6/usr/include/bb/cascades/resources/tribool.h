/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_tribool_h
#define cascades_tribool_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

   /*!
    * 
    * @brief A Boolean data type that allows for a third value called @c Undefined.
    * 
    * The @c Undefined value can either mean that the value is unknown to the framework,
    * or that it's up to the framework to decide the value depending on
    * some other sort of criteria.
    * 
    * @deprecated do not use
    *
    * @xmlonly
    * <apigrouping group="User interface/Resources"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
  class BBCASCADES_EXPORT TriBool {
    Q_GADGET
    Q_ENUMS (Type)

    public:

     /*!
      * @brief Specifies whether the value is @c true, @c false, or undefined.
      *
      * @since BlackBerry 10.0.0
      */
      enum Type {
        /*! @brief Specifies that the framework should decide the value, or the value is unknown.
         *
         * @since BlackBerry 10.0.0
         */
        Undefined = 0,
        /*! @brief Specifies that the value is @c false.
         *
         * @since BlackBerry 10.0.0
         */
        False = 1,
        /*! @brief Specifies that the value is @c true.
         *
         * @since BlackBerry 10.0.0
         */
        True = 2
      };

    private:

      TriBool();
      ~TriBool();
  };
}
}

#endif // cascades_tribool_h
