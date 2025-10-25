/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_itemgrouping_h
#define cascades_itemgrouping_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

   /*!
    * 
    * @brief Represents different ways of grouping items in a @c GroupDataModel.
    *
    * @xmlonly
    * <apigrouping group="Data management/Data models"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT ItemGrouping
    {
        Q_GADGET
        Q_ENUMS(Type)

    public:
       /*!
        * @brief Specifies if and how items are grouped.
        *
        * @since BlackBerry 10.0.0
        */
        enum Type
        {
            /*! 
             * @brief Items are not grouped.
             *
             * @since BlackBerry 10.0.0
             */
            None,
            /*! 
             * @brief Items are grouped.
             * 
             * For @c QString properties, only the first @c QChar (case insensitive) is used when comparing items for grouping.
             *
             * @since BlackBerry 10.0.0
             */
            ByFirstChar,
            /*! 
             * @brief Items are grouped.
             *
             * For @c QString properties, the entire strings (case insensitive) are used when comparing items for grouping.
             *
             * @since BlackBerry 10.0.0
             */
            ByFullValue
        };

    private:
        /*! @cond PRIVATE */
        ItemGrouping();
        ~ItemGrouping();
        /*! @endcond */
    };
}
}

#endif // cascades_itemgrouping_h

